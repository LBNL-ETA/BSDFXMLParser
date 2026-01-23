#include <memory>
#include <gtest/gtest.h>
#include <filesystem>
#include <chrono>
#include <iostream>

#include "bsdfdata/Parser.hpp"

#include <fstream>

/// Test loading a full-size BSDF XML file (145x145 matrices).
/// This test helps identify performance issues in FileParse XML parsing.
TEST(BSDFXMLFullFileLoad, Load2011SA1Full)
{
    SCOPED_TRACE("Begin Test: Load full 2011-SA1.XML (145x145 matrices)");
    std::filesystem::path product_path(TEST_DATA_DIR);
    product_path /= "products";
    product_path /= "2011-SA1.XML";

    // Measure load time
    const auto start = std::chrono::high_resolution_clock::now();

    auto product = BSDFData::loadWindowElementFromFile(product_path.string());

    const auto end = std::chrono::high_resolution_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Load time for 2011-SA1.XML: " << duration.count() << " ms" << std::endl;

    // Basic validation
    ASSERT_TRUE(product.has_value());
    EXPECT_EQ(BSDFData::WindowElementType::System, product->windowElementType);

    // Validate material properties
    ASSERT_TRUE(product->optical.layer.material.has_value());
    const auto & material = product->optical.layer.material.value();
    EXPECT_EQ(material.name, "Satine 5500 5%, White Pearl");
    EXPECT_EQ(material.manufacturer, "Nysan");
    ASSERT_TRUE(material.thickness.has_value());
    EXPECT_DOUBLE_EQ(material.thickness->value, 1.0);
    EXPECT_DOUBLE_EQ(material.thermalConductivity.value_or(0), 0.15);
    EXPECT_DOUBLE_EQ(material.TIR.value_or(0), 0.10916);
    EXPECT_DOUBLE_EQ(material.emissivityFront.value_or(0), 0.79626);
    EXPECT_DOUBLE_EQ(material.emissivityBack.value_or(0), 0.79626);
    EXPECT_EQ(material.deviceType, BSDFData::DeviceType::Other);

    // Validate wavelength data exists (should have 8 blocks: 4 solar + 4 visible)
    EXPECT_GE(product->optical.layer.wavelengthData.size(), 2);

    // Validate scattering data dimensions (145x145 for Klems Full basis)
    for(const auto & wavelengthData : product->optical.layer.wavelengthData)
    {
        const auto & scatteringData = wavelengthData.block.scatteringData;
        EXPECT_EQ(scatteringData.size(), 145) << "Expected 145 rows for Klems Full basis";
        if(!scatteringData.empty())
        {
            EXPECT_EQ(scatteringData[0].size(), 145) << "Expected 145 columns for Klems Full basis";
        }
    }

    // Performance assertion: loading should complete in under 1 second
    // (was ~0.2s before, now reportedly >5s which is unacceptable)
    EXPECT_LT(duration.count(), 1000) << "Loading took " << duration.count()
                                       << " ms, expected < 1000 ms";
}

/// Test loading from string to isolate file I/O from parsing
TEST(BSDFXMLFullFileLoad, Load2011SA1FullFromString)
{
    SCOPED_TRACE("Begin Test: Load full 2011-SA1.XML from string");
    std::filesystem::path product_path(TEST_DATA_DIR);
    product_path /= "products";
    product_path /= "2011-SA1.XML";

    // Read file into string first
    std::ifstream file(product_path.string());
    ASSERT_TRUE(file.good()) << "Failed to open file";
    std::string fileContent((std::istreambuf_iterator<char>(file)),
                            std::istreambuf_iterator<char>());
    file.close();

    // Measure parse time (excluding file I/O)
    const auto start = std::chrono::high_resolution_clock::now();

    auto product = BSDFData::loadWindowElementFromString(fileContent);

    const auto end = std::chrono::high_resolution_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Parse time for 2011-SA1.XML (from string): " << duration.count() << " ms"
              << std::endl;

    ASSERT_TRUE(product.has_value());
    EXPECT_EQ(BSDFData::WindowElementType::System, product->windowElementType);

    // Performance assertion
    EXPECT_LT(duration.count(), 1000) << "Parsing took " << duration.count()
                                       << " ms, expected < 1000 ms";
}

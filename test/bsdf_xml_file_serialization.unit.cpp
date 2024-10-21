#include <memory>
#include <gtest/gtest.h>
#include <filesystem>

#include "bsdfdata/Parser.hpp"

#include "test/helper/bsdfxml/TestHelper.hpp"

TEST(BSDFXMLFileSerialization, Load2011SA1SmallMaterialCommaSeparated)
{
    SCOPED_TRACE("Begin Test: Load 2011-SA1-Small-CommaSeparated.XML");
    std::filesystem::path product_path(TEST_DATA_DIR);
    product_path /= "products";
    product_path /= "2011-SA1-Small-CommaSeparated.XML";

    auto product = BSDFData::loadWindowElementFromFile(product_path.string());

    ASSERT_TRUE(product.has_value());
    EXPECT_EQ(BSDFData::WindowElementType::System, product->windowElementType);
    ASSERT_TRUE(product->optical.layer.material.has_value());

    // Define the expected material for comparison
    BSDFData::Material expectedMaterial;
    expectedMaterial.name = "Satine 5500 5%, White Pearl";
    expectedMaterial.manufacturer = "Nysan";
    expectedMaterial.thickness = BSDFData::Thickness{1.0, BSDFData::LengthUnit::Millimeter};
    expectedMaterial.deviceType = BSDFData::DeviceType::Other;
    expectedMaterial.thermalConductivity = 0.15;
    expectedMaterial.airPermeability = std::nullopt;
    expectedMaterial.emissivityFront = 0.79626;
    expectedMaterial.emissivityBack = 0.79626;
    expectedMaterial.TIR = 0.10916;
    expectedMaterial.effectiveOpennessFraction = std::nullopt;
    expectedMaterial.permeabilityFactor = 0.049855;
    expectedMaterial.AERCAcceptance = "@";

    Helper::compareMaterial(expectedMaterial, product->optical.layer.material.value());
}

TEST(BSDFXMLFileSerialization, Load2011SA1SmallDataDefinitionsCommaSeparated)
{
    SCOPED_TRACE("Begin Test: Load 2011-SA1-Small-CommaSeparated.XML");
    std::filesystem::path product_path(TEST_DATA_DIR);
    product_path /= "products";
    product_path /= "2011-SA1-Small-CommaSeparated.XML";

    auto product = BSDFData::loadWindowElementFromFile(product_path.string());

    ASSERT_TRUE(product.has_value());
    EXPECT_EQ(BSDFData::WindowElementType::System, product->windowElementType);
    ASSERT_TRUE(product->optical.layer.dataDefinition.has_value());

    BSDFData::DataDefinition expectedDataDefinition;
    expectedDataDefinition.incidentDataStructure = BSDFData::IncidentDataStructure::Columns;

    // Set expected values for AngleBasis
    BSDFData::AngleBasis angleBasis;
    angleBasis.name = "LBNL/Klems Full";

    // Fill expected blocks for AngleBasis
    angleBasis.blocks = {
      {0, std::nullopt, 1, BSDFData::ThetaBounds{0, 5, std::nullopt}, std::nullopt},
      {10, std::nullopt, 8, BSDFData::ThetaBounds{5, 15, std::nullopt}, std::nullopt},
      {20, std::nullopt, 16, BSDFData::ThetaBounds{15, 25, std::nullopt}, std::nullopt},
      {30, std::nullopt, 20, BSDFData::ThetaBounds{25, 35, std::nullopt}, std::nullopt},
      {40, std::nullopt, 24, BSDFData::ThetaBounds{35, 45, std::nullopt}, std::nullopt},
      {50, std::nullopt, 24, BSDFData::ThetaBounds{45, 55, std::nullopt}, std::nullopt},
      {60, std::nullopt, 24, BSDFData::ThetaBounds{55, 65, std::nullopt}, std::nullopt},
      {70, std::nullopt, 16, BSDFData::ThetaBounds{65, 75, std::nullopt}, std::nullopt},
      {82.5, std::nullopt, 12, BSDFData::ThetaBounds{75, 90, std::nullopt}, std::nullopt}};

    expectedDataDefinition.angleBasis = angleBasis;

    Helper::compareDataDefinition(expectedDataDefinition,
                                  product->optical.layer.dataDefinition.value());
}

TEST(BSDFXMLFileSerialization, Load2011SA1SmallWavelengthDataCommaSeparated)
{
    SCOPED_TRACE("Begin Test: Load 2011-SA1-Small-CommaSeparated.XML");
    std::filesystem::path product_path(TEST_DATA_DIR);
    product_path /= "products";
    product_path /= "2011-SA1-Small-CommaSeparated.XML";

    auto product = BSDFData::loadWindowElementFromFile(product_path.string());

    ASSERT_TRUE(product.has_value());
    EXPECT_EQ(BSDFData::WindowElementType::System, product->windowElementType);

    // Prepare the expected WavelengthData objects
    BSDFData::WavelengthData expectedData1;
    expectedData1.layerNumber = "System";
    expectedData1.wavelength = BSDFData::Wavelength{"Visible", BSDFData::WavelengthUnit::Integral};
    expectedData1.sourceSpectrum = "CIE Illuminant D65 1nm.ssp";
    expectedData1.detectorSpectrum = "ASTM E308 1931 Y.dsp";

    BSDFData::WavelengthData expectedData2 = expectedData1;

    BSDFData::WavelengthDataBlock block1;
    block1.wavelengthDataDirection = BSDFData::WavelengthDataDirection::TransmissionFront;
    block1.columnAngleBasis = "LBNL/Klems Full";
    block1.rowAngleBasis = "LBNL/Klems Full";
    block1.scatteringDataType = BSDFData::ScatteringDataType::BTDF;
    block1.scatteringData = {{2.063833, 0.014938}, {0.014954, 2.027935}};
    expectedData1.block = block1;

    BSDFData::WavelengthDataBlock block2;
    block2.wavelengthDataDirection = BSDFData::WavelengthDataDirection::TransmissionBack;
    block2.columnAngleBasis = "LBNL/Klems Full";
    block2.rowAngleBasis = "LBNL/Klems Full";
    block2.scatteringDataType = BSDFData::ScatteringDataType::BTDF;
    block2.scatteringData = {{2.063833, 0.014938}, {0.014954, 2.027935}};
    expectedData2.block = block2;

    // Ensure that the actual data has two WavelengthData objects
    ASSERT_EQ(product->optical.layer.wavelengthData.size(), 2);

    // Compare the actual data with the expected data
    Helper::compareWavelengthData(expectedData1, product->optical.layer.wavelengthData[0]);
    Helper::compareWavelengthData(expectedData2, product->optical.layer.wavelengthData[1]);
}

TEST(BSDFXMLFileSerialization, Load2011SA1SmallWavelengthDataTabSeparated)
{
    SCOPED_TRACE("Begin Test: Load 2011-SA1-Small-TabSeparated.XML");
    std::filesystem::path product_path(TEST_DATA_DIR);
    product_path /= "products";
    product_path /= "2011-SA1-Small-CommaSeparated.XML";

    auto product = BSDFData::loadWindowElementFromFile(product_path.string());

    ASSERT_TRUE(product.has_value());
    EXPECT_EQ(BSDFData::WindowElementType::System, product->windowElementType);

    // Prepare the expected WavelengthData objects
    BSDFData::WavelengthData expectedData1;
    expectedData1.layerNumber = "System";
    expectedData1.wavelength = BSDFData::Wavelength{"Visible", BSDFData::WavelengthUnit::Integral};
    expectedData1.sourceSpectrum = "CIE Illuminant D65 1nm.ssp";
    expectedData1.detectorSpectrum = "ASTM E308 1931 Y.dsp";

    BSDFData::WavelengthData expectedData2 = expectedData1;

    BSDFData::WavelengthDataBlock block1;
    block1.wavelengthDataDirection = BSDFData::WavelengthDataDirection::TransmissionFront;
    block1.columnAngleBasis = "LBNL/Klems Full";
    block1.rowAngleBasis = "LBNL/Klems Full";
    block1.scatteringDataType = BSDFData::ScatteringDataType::BTDF;
    block1.scatteringData = {{2.063833, 0.014938}, {0.014954, 2.027935}};
    expectedData1.block = block1;

    BSDFData::WavelengthDataBlock block2;
    block2.wavelengthDataDirection = BSDFData::WavelengthDataDirection::TransmissionBack;
    block2.columnAngleBasis = "LBNL/Klems Full";
    block2.rowAngleBasis = "LBNL/Klems Full";
    block2.scatteringDataType = BSDFData::ScatteringDataType::BTDF;
    block2.scatteringData = {{2.063833, 0.014938}, {0.014954, 2.027935}};
    expectedData2.block = block2;

    // Ensure that the actual data has two WavelengthData objects
    ASSERT_EQ(product->optical.layer.wavelengthData.size(), 2);

    // Compare the actual data with the expected data
    Helper::compareWavelengthData(expectedData1, product->optical.layer.wavelengthData[0]);
    Helper::compareWavelengthData(expectedData2, product->optical.layer.wavelengthData[1]);
}

TEST(BSDFXMLFileSerialization, Save2011SA1Small)
{
    SCOPED_TRACE("Begin Test: Save 2011-SA1-Small-CommaSeparated.XML");
    std::filesystem::path product_path(TEST_DATA_DIR);
    product_path /= "products";
    product_path /= "2011-SA1-Small-CommaSeparated.XML";

    // Load the XML file to create a product object
    auto product = BSDFData::loadWindowElementFromFile(product_path.string());
    ASSERT_TRUE(product.has_value());

    // Save the product object to a temporary file
    std::filesystem::path temp_path = "temp_2011-SA1-Small.xml";
      //std::filesystem::temp_directory_path() / "temp_2011-SA1-Small.xml";
    ASSERT_TRUE(BSDFData::saveToFile(*product, temp_path.string()) == 0);

    // Load the serialized file back
    auto serialized_product = BSDFData::loadWindowElementFromFile(temp_path.string());
    ASSERT_TRUE(serialized_product.has_value());

    // Compare the original product with the serialized product
    EXPECT_EQ(product->windowElementType, serialized_product->windowElementType);
    Helper::compareMaterial(product->optical.layer.material.value(),
                            serialized_product->optical.layer.material.value());
    Helper::compareDataDefinition(product->optical.layer.dataDefinition.value(),
                                  serialized_product->optical.layer.dataDefinition.value());

    ASSERT_EQ(product->optical.layer.wavelengthData.size(),
              serialized_product->optical.layer.wavelengthData.size());
    for(size_t i = 0; i < product->optical.layer.wavelengthData.size(); ++i)
    {
        Helper::compareWavelengthData(product->optical.layer.wavelengthData[i],
                                      serialized_product->optical.layer.wavelengthData[i]);
    }

    std::filesystem::remove(temp_path);
}

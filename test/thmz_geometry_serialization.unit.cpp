#include <memory>
#include <gtest/gtest.h>
#include <filesystem>

#include "bsdfdata/Parser.hpp"

#include "test/helper/bsdfxml/TestHelper.hpp"

TEST(THMZFile, Deserialization)
{
    SCOPED_TRACE("Begin Test: THMZ-Geometry.XML");
    std::filesystem::path product_path(TEST_DATA_DIR);
    product_path /= "products";
    product_path /= "THMZ-Geometry.XML";

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

    ASSERT_TRUE(product->optical.layer.geometry.has_value());
    Helper::compareLength(BSDFData::Length{25, BSDFData::LengthUnit::Millimeter}, product->optical.layer.geometry->width);
    Helper::compareLength(BSDFData::Length{0.045, BSDFData::LengthUnit::Meter}, product->optical.layer.geometry->height);
    ASSERT_TRUE(product->optical.layer.geometry->angle.has_value());
    EXPECT_DOUBLE_EQ(23.0, product->optical.layer.geometry->angle.value());
    Helper::compareLength(BSDFData::Length{12, BSDFData::LengthUnit::Millimeter}, product->optical.layer.geometry->spacing);
    ASSERT_TRUE(product->optical.layer.geometry->mgfBlock.has_value());
    EXPECT_EQ("some block text", product->optical.layer.geometry->mgfBlock.value());
}
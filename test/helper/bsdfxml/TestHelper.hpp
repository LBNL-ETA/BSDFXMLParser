#pragma once

#include <BSDFXML/Data.hpp>

namespace Helper
{
    void compareThickness(const BSDFData::Thickness & expected, const BSDFData::Thickness & actual);
    void compareThickness(const std::optional<BSDFData::Thickness> & expected,
                          const std::optional<BSDFData::Thickness> & actual);

    void compareWavelength(const BSDFData::Wavelength & expected, const BSDFData::Wavelength & actual);
    void compareWavelength(const std::optional<BSDFData::Wavelength> & expected,
                          const std::optional<BSDFData::Wavelength> & actual);

    void compareMaterial(const BSDFData::Material & expected, const BSDFData::Material & actual);

    void compareThetaBounds(const BSDFData::ThetaBounds & expected, const BSDFData::ThetaBounds & actual);
    void compareAngleBasisBlock(const BSDFData::AngleBasisBlock & expected, const BSDFData::AngleBasisBlock & actual);
    void compareAngleBasis(const BSDFData::AngleBasis & expected, const BSDFData::AngleBasis & actual);
    void compareDataDefinition(const BSDFData::DataDefinition & expected, const BSDFData::DataDefinition & actual);

    void compareScatteringData(const BSDFData::ScatteringData & expected, const BSDFData::ScatteringData & actual);
    void compareWavelengthDataBlock(const BSDFData::WavelengthDataBlock & expected, const BSDFData::WavelengthDataBlock & actual);
    void compareWavelengthData(const BSDFData::WavelengthData & expected, const BSDFData::WavelengthData & actual);
}   // namespace Helper
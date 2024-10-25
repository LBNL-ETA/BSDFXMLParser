#pragma once

#include <algorithm>
#include <regex>
#include <iterator>
#include <cmath>

#include <fileParse/Common.hxx>
#include <fileParse/Optional.hxx>
#include <fileParse/Variant.hxx>
#include <fileParse/Attributes.hxx>
#include <fileParse/Vector.hxx>
#include <fileParse/StringConversion.hxx>

#include "Data.hpp"
#include "Enumerators.hpp"

#include "EnumSerializers.hpp"

namespace BSDFData
{
    template<typename NodeAdapter>
    const NodeAdapter & operator>>(const NodeAdapter & node, BSDFData::Thickness & thickness)
    {
        using FileParse::operator>>;   // operators for basic C++ types are in the FileParse
                                       // namespace

        FileParse::loadAttribute<NodeAdapter, BSDFData::LengthUnit>(
          node, "unit", thickness.unit, BSDFData::LengthUnitFromString);
        node >> thickness.value;

        return node;
    }

    template<typename NodeAdapter>
    NodeAdapter & operator<<(NodeAdapter & node, const BSDFData::Thickness & thickness)
    {
        using FileParse::operator<<;   // operators for basic C++ types are in the FileParse
                                       // namespace

        FileParse::saveAttribute<NodeAdapter, BSDFData::LengthUnit>(
          node, "unit", thickness.unit, LengthUnitToString);
        node << thickness.value;

        return node;
    }

    template<typename NodeAdapter>
    const NodeAdapter & operator>>(const NodeAdapter & node, BSDFData::Wavelength & wavelength)
    {
        using FileParse::operator>>;   // operators for basic C++ types are in the FileParse
                                       // namespace

        FileParse::loadAttribute<NodeAdapter, BSDFData::WavelengthUnit>(
          node, "unit", wavelength.unit, WavelengthUnitFromString);
        FileParse::loadAttribute(node, "type", wavelength.type);
        node >> wavelength.value;

        return node;
    }

    template<typename NodeAdapter>
    NodeAdapter & operator<<(NodeAdapter & node, const BSDFData::Wavelength & wavelength)
    {
        using FileParse::operator<<;

        FileParse::saveAttribute<NodeAdapter, BSDFData::WavelengthUnit>(
          node, "unit", wavelength.unit, WavelengthUnitToString);
        FileParse::saveAttribute(node, "type", wavelength.type);
        node << wavelength.value;

        return node;
    }

    template<typename NodeAdapter>
    const NodeAdapter & operator>>(const NodeAdapter & node,
                                   BSDFData::OpticalProperties & opticalProperties)
    {
        node >> FileParse::Child{"Transmittance", opticalProperties.transmittance};
        node >> FileParse::Child{"ReflectanceFront", opticalProperties.reflectanceFront};
        node >> FileParse::Child{"ReflectanceBack", opticalProperties.reflectanceBack};
        node >> FileParse::Child{"Comments", opticalProperties.comments};

        return node;
    }

    template<typename NodeAdapter>
    NodeAdapter & operator<<(NodeAdapter & node,
                             const BSDFData::OpticalProperties & opticalProperties)
    {
        node << FileParse::Child{"Transmittance", opticalProperties.transmittance};
        node << FileParse::Child{"ReflectanceFront", opticalProperties.reflectanceFront};
        node << FileParse::Child{"ReflectanceBack", opticalProperties.reflectanceBack};
        node << FileParse::Child{"Comments", opticalProperties.comments};

        return node;
    }

    template<typename NodeAdapter>
    const NodeAdapter & operator>>(const NodeAdapter & node, BSDFData::Material & material)
    {
        using FileParse::Child;
        node >> Child{"Name", material.name};
        node >> Child{"ProductName", material.productName};
        node >> Child{"Manufacturer", material.manufacturer};
        node >> Child{"Thickness", material.thickness};
        node >> Child{"DeviceType", material.deviceType};
        node >> Child{"ThermalConductivity", material.thermalConductivity};
        node >> Child{"AirPermeability", material.airPermeability};
        node >> Child{"EmissivityFront", material.emissivityFront};
        node >> Child{"EmissivityBack", material.emissivityBack};
        node >> Child{"TIR", material.TIR};
        node >> Child{"EffectiveOpennessFraction", material.effectiveOpennessFraction};
        node >> Child{"PermeabilityFactor", material.permeabilityFactor};
        node >> Child{"OpticalProperties", material.opticalProperties};
        node >> Child{"Color", material.color};
        node >> Child{"AERCAcceptance", material.AERCAcceptance};
        node >> Child{"Comments", material.comments};
        node >> Child{"Width", material.width};
        node >> Child{"Height", material.height};
        node >> Child{"Openness", material.openness};

        return node;
    }

    template<typename NodeAdapter>
    NodeAdapter & operator<<(NodeAdapter & node, const BSDFData::Material & material)
    {
        using FileParse::Child;

        node << Child{"Name", material.name};
        node << Child{"ProductName", material.productName};
        node << Child{"Manufacturer", material.manufacturer};
        node << Child{"Thickness", material.thickness};
        node << Child{"DeviceType", material.deviceType};
        node << Child{"ThermalConductivity", material.thermalConductivity};
        node << Child{"AirPermeability", material.airPermeability};
        node << Child{"EmissivityFront", material.emissivityFront};
        node << Child{"EmissivityBack", material.emissivityBack};
        node << Child{"TIR", material.TIR};
        node << Child{"EffectiveOpennessFraction", material.effectiveOpennessFraction};
        node << Child{"PermeabilityFactor", material.permeabilityFactor};
        node << Child{"OpticalProperties", material.opticalProperties};
        node << Child{"Color", material.color};
        node << Child{"AERCAcceptance", material.AERCAcceptance};
        node << Child{"Comments", material.comments};
        node << Child{"Width", material.width};
        node << Child{"Height", material.height};
        node << Child{"Openness", material.openness};

        return node;
    }

    template<typename NodeAdapter>
    const NodeAdapter & operator>>(const NodeAdapter & node, BSDFData::Length & length)
    {
        using FileParse::operator>>;   // operators for basic C++ types are in the FileParse
                                       // namespace

        node >> length.value;
        FileParse::loadAttribute<NodeAdapter, BSDFData::LengthUnit>(
          node, "unit", length.unit, LengthUnitFromString);

        return node;
    }

    template<typename NodeAdapter>
    NodeAdapter & operator<<(NodeAdapter & node, const BSDFData::Length & length)
    {
        using FileParse::operator<<;   // operators for basic C++ types are in the FileParse
                                       // namespace

        node << length.value;
        FileParse::saveAttribute<NodeAdapter, BSDFData::LengthUnit>(
          node, "unit", length.unit, LengthUnitToString);

        return node;
    }

    template<typename NodeAdapter>
    const NodeAdapter & operator>>(const NodeAdapter & node,
                                   BSDFData::LengthWithCavity & lengthWithCavity)
    {
        using FileParse::operator>>;   // operators for basic C++ types are in the FileParse
                                       // namespace

        node >> lengthWithCavity.value;
        FileParse::loadAttribute(node, "cavity", lengthWithCavity.cavity);
        FileParse::loadAttribute<NodeAdapter, BSDFData::LengthUnit>(
          node, "unit", lengthWithCavity.unit, LengthUnitFromString);

        return node;
    }

    template<typename NodeAdapter>
    NodeAdapter & operator<<(NodeAdapter & node,
                             const BSDFData::LengthWithCavity & lengthWithCavity)
    {
        using FileParse::operator<<;   // operators for basic C++ types are in the FileParse
                                       // namespace

        node << lengthWithCavity.value;
        FileParse::saveAttribute(node, "cavity", lengthWithCavity.cavity);
        FileParse::saveAttribute<NodeAdapter, BSDFData::LengthUnit>(
          node, "unit", lengthWithCavity.unit, LengthUnitToString);

        return node;
    }

    template<typename NodeAdapter>
    const NodeAdapter & operator>>(const NodeAdapter & node, BSDFData::Geometry & geometry)
    {
        FileParse::loadAttribute<NodeAdapter, LengthUnit>(
          node, "unit", geometry.unit, LengthUnitFromString);
        FileParse::loadAttribute(node, "format", geometry.format);
        node >> FileParse::Child{"BlindSlatThickness", geometry.blindSlatThickness};
        node >> FileParse::Child{"BlindCurvature", geometry.blindCurvature};
        node >> FileParse::Child{"BlindWidth", geometry.blindWidth};
        node >> FileParse::Child{"BlindSpacing", geometry.blindSpacing};
        node >> FileParse::Child{"BlindAngle", geometry.blindAngle};
        node >> FileParse::Child{"DiffusingGlassCoverageFraction",
                                 geometry.diffusingGlassCoverageFraction};
        node >> FileParse::Child{"WovenShadeOpennessFraction", geometry.wovenShadeOpennessFraction};
        node >> FileParse::Child{"WovenShadeThreadDiameter", geometry.wovenShadeThreadDiameter};
        node >> FileParse::Child{"WovenShadeThreadSpacing", geometry.wovenShadeThreadSpacing};
        node >> FileParse::Child{"WovenShadeThickness", geometry.wovenShadeThickness};
        node >> FileParse::Child{"CellularShadeCellHeight", geometry.cellularShadeCellHeight};
        node >> FileParse::Child{"CellularShadeInnerWallLength",
                                 geometry.cellularShadeInnerWallLength};
        node
          >> FileParse::Child{"CellularShadeSideWallLength", geometry.cellularShadeSideWallLength};
        node >> FileParse::Child{"PleatedShadeCellHeight", geometry.pleatedShadeCellHeight};
        node >> FileParse::Child{"PleatedShadeCellSideWallLength",
                                 geometry.pleatedShadeCellSideWallLength};
        node >> FileParse::Child{"MgfBlock", geometry.mgfBlock};

        return node;
    }

    template<typename NodeAdapter>
    NodeAdapter & operator<<(NodeAdapter & node, const BSDFData::Geometry & geometry)
    {
        FileParse::saveAttribute<NodeAdapter, LengthUnit>(
          node, "unit", geometry.unit, LengthUnitToString);
        FileParse::saveAttribute(node, "format", geometry.format);
        node << FileParse::Child{"BlindSlatThickness", geometry.blindSlatThickness};
        node << FileParse::Child{"BlindCurvature", geometry.blindCurvature};
        node << FileParse::Child{"BlindWidth", geometry.blindWidth};
        node << FileParse::Child{"BlindSpacing", geometry.blindSpacing};
        node << FileParse::Child{"BlindAngle", geometry.blindAngle};
        node << FileParse::Child{"DiffusingGlassCoverageFraction",
                                 geometry.diffusingGlassCoverageFraction};
        node << FileParse::Child{"WovenShadeOpennessFraction", geometry.wovenShadeOpennessFraction};
        node << FileParse::Child{"WovenShadeThreadDiameter", geometry.wovenShadeThreadDiameter};
        node << FileParse::Child{"WovenShadeThreadSpacing", geometry.wovenShadeThreadSpacing};
        node << FileParse::Child{"WovenShadeThickness", geometry.wovenShadeThickness};
        node << FileParse::Child{"CellularShadeCellHeight", geometry.cellularShadeCellHeight};
        node << FileParse::Child{"CellularShadeInnerWallLength",
                                 geometry.cellularShadeInnerWallLength};
        node << FileParse::Child{"CellularShadeSideWallLength",
                                 geometry.cellularShadeSideWallLength};
        node << FileParse::Child{"PleatedShadeCellHeight", geometry.pleatedShadeCellHeight};
        node << FileParse::Child{"PleatedShadeCellSideWallLength",
                                 geometry.pleatedShadeCellSideWallLength};
        node << FileParse::Child{"MgfBlock", geometry.mgfBlock};

        return node;
    }

    template<typename NodeAdapter>
    const NodeAdapter & operator>>(const NodeAdapter & node, BSDFData::ThetaBounds & thetaBounds)
    {
        node >> FileParse::Child{"LowerTheta", thetaBounds.lowerTheta};
        node >> FileParse::Child{"UpperTheta", thetaBounds.upperTheta};
        node >> FileParse::Child{"Comments", thetaBounds.comments};

        return node;
    }

    template<typename NodeAdapter>
    NodeAdapter & operator<<(NodeAdapter & node, const BSDFData::ThetaBounds & thetaBounds)
    {
        node << FileParse::Child{"LowerTheta", thetaBounds.lowerTheta};
        node << FileParse::Child{"UpperTheta", thetaBounds.upperTheta};
        node << FileParse::Child{"Comments", thetaBounds.comments};

        return node;
    }

    template<typename NodeAdapter>
    const NodeAdapter & operator>>(const NodeAdapter & node,
                                   BSDFData::AngleBasisBlock & angleBasisBlock)
    {
        node >> FileParse::Child{"Theta", angleBasisBlock.theta};
        node >> FileParse::Child{"Phi", angleBasisBlock.phi};
        node >> FileParse::Child{"nPhis", angleBasisBlock.nPhis};
        FileParse::deserializeOptionalVariant(
          node, {"SolidAngle", "ThetaBounds"}, angleBasisBlock.bounds);
        node >> FileParse::Child{"Comments", angleBasisBlock.comments};

        return node;
    }

    template<typename NodeAdapter>
    NodeAdapter & operator<<(NodeAdapter & node, const BSDFData::AngleBasisBlock & angleBasisBlock)
    {
        node << FileParse::Child{"Theta", angleBasisBlock.theta};
        node << FileParse::Child{"Phi", angleBasisBlock.phi};
        node << FileParse::Child{"nPhis", angleBasisBlock.nPhis};
        FileParse::serializeOptionalVariant(
          node, {"SolidAngle", "ThetaBounds"}, angleBasisBlock.bounds);
        node << FileParse::Child{"Comments", angleBasisBlock.comments};

        return node;
    }

    template<typename NodeAdapter>
    const NodeAdapter & operator>>(const NodeAdapter & node, BSDFData::AngleBasis & angleBasis)
    {
        node >> FileParse::Child{"AngleBasisName", angleBasis.name};
        node >> FileParse::Child{"AngleBasisBlock", angleBasis.blocks};

        return node;
    }

    template<typename NodeAdapter>
    NodeAdapter & operator<<(NodeAdapter & node, const BSDFData::AngleBasis & angleBasis)
    {
        node << FileParse::Child{"AngleBasisName", angleBasis.name};
        node << FileParse::Child{"AngleBasisBlock", angleBasis.blocks};

        return node;
    }

    template<typename NodeAdapter>
    const NodeAdapter & operator>>(const NodeAdapter & node,
                                   BSDFData::DataDefinition & dataDefinition)
    {
        node >> FileParse::Child{"IncidentDataStructure", dataDefinition.incidentDataStructure};
        node >> FileParse::Child{"AngleBasis", dataDefinition.angleBasis};
        node >> FileParse::Child{"Comments", dataDefinition.comments};

        return node;
    }

    template<typename NodeAdapter>
    NodeAdapter & operator<<(NodeAdapter & node, const BSDFData::DataDefinition & dataDefinition)
    {
        node << FileParse::Child{"IncidentDataStructure", dataDefinition.incidentDataStructure};
        node << FileParse::Child{"AngleBasis", dataDefinition.angleBasis};
        node << FileParse::Child{"Comments", dataDefinition.comments};

        return node;
    }

    namespace
    {
        /// Trims whitespace from the start and end of a string.
        inline std::string trimWhitespace(const std::string & str)
        {
            const auto start = str.find_first_not_of(" \t");
            const auto end = str.find_last_not_of(" \t");

            return (start == std::string::npos || end == std::string::npos)
                     ? ""
                     : str.substr(start, end - start + 1);
        }

        /// Parses a single line of comma-separated values into a vector of doubles.
        std::vector<double> parseRow(const std::string & line)
        {
            std::vector<double> result;
            std::regex regex("[,\t]");   // Regular expression to match commas or tabs
            std::sregex_token_iterator iter(line.begin(), line.end(), regex, -1);
            std::sregex_token_iterator end;

            for(; iter != end; ++iter)
            {
                try
                {
                    if(!iter->str().empty())
                    {
                        result.push_back(std::stod(iter->str()));
                    }
                }
                catch(const std::invalid_argument &)
                {
                    // Handle conversion error if needed
                }
            }

            return result;
        }

        std::vector<std::vector<double>> convertToSquareMatrix(std::vector<double> const & v)
        {
            double intPart;
            if(std::modf(std::sqrt(v.size()), &intPart) != 0)
            {
                throw std::runtime_error("Non-square matrix");
            }
            const auto size = static_cast<size_t>(intPart);
            std::vector<double> inner;
            inner.resize(size);
            std::vector<std::vector<double>> m(size, inner);
            for(size_t row = 0; row < size; ++row)
            {
                for(size_t col = 0; col < size; ++col)
                {
                    m[row][col] = v[row * size + col];
                }
            }
            return m;
        }
    }   // namespace

    /// Parses a string representation of scattering data into a vector of vectors of doubles.
    inline BSDFData::ScatteringData parseScatteringData(const std::string & value)
    {
        std::vector<double> data;
        std::istringstream inputStream(value);
        std::string line;

        while(std::getline(inputStream, line))
        {
            auto row = parseRow(line);
            data.insert(data.end(), row.begin(), row.end());
        }

        return convertToSquareMatrix(data);
    }

    template<typename NodeAdapter>
    const NodeAdapter & operator>>(const NodeAdapter & node,
                                   BSDFData::ScatteringData & scatteringData)
    {
        std::string value;
        node >> FileParse::Child{"ScatteringData", value};

        scatteringData = parseScatteringData(value);

        return node;
    }

    namespace
    {
        /// Converts a row of double values into a comma-separated string.
        std::string serializeRow(const std::vector<double> & row)
        {
            std::ostringstream rowStream;

            // Transform each element into a formatted string and join them with ", "
            std::transform(row.begin(),
                           row.end(),
                           std::ostream_iterator<std::string>(rowStream, ", "),
                           [](double value) { return FileParse::formatDouble(value, 5, 1, 0.99); });

            return rowStream.str();
        }
    }   // anonymous namespace

    /// Serializes the entire ScatteringData into a single string.
    inline std::string serializeScatteringData(const BSDFData::ScatteringData & scatteringData)
    {
        std::ostringstream outputStream;

        // Adding new line at the beginning of the matrix so that it looks nicely formatted
        outputStream << "\n";

        std::for_each(scatteringData.begin(), scatteringData.end(), [&](const auto & row) {
            outputStream << serializeRow(row) << "\n";
        });

        return outputStream.str();
    }

    template<typename NodeAdapter>
    NodeAdapter & operator<<(NodeAdapter & node, const BSDFData::ScatteringData & scatteringData)
    {
        const std::string value{serializeScatteringData(scatteringData)};
        node << FileParse::Child{"ScatteringData", value};

        return node;
    }

    template<typename NodeAdapter>
    const NodeAdapter & operator>>(const NodeAdapter & node,
                                   BSDFData::WavelengthDataBlock & wavelengthDataBlock)
    {
        node >> FileParse::Child{"WavelengthDataDirection",
                                 wavelengthDataBlock.wavelengthDataDirection};
        node >> FileParse::Child{"ColumnAngleBasis", wavelengthDataBlock.columnAngleBasis};
        node >> FileParse::Child{"RowAngleBasis", wavelengthDataBlock.rowAngleBasis};
        node >> FileParse::Child{"ScatteringDataType", wavelengthDataBlock.scatteringDataType};
        // Child node name is moved down to the ScatteringData serializer since compiler cannot
        // resolve between serializer of std::vector<std::vector<double>> and Child<std::vector<T>>
        // defined in FileParse
        node >> wavelengthDataBlock.scatteringData;

        return node;
    }

    template<typename NodeAdapter>
    NodeAdapter & operator<<(NodeAdapter & node,
                             const BSDFData::WavelengthDataBlock & wavelengthDataBlock)
    {
        node << FileParse::Child{"WavelengthDataDirection",
                                 wavelengthDataBlock.wavelengthDataDirection};
        node << FileParse::Child{"ColumnAngleBasis", wavelengthDataBlock.columnAngleBasis};
        node << FileParse::Child{"RowAngleBasis", wavelengthDataBlock.rowAngleBasis};
        node << FileParse::Child{"ScatteringDataType", wavelengthDataBlock.scatteringDataType};
        // Child node name is moved down to the ScatteringData serializer since compiler cannot
        // resolve between serializer of std::vector<std::vector<double>> and Child<std::vector<T>>
        // defined in FileParse
        node << wavelengthDataBlock.scatteringData;

        return node;
    }

    template<typename NodeAdapter>
    const NodeAdapter & operator>>(const NodeAdapter & node,
                                   BSDFData::WavelengthData & wavelengthData)
    {
        node >> FileParse::Child{"LayerNumber", wavelengthData.layerNumber};
        node >> FileParse::Child{"Angle", wavelengthData.angle};
        node >> FileParse::Child{"Wavelength", wavelengthData.wavelength};
        node >> FileParse::Child{"SourceSpectrum", wavelengthData.sourceSpectrum};
        node >> FileParse::Child{"DetectorSpectrum", wavelengthData.detectorSpectrum};
        node >> FileParse::Child{"WavelengthDataBlock", wavelengthData.block};
        node >> FileParse::Child{"Comments", wavelengthData.comments};

        return node;
    }

    template<typename NodeAdapter>
    NodeAdapter & operator<<(NodeAdapter & node, const BSDFData::WavelengthData & wavelengthData)
    {
        node << FileParse::Child{"LayerNumber", wavelengthData.layerNumber};
        node << FileParse::Child{"Angle", wavelengthData.angle};
        node << FileParse::Child{"Wavelength", wavelengthData.wavelength};
        node << FileParse::Child{"SourceSpectrum", wavelengthData.sourceSpectrum};
        node << FileParse::Child{"DetectorSpectrum", wavelengthData.detectorSpectrum};
        node << FileParse::Child{"WavelengthDataBlock", wavelengthData.block};
        node << FileParse::Child{"Comments", wavelengthData.comments};

        return node;
    }

    template<typename NodeAdapter>
    const NodeAdapter & operator>>(const NodeAdapter & node, BSDFData::Layer & layer)
    {
        node >> FileParse::Child{"Material", layer.material};
        node >> FileParse::Child{"Geometry", layer.geometry};
        node >> FileParse::Child{"DataDefinition", layer.dataDefinition};
        node >> FileParse::Child{"WavelengthData", layer.wavelengthData};

        return node;
    }

    template<typename NodeAdapter>
    NodeAdapter & operator<<(NodeAdapter & node, const BSDFData::Layer & layer)
    {
        node << FileParse::Child{"Material", layer.material};
        node << FileParse::Child{"Geometry", layer.geometry};
        node << FileParse::Child{"DataDefinition", layer.dataDefinition};
        node << FileParse::Child{"WavelengthData", layer.wavelengthData};

        return node;
    }

    template<typename NodeAdapter>
    const NodeAdapter & operator>>(const NodeAdapter & node, BSDFData::Optical & optical)
    {
        node >> FileParse::Child{"Layer", optical.layer};

        return node;
    }

    template<typename NodeAdapter>
    NodeAdapter & operator<<(NodeAdapter & node, const BSDFData::Optical & optical)
    {
        node << FileParse::Child{"Layer", optical.layer};

        return node;
    }

    template<typename NodeAdapter>
    const NodeAdapter & operator>>(const NodeAdapter & node,
                                   BSDFData::WindowElement & windowElement)
    {
        node >> FileParse::Child{"WindowElementType", windowElement.windowElementType};
        node >> FileParse::Child{"FileType", windowElement.fileType};
        node >> FileParse::Child{"Checksum", windowElement.Checksum};
        node >> FileParse::Child{"Optical", windowElement.optical};

        return node;
    }

    template<typename NodeAdapter>
    NodeAdapter & operator<<(NodeAdapter & node, const BSDFData::WindowElement & windowElement)
    {
        node << FileParse::Child{"WindowElementType", windowElement.windowElementType};
        node << FileParse::Child{"FileType", windowElement.fileType};
        node << FileParse::Child{"Checksum", windowElement.Checksum};
        node << FileParse::Child{"Optical", windowElement.optical};

        return node;
    }

}   // namespace BSDFData
#pragma once

#include <fileParse/Enum.hxx>

#include "Enumerators.hpp"

namespace BSDFData
{
    template<typename NodeAdapter>
    const NodeAdapter & operator>>(const NodeAdapter & node,
                                   BSDFData::WindowElementType & windowElementType)
    {
        return FileParse::deserializeEnum<NodeAdapter, WindowElementType>(
          node, windowElementType, windowElementTypeFromString);
    }

    template<typename NodeAdapter>
    NodeAdapter & operator<<(NodeAdapter & node,
                             const BSDFData::WindowElementType & windowElementType)
    {
        return FileParse::serializeEnum<NodeAdapter, WindowElementType>(
          node, windowElementType, windowElementTypeToString);
    }

    template<typename NodeAdapter>
    const NodeAdapter & operator>>(const NodeAdapter & node, BSDFData::DeviceType & deviceType)
    {
        return FileParse::deserializeEnum<NodeAdapter, DeviceType>(
          node, deviceType, DeviceTypeFromString);
    }

    template<typename NodeAdapter>
    NodeAdapter & operator<<(NodeAdapter & node, const BSDFData::DeviceType & deviceType)
    {
        return FileParse::serializeEnum<NodeAdapter, DeviceType>(
          node, deviceType, DeviceTypeToString);
    }

    template<typename NodeAdapter>
    const NodeAdapter & operator>>(const NodeAdapter & node,
                                   BSDFData::IncidentDataStructure & incidentDataStructure)
    {
        return FileParse::deserializeEnum<NodeAdapter, IncidentDataStructure>(
          node, incidentDataStructure, IncidentDataStructureFromString);
    }

    template<typename NodeAdapter>
    NodeAdapter & operator<<(NodeAdapter & node,
                             const BSDFData::IncidentDataStructure & incidentDataStructure)
    {
        return FileParse::serializeEnum<NodeAdapter, IncidentDataStructure>(
          node, incidentDataStructure, IncidentDataStructureToString);
    }

    template<typename NodeAdapter>
    const NodeAdapter & operator>>(const NodeAdapter & node,
                                   BSDFData::WavelengthDataDirection & wavelengthDataDirection)
    {
        return FileParse::deserializeEnum<NodeAdapter, WavelengthDataDirection>(
          node, wavelengthDataDirection, WavelengthDataDirectionFromString);
    }

    template<typename NodeAdapter>
    NodeAdapter & operator<<(NodeAdapter & node,
                             const BSDFData::WavelengthDataDirection & wavelengthDataDirection)
    {
        return FileParse::serializeEnum<NodeAdapter, WavelengthDataDirection>(
          node, wavelengthDataDirection, WavelengthDataDirectionToString);
    }

    template<typename NodeAdapter>
    const NodeAdapter & operator>>(const NodeAdapter & node,
                                   BSDFData::ScatteringDataType & scatteringDataType)
    {
        return FileParse::deserializeEnum<NodeAdapter, ScatteringDataType>(
          node, scatteringDataType, ScatteringDataTypeFromString);
    }

    template<typename NodeAdapter>
    NodeAdapter & operator<<(NodeAdapter & node,
                             const BSDFData::ScatteringDataType & scatteringDataType)
    {
        return FileParse::serializeEnum<NodeAdapter, ScatteringDataType>(
          node, scatteringDataType, ScatteringDataTypeToString);
    }

    template<typename NodeAdapter>
    const NodeAdapter & operator>>(const NodeAdapter & node, BSDFData::FileType & fileType)
    {
        return FileParse::deserializeEnum<NodeAdapter, FileType>(
          node, fileType, FileTypeFromString);
    }

    template<typename NodeAdapter>
    NodeAdapter & operator<<(NodeAdapter & node, const BSDFData::FileType & fileType)
    {
        return FileParse::serializeEnum<NodeAdapter, FileType>(node, fileType, FileTypeToString);
    }

    template<typename NodeAdapter>
    const NodeAdapter & operator>>(const NodeAdapter & node,
                                   BSDFData::WavelengthUnit & wavelengthUnit)
    {
        return FileParse::deserializeEnum<NodeAdapter, WavelengthUnit>(
          node, wavelengthUnit, WavelengthUnitFromString);
    }

    template<typename NodeAdapter>
    NodeAdapter & operator<<(NodeAdapter & node, const BSDFData::WavelengthUnit & wavelengthUnit)
    {
        return FileParse::serializeEnum<NodeAdapter, WavelengthUnit>(
          node, wavelengthUnit, WavelengthUnitToString);
    }

    template<typename NodeAdapter>
    const NodeAdapter & operator>>(const NodeAdapter & node, BSDFData::LengthUnit & lengthUnit)
    {
        return FileParse::deserializeEnum<NodeAdapter, LengthUnit>(
          node, lengthUnit, LengthUnitFromString);
    }

    template<typename NodeAdapter>
    NodeAdapter & operator<<(NodeAdapter & node, const BSDFData::LengthUnit & lengthUnit)
    {
        return FileParse::serializeEnum<NodeAdapter, LengthUnit>(
          node, lengthUnit, LengthUnitToString);
    }

    template<typename NodeAdapter>
    const NodeAdapter & operator>>(const NodeAdapter & node,
                                   BSDFData::ConductivityUnit & conductivityUnit)
    {
        return FileParse::deserializeEnum<NodeAdapter, ConductivityUnit>(
          node, conductivityUnit, ConductivityUnitFromString);
    }

    template<typename NodeAdapter>
    NodeAdapter & operator<<(NodeAdapter & node, const BSDFData::ConductivityUnit & conductivityUnit)
    {
        return FileParse::serializeEnum<NodeAdapter, ConductivityUnit>(
          node, conductivityUnit, ConductivityUnitToString);
    }
}   // namespace BSDFXML
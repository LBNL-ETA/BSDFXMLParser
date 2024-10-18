#pragma once

#include <string>
#include <optional>

#include "Data.hpp"

namespace BSDFData
{
    std::optional<WindowElement> loadWindowElementFromFile(std::string_view fileName);
    int saveToFile(const WindowElement & model, std::string_view fileName);
}
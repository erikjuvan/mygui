#pragma once

#include "Config.hpp"
#include <SFML/Graphics.hpp>

namespace mygui
{

class MYGUI_API ResourceManager
{
private:
    inline static std::string m_system_font_name; // No default font

public:
    static void        SetSystemFontName(std::string const& system_font_name) { m_system_font_name = system_font_name; }
    static std::string GetSystemFontName() { return m_system_font_name; }
};

} // namespace mygui
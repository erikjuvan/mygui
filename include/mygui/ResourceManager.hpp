#pragma once

#include "Config.hpp"
#include <SFML/Graphics.hpp>

namespace mygui
{

class MYGUI_API ResourceManager
{
protected:
    inline static std::string m_system_font_name = "arial.ttf"; // default

public:
    ResourceManager() {}
    ResourceManager(ResourceManager const& rm) = delete;
    ResourceManager& operator=(ResourceManager const& rm) = delete;

    static void FontName(std::string const& font_name) { m_system_font_name = font_name; }
};

} // namespace mygui
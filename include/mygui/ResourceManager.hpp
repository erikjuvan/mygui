#pragma once

#include "Config.hpp"
#include <SFML/Graphics.hpp>

namespace mygui
{

class MYGUI_API ResourceManager
{
private:
    std::shared_ptr<sf::Font> m_font;

public:
    bool Font(std::string const& font_name)
    {
        if (!m_font) {
            m_font = std::make_shared<sf::Font>();
        }
        return m_font->loadFromFile(font_name);
    }

    auto Font() const
    {
        return m_font;
    }
};

} // namespace mygui
#include "Label.hpp"

namespace mygui
{

Label::Label(int x, int y, const char* text, int character_size, const char* font_name)
{

    m_font.loadFromFile(font_name);
    m_text.setFont(m_font);
    m_text.setString(text);
    m_text.setCharacterSize(character_size);
    m_text.setPosition(x, y);
    m_text.setFillColor(sf::Color::Black);
}

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_text);
}

void Label::Handle(const sf::Event& event)
{
    if (!Enabled())
        return;

    if (m_text.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            if (m_onClick)
                m_onClick();
        }
    }
}

void Label::SetText(const std::string& text)
{
    m_text.setString(text);
}

void Label::Enabled(bool enabled)
{
    m_enabled = enabled;
    if (enabled) {
        m_text.setFillColor(sf::Color::Black);
    } else {
        m_text.setFillColor(sf::Color(100, 100, 100));
    }
}

bool Label::Enabled() const
{
    return m_enabled;
}

// Actions
void Label::OnClick(const fptr& f)
{
    m_onClick = f;
}

} // namespace mygui
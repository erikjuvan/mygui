#include "Label.hpp"

namespace mygui
{

Label::Label(int x, int y, std::string const& text, int character_size) :
    m_x(x), m_y(y)
{
    m_font.loadFromFile(m_system_font_name);
    m_text.setFont(m_font);
    m_text.setCharacterSize(character_size);
    m_text.setFillColor(sf::Color::Black);
    SetText(text);
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
            if (m_onClick != nullptr)
                m_onClick();
        }
    }
}

void Label::SetText(const std::string& text)
{
    // top heavy/bottom heavy letter hack
    m_text.setString("I"); // choose top heavy string and save center
    float y_center = m_text.getLocalBounds().top + m_text.getLocalBounds().height / 2.f;
    // Set text
    m_text.setString(text);
    // Get bounds
    auto const& text_bounds = m_text.getLocalBounds();
    // Correct location to left middle
    m_text.setOrigin(text_bounds.left, y_center);
    m_text.setPosition(m_x, m_y);
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
void Label::OnClick(const callback_type& f)
{
    m_onClick = f;
}

} // namespace mygui
#include "Button.hpp"

namespace mygui
{

Button::Button(int x, int y, const char* text, int w, int h, int character_size) :
    m_idle_shape(sf::Vector2f(static_cast<float>(w), static_cast<float>(h))), m_pressed_shape(m_idle_shape), m_pressed(false)
{
    m_idle_shape.setPosition(static_cast<float>(x), static_cast<float>(y));
    m_idle_shape.setFillColor(m_idle_color);
    m_idle_shape.setOutlineColor(sf::Color::Black);
    m_idle_shape.setOutlineThickness(1.f);

    m_pressed_shape.setPosition(static_cast<float>(x), static_cast<float>(y));
    m_pressed_shape.setFillColor(sf::Color(200, 230, 235));
    m_pressed_shape.setOutlineColor(sf::Color::Black);
    m_pressed_shape.setOutlineThickness(1.f);

    m_mouseover_shape.setPosition(static_cast<float>(x), static_cast<float>(y));
    m_mouseover_shape.setFillColor(sf::Color(215, 240, 245));
    m_mouseover_shape.setOutlineColor(sf::Color::Black);
    m_mouseover_shape.setOutlineThickness(1.f);

    m_active_shape = &m_idle_shape;

    m_font.loadFromFile(m_system_font_name);
    m_text.setFont(m_font);
    m_text.setCharacterSize(character_size);
    m_text.setFillColor(sf::Color::Black);
    SetText(text);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*m_active_shape, states);
    target.draw(m_text, states);
}

void Button::Handle(const sf::Event& event)
{
    if (!Enabled())
        return;

    if (m_active_shape->getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            m_active_shape = &m_pressed_shape;
            m_pressed      = true;
        } else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            m_active_shape = &m_idle_shape;
            if (m_onClick != nullptr && m_pressed)
                m_onClick();
            m_pressed = false;
        }
    } else {
        if (m_active_shape == &m_pressed_shape && event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            m_active_shape = &m_idle_shape;
            m_pressed      = false;
        }
    }
}

void Button::Enabled(bool enabled)
{
    m_enabled = enabled;
    if (enabled) {
        m_text.setFillColor(sf::Color::Black);
    } else {
        m_text.setFillColor(sf::Color(100, 100, 100));
    }
}

bool Button::Enabled() const
{
    return m_enabled;
}

void Button::SetText(const std::string& text)
{
    // top heavy/bottom heavy letter hack
    m_text.setString("I"); // choose top heavy string and save center
    float y_center = m_text.getLocalBounds().top + m_text.getLocalBounds().height / 2.f;
    // Set text
    m_text.setString(text);
    // Get bounds
    auto const& text_bounds  = m_text.getLocalBounds();
    auto const& shape_bounds = m_idle_shape.getGlobalBounds();
    // Correct location to center
    m_text.setOrigin(text_bounds.left + text_bounds.width / 2.f, y_center);
    m_text.setPosition(shape_bounds.left + shape_bounds.width / 2.f, shape_bounds.top + shape_bounds.height / 2.f);
}

sf::FloatRect Button::GetGlobalBounds()
{
    return m_idle_shape.getGlobalBounds();
}

void Button::SetColor(const sf::Color& col)
{
    m_idle_shape.setFillColor(col);
}

void Button::ResetColor()
{
    m_idle_shape.setFillColor(m_idle_color);
}

void Button::OnClick(const callback_type& f)
{
    m_onClick = f;
}

} // namespace mygui
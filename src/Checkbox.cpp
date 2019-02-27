#include "Checkbox.hpp"
#include "ResourceManager.hpp"
#include <iostream>

namespace mygui
{

Checkbox::Checkbox(int x, int y, std::string const& text, int w, int h, int character_size) :
    m_rect_checked(sf::Vector2f(static_cast<float>(w), static_cast<float>(h))),
    m_rect_unchecked(m_rect_checked), m_checked(false)
{

    m_rect_checked.setPosition(static_cast<float>(x), static_cast<float>(y));
    m_rect_checked.setFillColor(sf::Color::Black);
    m_rect_checked.setOutlineColor(sf::Color::Black);
    m_rect_checked.setOutlineThickness(1.f);

    m_rect_unchecked.setPosition(static_cast<float>(x), static_cast<float>(y));
    m_rect_unchecked.setFillColor(sf::Color::White);
    m_rect_unchecked.setOutlineColor(sf::Color::Black);
    m_rect_unchecked.setOutlineThickness(1.f);

    m_rect = &m_rect_unchecked;

    m_font.loadFromFile(ResourceManager::GetSystemFontName());
    m_text.setFont(m_font);
    m_text.setCharacterSize(character_size);
    m_text.setFillColor(sf::Color::Black);
    SetText(text);
}

void Checkbox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*m_rect);
    target.draw(m_text);
}

void Checkbox::Handle(const sf::Event& event)
{
    if (!Enabled())
        return;

    if (m_rect->getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            m_pressed_in_focus = true;
        } else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            if (m_pressed_in_focus) {
                if (!m_checked) {
                    m_rect    = &m_rect_checked;
                    m_checked = true;
                } else {
                    m_rect    = &m_rect_unchecked;
                    m_checked = false;
                }

                if (m_onClick != nullptr)
                    m_onClick();

                m_pressed_in_focus = false;
            }
        }
    } else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        m_pressed_in_focus = false;
    }
}

// Actions
void Checkbox::OnClick(const callback_type& f)
{
    m_onClick = f;
}

bool Checkbox::Checked() const
{
    return m_checked;
}

void Checkbox::Checked(bool checked)
{
    m_checked = checked;
    if (checked) {
        m_rect = &m_rect_checked;
    } else {
        m_rect = &m_rect_unchecked;
    }
}

void Checkbox::Enabled(bool enabled)
{
    m_enabled = enabled;
    if (enabled) {
        m_text.setFillColor(sf::Color::Black);
    } else {
        m_text.setFillColor(sf::Color(100, 100, 100));
    }
}

bool Checkbox::Enabled() const
{
    return m_enabled;
}

// Known "issue"  (not really an issue just an estetic "bug") that I circumvented - if text has top heavy 'b' and/or bottom heavy 'p' - letters then the center of text changes
// e.g. if text is "ab" vs "ap" those 2 texts won't be aligned, "ab" will be lower and "ap" will be higher
void Checkbox::SetText(const std::string& text)
{
    // top heavy/bottom heavy letter hack
    m_text.setString("I"); // choose top heavy string and save center
    float y_center = m_text.getLocalBounds().top + m_text.getLocalBounds().height / 2.f;
    // Set text
    m_text.setString(text);
    // Get bounds
    auto const& text_bounds  = m_text.getLocalBounds();
    auto const& shape_bounds = m_rect_unchecked.getGlobalBounds();
    // Correct location to left middle
    m_text.setOrigin(text_bounds.left, y_center);
    m_text.setPosition(shape_bounds.left + shape_bounds.width + 4.f, shape_bounds.top + shape_bounds.height / 2.f);
}

} // namespace mygui
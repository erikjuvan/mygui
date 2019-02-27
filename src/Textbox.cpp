#include "Textbox.hpp"
#include "ResourceManager.hpp"

namespace mygui
{

Textbox::Textbox(int x, int y, const std::string& text, int w, int h, int character_size) :
    m_rect(sf::Vector2f(static_cast<float>(w), static_cast<float>(h)))
{

    m_rect.setPosition(static_cast<float>(x), static_cast<float>(y));
    m_rect.setFillColor(sf::Color::White);
    m_rect.setOutlineColor(sf::Color::Black);
    m_rect.setOutlineThickness(1.f);

    m_font.loadFromFile(ResourceManager::GetSystemFontName());
    m_text.setFont(m_font);
    m_text.setCharacterSize(character_size);
    m_text.setFillColor(sf::Color::Black);
    SetText(text);
}

void Textbox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_rect);
    target.draw(m_text);
}

void Textbox::Handle(const sf::Event& event)
{
    if (!Enabled())
        return;

    if (event.type == sf::Event::TextEntered && m_mouseover) {

        std::string str = m_text.getString();

        if (event.text.unicode == '\b') {
            if (str.length() > 0)
                str.pop_back();
        } else {
            str += event.text.unicode;
        }

        // temporary text to see if the added character is too long to fit into the textbox
        sf::Text txt(m_text);
        txt.setString(str);

        if (txt.getGlobalBounds().width < (m_rect.getGlobalBounds().width - m_margin))
            SetText(str);

        if (m_keyPress != nullptr)
            m_keyPress();

    } else if (event.type == sf::Event::MouseMoved) {
        if (m_rect.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
            m_mouseover = true;
        } else {
            m_mouseover = false;
        }
    }
}

void Textbox::SetText(const std::string& text)
{
    // top heavy/bottom heavy letter hack
    m_text.setString("I"); // choose top heavy string and save center
    float y_center = m_text.getLocalBounds().top + m_text.getLocalBounds().height / 2.f;
    // Set text
    m_text.setString(text);
    // Get bounds
    auto const& text_bounds  = m_text.getLocalBounds();
    auto const& shape_bounds = m_rect.getGlobalBounds();
    // Correct location to center
    m_text.setOrigin(text_bounds.left, y_center);
    m_text.setPosition(shape_bounds.left + m_margin, shape_bounds.top + shape_bounds.height / 2.f);
}

std::string Textbox::GetText() const
{
    return m_text.getString();
}

void Textbox::onKeyPress(const callback_type& f)
{
    m_keyPress = f;
}

void Textbox::Enabled(bool enabled)
{
    m_enabled = enabled;
    if (enabled) {
        m_text.setFillColor(sf::Color::Black);
    } else {
        m_text.setFillColor(sf::Color(100, 100, 100));
    }
}

bool Textbox::Enabled() const
{
    return m_enabled;
}

} // namespace mygui
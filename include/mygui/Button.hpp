#pragma once

#include "Object.hpp"

namespace mygui
{

class MYGUI_API Button : public Object, public ResourceManager
{

public:
    Button(int x, int y, const char* text, int w = 90, int h = 30, int character_size = 20);

    // Virtual Methods
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual void Handle(const sf::Event& event) override;

    void          Enabled(bool enabled) override;
    bool          Enabled() const override;
    void          SetText(const std::string& text);
    void          SetColor(const sf::Color& col);
    void          ResetColor();
    sf::FloatRect GetGlobalBounds();

    // Actions
    void OnClick(const callback_type& f);

private:
    const sf::Color m_idle_color{sf::Color(200, 200, 200)};

    sf::RectangleShape  m_idle_shape;
    sf::RectangleShape  m_pressed_shape;
    sf::RectangleShape  m_mouseover_shape;
    sf::RectangleShape* m_active_shape{nullptr};
    sf::Text            m_text;
    sf::Font            m_font;

    bool m_pressed{false};

    callback_type m_onClick{nullptr};
};

} // namespace mygui
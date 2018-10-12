#pragma once

#include "Object.hpp"

namespace mygui
{

class MYGUI_API Textbox : public Object
{

public:
    Textbox(int x, int y, const std::string& text = "", int w = 90, int h = 30, int character_size = 18, const char* font_name = "arial.ttf");

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual void Handle(const sf::Event& event) override;

    void        SetText(const std::string& text);
    std::string GetText() const;

    void Enabled(bool enabled) override;
    bool Enabled() const override;

    // Actions
    void onKeyPress(const callback_type& f);

private:
    static constexpr int m_margin{10};

    sf::RectangleShape m_rect;
    sf::Text           m_text;
    sf::Font           m_font;

    bool m_mouseover{false};

    callback_type m_keyPress{nullptr};
};

} // namespace mygui
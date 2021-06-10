#pragma once

#include "Object.hpp"

namespace mygui
{

class MYGUI_API Textbox : public Object
{

public:
    Textbox(int x, int y, const std::string& text = "", int w = 70, int h = 22, int character_size = 12);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual void Handle(const sf::Event& event) override;

    void        SetText(const std::string& text);
    std::string GetText() const;

    virtual void Enabled(bool enabled) override;
    // Unhide bool Object::Enabled()
    using Object::Enabled;

    virtual void Selected(bool selected) override;
    // Unhide bool Object::Enabled()
    using Object::Selected;

    // Actions
    void OnKeyPress(const callback_type& f);
    void OnEnterPress(const callback_type& f);

private:
    const int m_margin{5};

    sf::RectangleShape m_rect;
    sf::Text           m_text;
    sf::Font           m_font;

    bool m_mouseover{false};

    callback_type m_keyPress{nullptr};
    callback_type m_enterPress{nullptr};
};

} // namespace mygui
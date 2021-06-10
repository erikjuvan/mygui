#pragma once

#include "Object.hpp"

namespace mygui
{

class MYGUI_API Checkbox : public Object
{

public:
    Checkbox(int x, int y, std::string const& text = "", int w = 12, int h = 12, int character_size = 12);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual void Handle(const sf::Event& event) override;

    void Enabled(bool enabled) override;
    bool Enabled() const override;
    void Checked(bool checked);
    bool Checked() const;
    void SetText(const std::string& text);

    // Actions
    void OnClick(const callback_type& f);

private:
    sf::RectangleShape  m_rect_checked;
    sf::RectangleShape  m_rect_unchecked;
    sf::RectangleShape* m_rect{nullptr};
    sf::Text            m_text;
    sf::Font            m_font;

    bool m_pressed_in_focus{false};
    bool m_checked;

    callback_type m_onClick{nullptr};
};

} // namespace mygui
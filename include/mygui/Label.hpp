#pragma once

#include "Object.hpp"

namespace mygui
{

class MYGUI_API Label : public Object
{

public:
    Label(int x, int y, std::string const& text, int character_size = 12);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual void Handle(const sf::Event& event) override;

    void Enabled(bool enabled) override;
    bool Enabled() const override;

    void SetText(const std::string& text);

    // Actions
    void OnClick(const callback_type& f);

private:
    float m_x, m_y;

    sf::Text m_text;
    sf::Font m_font;

    callback_type m_onClick{nullptr};
};

} // namespace mygui
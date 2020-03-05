#pragma once

#include "Config.hpp"
#include <SFML/Graphics.hpp>
#include <functional>

namespace mygui
{

class MYGUI_API Object : public sf::Drawable
{
protected:
    using callback_type = std::function<void()>;

    bool m_enabled{true};
    bool m_selected{false};

public:
    virtual void Handle(const sf::Event& event) = 0;

    virtual void Enabled(bool enabled) { m_enabled = enabled; }
    virtual bool Enabled() const { return m_enabled; }

    virtual void Selected(bool selected) { m_selected = selected; }
    virtual bool Selected() const { return m_selected; }
};

} // namespace mygui
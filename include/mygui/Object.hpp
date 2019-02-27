#pragma once

#include "Config.hpp"
#include "ResourceManager.hpp"
#include <SFML/Graphics.hpp>
#include <functional>

namespace mygui
{

class MYGUI_API Object : public sf::Drawable
{
protected:
    using callback_type = std::function<void()>;

    bool m_enabled{true};

public:
    virtual void Handle(const sf::Event& event) = 0;

    virtual void Enabled(bool enabled) = 0;
    virtual bool Enabled() const       = 0;
};

} // namespace mygui
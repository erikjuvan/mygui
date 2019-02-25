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
    using ResManager    = const std::shared_ptr<ResourceManager>;

    bool       m_enabled{true};
    ResManager m_resource_manager;

public:
    Object(ResManager& rm) :
        m_resource_manager(rm) {}

    virtual void Handle(const sf::Event& event) = 0;

    virtual void Enabled(bool enabled) = 0;
    virtual bool Enabled() const       = 0;
};

} // namespace mygui
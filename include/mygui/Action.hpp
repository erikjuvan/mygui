#pragma once

#include "Object.hpp"

namespace mygui
{

class MYGUI_API Action : public Object
{

public:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual void Handle(const sf::Event& event) override;

    // Actions
    void DoAction(const callback_type& f);

private:
    callback_type m_doAction{nullptr};
};

} // namespace mygui
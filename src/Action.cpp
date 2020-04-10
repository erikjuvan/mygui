#include "Action.hpp"

namespace mygui
{
void Action::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (Enabled())
        m_doAction(); // weird to execute action in draw function, but Handle only gets called on events and so doesn't update on every Update call
}

void Action::Handle(const sf::Event& event)
{
}

void Action::DoAction(const callback_type& f)
{
    m_doAction = f;
}
} // namespace mygui
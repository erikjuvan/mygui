#pragma once

#include "Config.hpp"
#include <SFML/Graphics.hpp>

namespace mygui {

class MYGUI_API Object : public sf::Drawable {
public:
	virtual void Handle(const sf::Event& event) = 0;
};

}
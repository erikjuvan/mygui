#pragma once

#include <SFML/Graphics.hpp>

namespace mygui {

class Object : public sf::Drawable {
public:
	virtual void Handle(const sf::Event& event) = 0;
};

}
#pragma once

#include "Config.hpp"
#include <SFML/Graphics.hpp>

namespace mygui {

class MYGUI_API Object : public sf::Drawable {
protected:
	using fptr = void(*)();

	bool	m_enabled{ true };

public:
	virtual void Handle(const sf::Event& event) = 0;

	virtual void Enabled(bool enabled) = 0;
	virtual bool Enabled() const = 0;
};

}
#pragma once

#include "Object.hpp"

namespace mygui {

class Label : public Object {

	using fptr = void(*)(void*);

public:
	Label(int x, int y, const char* text, int character_size = 18, const char* font_name = "arial.ttf");

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void Handle(const sf::Event& event) override;

	void SetText(const std::string& text);

	// Actions
	void OnClick(void* vobj, const fptr& f);

private:
	sf::Text	m_text;
	sf::Font	m_font;

	fptr		m_onClick{ nullptr };
	void*		m_onClick_vobject{ nullptr };
};

}
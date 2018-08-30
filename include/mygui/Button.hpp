#pragma once

#include "Config.hpp"
#include "Object.hpp"

namespace mygui {

class MYGUI_API Button : public Object {

	using fptr = void(*)(void*);

public:
	Button(int x, int y, const char* text, int w = 90, int h = 30, int character_size = 20, const char* font_name = "arial.ttf");

	// Virtual Methods
	virtual void	draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void	Handle(const sf::Event& event) override;

	void			SetText(const std::string& text);
	void			SetColor(const sf::Color& col);
	void			ResetColor();
	sf::FloatRect	GetGlobalBounds();		
	
	// Actions
	void			OnClick(void* vobj, const fptr& f);

private:
	const sf::Color		m_idle_color{ sf::Color(200, 200, 200) };
	sf::RectangleShape	m_idle_shape;
	sf::RectangleShape	m_pressed_shape;
	sf::RectangleShape	m_mouseover_shape;
	sf::RectangleShape	*m_active_shape{ nullptr };
	sf::Text			m_text;
	sf::Font			m_font;
	bool				m_pressed{ false };
		
	fptr				m_onClick{ nullptr };
	void				*m_onClick_vobject{ nullptr };
};

}
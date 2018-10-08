#pragma once

#include "Object.hpp"

namespace mygui {

class MYGUI_API Checkbox : public Object {

public:
	Checkbox(int x, int y, const char* text = "", int w = 17, int h = 17, int character_size = 18, const char* font_name = "arial.ttf");

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void Handle(const sf::Event& event) override;

	void Enabled(bool enabled) override;
	bool Enabled() const override;
	void Checked(bool checked);
	bool Checked() const;	

	// Actions
	void OnClick(const fptr& f);	

private:
	static constexpr int m_margin{ 20 };

	sf::RectangleShape	m_rect_checked;
	sf::RectangleShape	m_rect_unchecked;
	sf::RectangleShape	* m_rect{ nullptr };	
	sf::Text			m_text;
	sf::Font			m_font;	

	bool				m_pressed_in_focus{ false };
	bool				m_checked;

	fptr				m_onClick{ nullptr };
};

}
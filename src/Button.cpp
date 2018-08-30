#pragma once

#include "Button.hpp"

namespace mygui {

Button::Button(int x, int y, const char* text, int w , int h, int character_size , const char* font_name) :
	m_idle_shape(sf::Vector2f(static_cast<float>(w), static_cast<float>(h))), m_pressed_shape(m_idle_shape), m_pressed(false) {

	m_idle_shape.setPosition(static_cast<float>(x), static_cast<float>(y));
	m_idle_shape.setFillColor(m_idle_color);
	m_idle_shape.setOutlineColor(sf::Color::Black);
	m_idle_shape.setOutlineThickness(1.f);

	m_pressed_shape.setPosition(static_cast<float>(x), static_cast<float>(y));
	m_pressed_shape.setFillColor(sf::Color(200, 230, 235));
	m_pressed_shape.setOutlineColor(sf::Color::Black);
	m_pressed_shape.setOutlineThickness(1.f);
	
	m_mouseover_shape.setPosition(static_cast<float>(x), static_cast<float>(y));
	m_mouseover_shape.setFillColor(sf::Color(215, 240, 245));
	m_mouseover_shape.setOutlineColor(sf::Color::Black);
	m_mouseover_shape.setOutlineThickness(1.f);

	m_active_shape = &m_idle_shape;

	m_font.loadFromFile(font_name);
	m_text.setFont(m_font);
	m_text.setCharacterSize(character_size);
	m_text.setFillColor(sf::Color::Black);
	SetText(text);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(*m_active_shape, states);
	target.draw(m_text, states);
}

void Button::SetText(const std::string& text) {
	m_text.setString(text);

	float tx = m_text.getLocalBounds().left;
	float tw = m_text.getLocalBounds().width;
	float ty = m_text.getLocalBounds().top;
	float th = m_text.getLocalBounds().height;

	float x = m_idle_shape.getGlobalBounds().left;
	float w = m_idle_shape.getGlobalBounds().width;
	float y = m_idle_shape.getGlobalBounds().top;
	float h = m_idle_shape.getGlobalBounds().height;

	m_text.setOrigin(tx + tw / 2.0f, ty + th / 2.0f);
	m_text.setPosition(x + w / 2.0f, y + h / 2.0f);
}

sf::FloatRect Button::GetGlobalBounds() {
	return m_idle_shape.getGlobalBounds();
}

void Button::SetColor(const sf::Color& col) {
	m_idle_shape.setFillColor(col);
}

void Button::ResetColor() {
	m_idle_shape.setFillColor(m_idle_color);
}

void Button::Handle(const sf::Event& event) {

	if (m_active_shape->getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			m_active_shape = &m_pressed_shape;
			m_pressed = true;
		}
		else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
			m_active_shape = &m_idle_shape;
			if (m_onClick && m_pressed) m_onClick(m_onClick_vobject);
			m_pressed = false;
		}
	}
	else {
		if (m_active_shape == &m_pressed_shape && event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
			m_active_shape = &m_idle_shape;
			m_pressed = false;
		}
	}
}

void Button::OnClick(void* vobj, const fptr& f) {
	m_onClick = f;
	m_onClick_vobject = vobj;
}

}
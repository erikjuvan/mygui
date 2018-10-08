#include "Checkbox.hpp"

namespace mygui {

Checkbox::Checkbox(int x, int y, const char* text, int w, int h, int character_size, const char* font_name) :
	m_rect_checked(sf::Vector2f(static_cast<float>(w), static_cast<float>(h))),
	m_rect_unchecked(m_rect_checked), m_checked(false) {


	m_rect_checked.setPosition(static_cast<float>(x), static_cast<float>(y));
	m_rect_checked.setFillColor(sf::Color::Black);
	m_rect_checked.setOutlineColor(sf::Color::Black);
	m_rect_checked.setOutlineThickness(1.f);

	m_rect_unchecked.setPosition(static_cast<float>(x), static_cast<float>(y));
	m_rect_unchecked.setFillColor(sf::Color::White);
	m_rect_unchecked.setOutlineColor(sf::Color::Black);
	m_rect_unchecked.setOutlineThickness(1.f);

	m_rect = &m_rect_unchecked;

	m_font.loadFromFile(font_name);
	m_text.setFont(m_font);
	m_text.setString(text);
	m_text.setCharacterSize(character_size);
	sf::FloatRect text_pos = m_text.getGlobalBounds();
	m_text.setPosition(x + w + m_margin / 2.f, y - 2.f);
	m_text.setFillColor(sf::Color::Black);
}

void Checkbox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(*m_rect);
	target.draw(m_text);
}

void Checkbox::Handle(const sf::Event& event) {
	if (!Enabled()) return;

	if (m_rect->getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			m_pressed_in_focus = true;
		}
		else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
			if (m_pressed_in_focus) {
				if (!m_checked) {
					m_rect = &m_rect_checked;
					m_checked = true;
				}
				else {
					m_rect = &m_rect_unchecked;
					m_checked = false;
				}

				if (m_onClick != nullptr)
					m_onClick();

				m_pressed_in_focus = false;
			}
		}
	}
	else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
		m_pressed_in_focus = false;
	}
}

// Actions
void Checkbox::OnClick(const fptr& f) {
	m_onClick = f;
}

bool Checkbox::Checked() const {
	return m_checked;
}

void Checkbox::Checked(bool checked) {
	m_checked = checked;
	if (checked) {
		m_rect = &m_rect_checked;
	}
	else {
		m_rect = &m_rect_unchecked;
	}
}

void Checkbox::Enabled(bool enabled) {
	m_enabled = enabled;
	if (enabled) {
		m_text.setFillColor(sf::Color::Black);
	}
	else {
		m_text.setFillColor(sf::Color(100, 100, 100));
	}
}

bool Checkbox::Enabled() const {
	return m_enabled;
}

}
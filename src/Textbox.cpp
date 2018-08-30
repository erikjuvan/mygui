#include "Textbox.hpp"

namespace mygui {

Textbox::Textbox(int x, int y, const std::string& text, int w, int h, int character_size, const char* font_name) : 
	m_rect(sf::Vector2f(static_cast<float>(w), static_cast<float>(h))) {

	m_rect.setPosition(static_cast<float>(x), static_cast<float>(y));
	m_rect.setFillColor(sf::Color::White);
	m_rect.setOutlineColor(sf::Color::Black);
	m_rect.setOutlineThickness(1.f);

	m_font.loadFromFile(font_name);
	m_text.setFont(m_font);
	m_text.setString(text);
	m_text.setCharacterSize(character_size);
	m_text.setFillColor(sf::Color::Black);

	float tx = m_text.getLocalBounds().left;
	float tw = m_text.getLocalBounds().width;
	float ty = m_text.getLocalBounds().top;
	float th = m_text.getLocalBounds().height;

	m_text.setOrigin(tx, ty + th / 2.0f);
	m_text.setPosition(x + m_margin, y + m_rect.getLocalBounds().height / 2.0f);
}

void Textbox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_rect);
	target.draw(m_text);
}

void Textbox::Handle(const sf::Event& event) {
	if (event.type == sf::Event::TextEntered && m_mouseover) {

		std::string str = m_text.getString();

		if (event.text.unicode == '\b') {
			if (str.length() > 0) str.pop_back();
		}
		else {
			str += event.text.unicode;
		}

		// temporary text to see if the added character is too long to fit into the textbox
		sf::Text txt(m_text);
		txt.setString(str);

		if (txt.getGlobalBounds().width < (m_rect.getGlobalBounds().width - m_margin))
			m_text.setString(str);
	}
	else if (event.type == sf::Event::MouseMoved) {
		if (m_rect.getGlobalBounds().contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y))) {
			m_mouseover = true;
		}
		else {
			m_mouseover = false;
		}
	}
}

void Textbox::SetText(const std::string& text) {
	m_text.setString(text);
}

std::string Textbox::GetText() const {
	return m_text.getString();
}

void Textbox::onKeyPress(const fptr& f) {
	m_keyPress = f;
}

}
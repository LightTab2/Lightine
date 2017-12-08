#pragma once
#include <SFML/Graphics.hpp>
#include <memory>


struct CustomTextWithFont
{
	CustomTextWithFont(sf::Text &&text) : t(text) {
		afactor = t.getFillColor().a / 255.f; sf::Color color = t.getFillColor(); t.setFillColor(color);
	}
	CustomTextWithFont(const sf::Text &text) : t(text) {
		afactor = t.getFillColor().a / 255.f; sf::Color color = t.getFillColor(); t.setFillColor(color);
	}
	sf::Text t;
	float afactor;
	std::shared_ptr<sf::Font> font;
};
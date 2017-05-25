#pragma once
#include "Stat.h"

struct TypeBox
{
	TypeBox(std::wstring *s) : s(s) { t.setString(*s); }
	sf::RectangleShape rt;
	std::wstring *s;
	sf::Text t;
};
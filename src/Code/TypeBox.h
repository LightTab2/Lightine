#pragma once
#include "Stat.h"

struct TypeBox
{
	TypeBox(std::wstring *s, std::pair<unsigned, unsigned> limits, int minchars) : s(s), limits(limits), minchars(minchars)  { t.setString(*s); }
	sf::RectangleShape rt;
	std::wstring *s;
	sf::Text t;
	std::pair<unsigned, unsigned> limits;
	int minchars = 0;
	bool InsertChar(wchar_t c)
	{
		s->push_back(c);
		t.setString(*s);
		if ((t.getGlobalBounds().left + t.getLocalBounds().left + t.getGlobalBounds().width) > (rt.getGlobalBounds().left + rt.getGlobalBounds().width - rt.getOutlineThickness()))
		{
			if (limits.second == 0U || (static_cast<unsigned>(count(s->begin(), s->end(), L'\n') + 1) < limits.second) )
			{
				s->insert(s->end() - 1, L'\n');
				t.setString(*s);
				return true;
			}
			else
			{
				s->pop_back();
				t.setString(*s);
			}
		}
		return false;
	}
	bool DeleteChar()
	{
		if (s->size() != 0U)
		{
			s->pop_back();
			if (s->size() != 0U && *(s->end() - 1) == L'\n') {
				s->pop_back();
				t.setString(*s);
				return true;
			}
			t.setString(*s);
		}
		return false;
	}
};
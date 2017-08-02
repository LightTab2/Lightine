#pragma once
#include "Stat.h"

struct TypeBox
{
<<<<<<< HEAD
	TypeBox(std::wstring *s, std::pair<unsigned, unsigned> limits, int minchars) : s(s), limits(limits), minchars(minchars)  { t.setString(*s); }
=======
	TypeBox(std::wstring *s, std::pair<unsigned, unsigned> limits) : s(s), limits(limits)  { t.setString(*s); }
>>>>>>> 962c618769e951108e54dadcdc7dac935fcb7185
	sf::RectangleShape rt;
	std::wstring *s;
	sf::Text t;
	std::pair<unsigned, unsigned> limits;
<<<<<<< HEAD
	int minchars = 0;
	bool InsertChar(wchar_t c)
	{
=======
	bool InsertChar(wchar_t c)
	{
		if ((limits.first != 0U && s->size() >= limits.first) || !(c > 31U && c < 127U)) return false;
>>>>>>> 962c618769e951108e54dadcdc7dac935fcb7185
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
<<<<<<< HEAD
	}
=======
	};
>>>>>>> 962c618769e951108e54dadcdc7dac935fcb7185
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
<<<<<<< HEAD
	}
=======
	};
>>>>>>> 962c618769e951108e54dadcdc7dac935fcb7185
};
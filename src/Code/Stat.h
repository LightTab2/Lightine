/*
@Author: LightTab2
The MIT License(MIT)

Copyright(c) 2016 LightTab2 azorro12@gmail.com
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and / or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#pragma once
#include "Exceptions.h"
#include <SFML/Graphics.hpp>

extern unsigned int priorlimit;												//Prior mechanizm is used to order all Stats

struct Stat																	//Stats that changes hero over game, you can see not-hidden ones in gamestate -1
{
	std::wstring name;														//Name; identificator
	bool hidden;															//If true - it won't show in gamestate -1
	//unsigned int prior;														//Prior mechanizm is used to order all Stats
	bool operator<(const Stat &cmp) const{
		return this->name < cmp.name;
	};
protected:
	Stat(std::wstring &name, const bool hidden/*, const unsigned int prior*/)
		: name(name), hidden(hidden)/*, prior(prior > priorlimit ? priorlimit : prior)*/ {}
};

struct IStat
{
	int value;
protected:
	IStat(int value) : value(value) {}
	IStat() : value(0) {}
};

struct SStat
{
	std::wstring value;
protected:
	SStat(std::wstring &value) : value(value) {}
	SStat() {}
};

class IntStat : public Stat, public IStat									//Indicates in % how much you've gained something
{
public:
	IntStat(std::wstring &name, const int value, const int max, const int min, const bool hidden)
		: Stat(name, hidden), IStat(value), max(max), min(min)
	{
		if (max == min) throw w_err(L"IntStat with name \"" + name + L"\" has maximum value equals minimum one, there's no purpose for this stat to exist. Use Int instead");
		else if (max < min) throw w_err(L"IntStat with name \"" + name + L"\" has maximum value lesser than minimum one.");
	}
	void setSprite(const sf::Image &img)
	{
		tx.loadFromImage(img);
		s.setTexture(tx);
	}
	int max;																//Maximum value
	int min;																//Minimum value
	sf::Vector2i pos[2];
	sf::Text t;																//These three below are displayed in show_stats
	sf::Sprite s;
private:
	sf::Texture tx;
};

class IntStatOpposite : public Stat, public IStat								//Indicates in % how much you've gained something and another thing (while one increases, another decreases)
{
public:
	IntStatOpposite(std::wstring &name, const int value, const int max, const int min, const int threshold, const bool hidden, std::wstring &opposite)
		: Stat(name, hidden), IStat(value), max(max), min(min), threshold(threshold), opposite(opposite)
	{
		if (max == min) throw w_err(L"IntStatOpposite with name \"" + name + L"\" has maximum value equals minimum one, there's no purpose for this stat to exist. Use Int instead");
		else if (max < min) throw w_err(L"IntStatOpposite with name \"" + name + L"\" has maximum value lesser than minimum one.");
	}
	void setSprite(const sf::Image &img)
	{
		tx.loadFromImage(img);
		s.setTexture(tx);
	}
	int max;																//Maximum value
	int min;																//Minimum value
	int threshold;															//When you become more aligned to "name" or "opposite" (lower - name, higher - opposite)
	std::wstring opposite;													//Eg. you can be Evil or Good, when threshold is -100 all numbers(higher or equal than min, lesser or equal than max) below are Evil and all above Good
	sf::Vector2i pos[4];
	sf::Text t[3];															//These three below are displayed in show_stats
	sf::Sprite s;
private:
	sf::Texture tx;
};

struct Int : public Stat, public IStat
{
	Int(std::wstring &name, const int value, const bool hidden)
		: Stat(name, hidden), IStat(value) {}
	sf::Vector2i pos;
	sf::Text t;																//This is displayed in show_stats
};

struct StringStat : public Stat, public SStat								//Stat that's value is a string, eg. pseudonim of the hero
{
	StringStat(std::wstring &name, std::wstring &value, const bool namehidden, const bool valuehidden)
		: Stat(name, namehidden), SStat(value), vhidden(valuehidden) {}
	bool vhidden;															//Might be usefull sometimes... hides value leaving only name
	sf::Vector2i pos;
	sf::Text t;
};

struct StcString : public SStat
{
	StcString(std::wstring &name, std::wstring &value) : name(name), SStat(value) {}
	std::wstring name;
};

struct StcInt : public IStat
{
	StcInt(std::wstring &name, const int value) : name(name), IStat(value) {}
	std::wstring name;
};
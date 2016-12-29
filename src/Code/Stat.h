/*
@Author: LightTab2
The MIT License(MIT)

Copyright(c) 2016 LightTab2 azorro12@gmail.com
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and / or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#pragma once
#include <string>
extern unsigned int priorlimit;														//Prior mechanizm is used to order all Stats

class Stat																	//Stats that changes hero over game, you can see not-hidden ones in gamestate -1
{
public:
																			//Changes hidden option
	void SetHidden(bool sethidden)
	{
		hidden = sethidden;
	}
	std::wstring name;														//Name; identificator
	bool hidden;															//If true - it won't show in gamestate -1
	bool read = false;														//When acquiring all object of this type and processing them it might save a lot of time
	unsigned int prior;														//Prior mechanizm is used to order all Stats
	unsigned int address;													//Indicates which index is needed to change this stat in s_pos or v_pos
};

class IntStat : public Stat													//Indicates in % how much you've gained something
{
public:
	IntStat(std::wstring &setname, int setvalue, int setmax, int setminimum, bool sethidden, unsigned int setprior)
	{
		name = setname;
		value = setvalue;
		max = setmax;
		min = setminimum;
		hidden = sethidden;
		if (setprior > priorlimit) prior = priorlimit;
		else prior = setprior;
		if (setmax == setminimum) throw std::runtime_error("Maximum value equals minimum one, there's no purpose for this stat to exist. Use Int instead");
		else if (setmax < setminimum) throw std::runtime_error("Maximum value lesser than minimum one. Unable to render such variable");
	}
	int value;																//Value
	int max;																//Maximum value
	int min;																//Minimum value
};

class IntStatOpposite : public Stat											//Indicates in % how much you've gained something and another thing (while one increases, another decreases)
{
public:
	IntStatOpposite(std::wstring &setname, int setvalue, int setmax, int setminimum, int setthreshold, bool sethidden, unsigned int setprior, std::wstring &setopposite) //konwersja jawna
	{
		name = setname;
		value = setvalue;
		max = setmax;
		min = setminimum;
		threshold = setthreshold;
		hidden = sethidden;
		if (setprior > priorlimit) prior = priorlimit;
		else prior = setprior;
		opposite = setopposite;
		if (setmax == setminimum) throw std::runtime_error("Maximum value equals minimum one, there's no purpose for this stat to exist. Use Int instead");
		else if (setmax < setminimum) throw std::runtime_error("Maximum value lesser than minimum one. Unable to render such variable");
	}
	int value;																//Value
	int max;																//Maximum value
	int min;																//Minimum value
	int threshold;															//When you become more aligned to "name" or "opposite" (lower - name, higher - opposite)
	std::wstring opposite;													//Eg. you can be Evil or Good, when threshold is -100 all numbers below are Evil and all above Good
};

class Int : public Stat
{
public:
	Int(std::wstring &setname, int setvalue, bool sethidden, unsigned int setprior)
	{
		name = setname;
		value = setvalue;
		hidden = sethidden;
		if (setprior > priorlimit) prior = priorlimit;
		else prior = setprior;
	}
	std::wstring name;														//Name; identificator
	int value;																//Value
};


class StringStat : public Stat												//Stat that's value is a string, eg. pseudonim of the hero
{
public:
	explicit StringStat(std::wstring &setname, std::wstring &setvalue, bool setnamehidden, bool setvaluehidden, unsigned int setprior)
	{
		name = setname;
		value = setvalue;
		hidden = setnamehidden;
		vhidden = setvaluehidden;
		if (setprior > priorlimit) prior = priorlimit;
		else prior = setprior;
	}
	std::wstring value;														//Value
	bool vhidden = false;													//Might be usefull sometimes... hides value leaving only name
};
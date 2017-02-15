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

class CustImg																//Custom image that can be drawn by story writer
{
	CustImg(sf::Vector2f pos, sf::Texture text, sf::Sprite sprite) : pos(pos), text(text), sprite(sprite) {};
public:
	sf::Vector2f pos;														//Position of the image
	sf::Texture text;														//Texture of the image
	sf::Sprite sprite;														//Sprite of the image
	int lifetime;															//How long does it "live" after it hit its lifeline
	int fadetime;															//How long does it fade away
	int lifeline;															//Used in check (after every Parse()) if sgoto is higher than it, if true - creates lifeclock
	std::unique_ptr<sf::Clock> lifeclock;									//When created, exist lifetime long (in microseconds)
};
/*
@Author: LightTab2
The MIT License(MIT)

Copyright(c) 2016 LightTab2 azorro12@gmail.com
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and / or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "Cmain.h"
#include <limits>
#include <codecvt>
#include <cstdlib>

void Cmain::onTick()
{
	window.draw(Background);
	if (stigger)
	{
		if (sliders.getPosition().y + smouseposy != window.mapCoordsToPixel(mousepos).y)
		{
			sviewchange(static_cast<float>(sf::Mouse::getPosition(window).y - smouseposy));
		}
	}
}

void Cmain::sviewchange(float setPos)
{
	if (setPos + static_cast<int>(sliders.getGlobalBounds().height) > smaxdown) setPos = round(smaxdown - sliders.getGlobalBounds().height);
	else if (setPos < smaxup) setPos = static_cast<float>(smaxup);
	if (gamestate != -1) numbss = static_cast<int>(round(scenario.the - h) * (setPos - smaxup) / smax);
	else numbss = static_cast<int>((scenario.she - h) * (setPos - smaxup) / smax);
	window.setView(sf::View(sf::Vector2f(window.getDefaultView().getCenter().x, round(h / 2.f + numbss)), sf::Vector2f(static_cast<float>(w), static_cast<float>(h))));
	sliders.setPosition(window.mapPixelToCoords(sf::Vector2i(static_cast<int>(sliders.getPosition().x), static_cast<int>(setPos))));
	bars.setPosition(window.mapPixelToCoords(sf::Vector2i(w - static_cast<int>(bars.getGlobalBounds().width), 0)));
	for (IntStat& i : scenario.i_stats)
	{
		i.t.setPosition(window.mapPixelToCoords(i.pos[0]));
		i.s.setPosition(window.mapPixelToCoords(i.pos[1]));
	}
	for (IntStatOpposite& o : scenario.io_stats)
	{
		o.t[0].setPosition(window.mapPixelToCoords(o.pos[0]));
		o.t[1].setPosition(window.mapPixelToCoords(o.pos[1]));
		o.t[2].setPosition(window.mapPixelToCoords(o.pos[2]));
		o.s.setPosition(window.mapPixelToCoords(o.pos[3]));
	}
	for (Int& I : scenario.Ints) I.t.setPosition(window.mapPixelToCoords(I.pos));
	for (StringStat& s : scenario.s_stats) s.t.setPosition(window.mapPixelToCoords(s.pos));
	button_1_text.setPosition(window.mapPixelToCoords(pos[0]));
	button_2_text.setPosition(window.mapPixelToCoords(pos[1]));
	button_3_text.setPosition(window.mapPixelToCoords(pos[2]));
	profilesmenu.setPosition(window.mapPixelToCoords(pos[3]));
	f14_text.setPosition(window.mapPixelToCoords(pos[4]));
	help_text.setPosition(window.mapPixelToCoords(pos[5]));
	arrowup.setPosition(window.mapPixelToCoords(pos[6]));
	arrowdn.setPosition(window.mapPixelToCoords(pos[7]));
	ctext.setPosition(window.mapPixelToCoords(pos[8]));
	enternewerror_t.setPosition(window.mapPixelToCoords(pos[9]));
	newname.setPosition(window.mapPixelToCoords(pos[10]));
	ntext.setPosition(window.mapPixelToCoords(pos[11]));
	showstats.setPosition(window.mapPixelToCoords(pos[12]));
	resbutton1_text.setPosition(window.mapPixelToCoords(pos[13]));
	resbutton1_shape.setPosition(window.mapPixelToCoords(pos[14]));
	resbutton2_text.setPosition(window.mapPixelToCoords(pos[15]));
	resbutton2_shape.setPosition(window.mapPixelToCoords(pos[16]));
	resets.setPosition(window.mapPixelToCoords(pos[17]));

	Background.setPosition(window.mapPixelToCoords(sf::Vector2i(0,0)));
	michaupase³ke³.setPosition(window.mapPixelToCoords(sf::Vector2i(0,0)));

	button_1 = button_1_text.getGlobalBounds();
	button_2 = button_2_text.getGlobalBounds();
	button_3 = button_3_text.getGlobalBounds();
	slidersb = sliders.getGlobalBounds();
	arrowdn_b = arrowdn.getGlobalBounds();
	arrowup_b = arrowup.getGlobalBounds();
	resbutton1 = resbutton1_shape.getGlobalBounds();
	resbutton2 = resbutton2_shape.getGlobalBounds();
	shwstats = showstats.getGlobalBounds();
	resets_b = resets.getGlobalBounds();
	if (gamestate != -1) lsetPos = setPos;
	else ssetPos = setPos;
}
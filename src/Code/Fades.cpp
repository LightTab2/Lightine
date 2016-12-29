/*
@Author: LightTab2
The MIT License(MIT)

Copyright(c) 2016 LightTab2 azorro12@gmail.com
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and / or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "Cmain.h"
sf::Color color1(static_cast<sf::Uint8>(255), static_cast<sf::Uint8>(255), static_cast<sf::Uint8>(255), static_cast<sf::Uint8>(0));
sf::Color color67(static_cast<sf::Uint8>(255), static_cast<sf::Uint8>(255), static_cast<sf::Uint8>(255), static_cast<sf::Uint8>(0));
sf::Color colorminus1(static_cast<sf::Uint8>(255), static_cast<sf::Uint8>(255), static_cast<sf::Uint8>(255), static_cast<sf::Uint8>(0));

void Cmain::Reset() //this function is here, because it needs to change colorminus1
{
	scenario.additional.clear();
	scenario.choice.clear();
	scenario.the = h / 12;

	scenario.sgoto = 0;
	std::wofstream save(L"bin/Saves/" + profiles[selectionp].getString().toWideString() + L"_" + stories[selections].getString().toWideString() + L".txt", std::ios::trunc);
	scenario.loadtextonly = false;
	LoadSave();
	resetsb = false;
	scenario.choicesel = -1;
	colorminus1.a = 0;
	statcolor.a = colorminus1.a;
	resets.setColor(colorminus1);
	for (auto &v : v_pos) v.setColor(statcolor);
	for (auto &s : s_pos) s.setFillColor(colorminus1);
}

inline void Cmain::Manage67(bool add) //this code could've been better in aspect of transparency, but performance is the prior here
{
	if (add)
	{
		Draw67();
		if (visible) return;
		if (color67.a > static_cast<sf::Uint8>(253)) color67.a = static_cast<sf::Uint8>(255);
		else
			color67.a += 2;
	}
	else
	{
		if (visible) return;
		Draw67();
		if (color67.a < static_cast<sf::Uint8>(3)) color67.a = static_cast<sf::Uint8>(0);
		else
			color67.a -= 2;
	}
	menuprofilesmenuoutlinecolor.a = color67.a;
	menuprofilesmenufillcolor.a = static_cast<sf::Uint8>(color67.a * profilesmenufillfactor);
	if (gwhich)
	{
		menustoriescolor.a = menustoriesselectcolor.a = color67.a;
		for (unsigned int index = 0U, size = stories.size(); index < size; ++index) {
			if (selections == index) stories[index].setFillColor(menustoriesselectcolor);
			else stories[index].setFillColor(menustoriescolor);
		}
	}
	else
	{
		menuprofilescolor.a = menuprofilesselectcolor.a = color67.a;
		for (unsigned int index = 0U, size = profiles.size(); index < size; ++index) {
			if (selectionp == index) profiles[index].setFillColor(menuprofilesselectcolor);
			else profiles[index].setFillColor(menuprofilescolor);
		}
	}
	profilesmenu.setOutlineColor(menuprofilesmenuoutlinecolor);
	profilesmenu.setFillColor(menuprofilesmenufillcolor);
	arrowdn.setColor(sf::Color(static_cast<sf::Uint8>(255), static_cast<sf::Uint8>(255), static_cast<sf::Uint8>(255), static_cast<sf::Uint8>(color67.a * (arrowed_dn ? 0.35 : 1))));
	arrowup.setColor(sf::Color(static_cast<sf::Uint8>(255), static_cast<sf::Uint8>(255), static_cast<sf::Uint8>(255), static_cast<sf::Uint8>(color67.a * (arrowed_up ? 0.35 : 1))));
}

inline void Cmain::Manage1(bool add)
{
	if (add)
	{
		Draw1();
		if (visible) return;
		if (color1.a > static_cast<sf::Uint8>(253))
			color1.a = static_cast<sf::Uint8>(255);
		else color1.a += 2;
	}
	else
	{
		if (visible) return;
		Draw1();
		if (color1.a < static_cast<sf::Uint8>(3)) color1.a = static_cast<sf::Uint8>(0);
		else color1.a -= 2;
	}
	textcolor.a = textchoicecolor.a = textchoiceunavaiblecolor.a = color1.a;
	textchoicefillcolor.a = static_cast<sf::Uint8>(choicefactor * color1.a);
	showstats.setColor(color1);
	sliders.setColor(color1);
	bars.setColor(color1);
	for (unsigned int index = 0U, size = scenario.choice.size(); index < size; ++index)
	{
		Choice &c = scenario.choice[index];
		if (!c.avaible && c.hidden) continue;
		if (c.avaible)
		{
			if (index == scenario.choicesel) c.cs.setFillColor(textchoicefillcolor);
			c.cs.setOutlineColor(textchoicecolor);
			c.c.setOutlineColor(textchoicecolor);
			for (sf::Text &t : c.text)
			{
				t.setFillColor(textchoicecolor);
			}
		}
		else
		{
			c.cs.setOutlineColor(textchoiceunavaiblecolor);
			c.c.setOutlineColor(textchoiceunavaiblecolor);
			for (sf::Text &t : c.text)
			{
				t.setFillColor(textchoiceunavaiblecolor);
			}
		}
	}
	scenario.next.setColor(color1);
	for (auto &a : scenario.additional) a.setFillColor(textcolor);
}

inline void Cmain::Manageminus1(bool add)
{
	if (add)
	{
		Drawminus1();
		if (visible) return;
		if (colorminus1.a > static_cast<sf::Uint8>(253))
			colorminus1.a = static_cast<sf::Uint8>(255);
		else
			colorminus1.a += 2;
	}
	else
	{
		if (visible) return;
		Drawminus1();
		if (colorminus1.a < static_cast<sf::Uint8>(3))
			colorminus1.a = static_cast<sf::Uint8>(0);
		else
			colorminus1.a -= 2;
	}
	statcolor.a = colorminus1.a;
	resets.setColor(colorminus1);
	for (auto &v : v_pos) v.setColor(statcolor);
	for (auto &s : s_pos) s.setFillColor(colorminus1);
}

inline void Cmain::Draw67()
{
	if (k_delete || enternew) return;
	if (gwhich)
	{
		for (unsigned int x = 0, size = stories.size(); x < size && x < menucapacity; x++)
			window.draw(stories[arroweds + x]);
	}
	else
	{
		for (unsigned int x = 0, size = profiles.size(); x < size && x < menucapacity; x++)
			window.draw(profiles[arrowedp + x]);
	}
	window.draw(arrowdn);
	window.draw(arrowup);
	window.draw(profilesmenu);
}

inline void Cmain::Draw1()
{
	for (auto &s : scenario.additional)
		window.draw(s);
	for (const auto &c : scenario.choice)
	{
		if (!c.avaible && c.hidden) continue;
		for (auto &t : c.text) window.draw(t);
		window.draw(c.c);
		window.draw(c.cs);
	}
	window.draw(michaupase³ke³);
	if (scenario.drawnext) window.draw(scenario.next);
	if (!scenario.additional.empty() && !scenario.pempty && !scenario.sempty) window.draw(showstats);
	if (scenario.slideratv) {
		window.draw(bars);
		window.draw(sliders);
	}
}

inline void Cmain::Drawminus1()
{
	if (resetsb)
	{
		window.draw(button_2_text);
		window.draw(button_3_text);
		return;
	}
	for (auto &v : v_pos) window.draw(v);
	for (auto &s : s_pos) window.draw(s);
	window.draw(resets);
}

void Cmain::PrepareMenu()
{
	switch (gamestate)
	{
	case -1:
		Manage1(false);
		Manage67(false);
		Manageminus1(true);
		if (!visible) visible = (color1.a == static_cast<sf::Uint8>(0) && color67.a == static_cast<sf::Uint8>(0) && colorminus1.a == static_cast<sf::Uint8>(255));
		break;
	case 1:
		Manage67(false);
		Manage1(true);
		Manageminus1(false);
		if (!visible) visible = (color1.a == static_cast<sf::Uint8>(255) && color67.a == static_cast<sf::Uint8>(0) && colorminus1.a == static_cast<sf::Uint8>(0));
		break;
	default:
		if (gamestate == 6 || gamestate == 7) {
			setupMenu();
			Manage1(false);
			Manageminus1(false);
			Manage67(true);
			if (!enternew) {
				if (k_delete) window.draw(ctext);
				else window.draw(help_text);
			}
			else
			{
				if (enternewerror)
				{
					window.draw(enternewerror_t);
					if (errclock.getElapsedTime().asMilliseconds() > 1500)
					{
						menuerrorcolor.a -= 1;
						enternewerror_t.setFillColor(menuerrorcolor);
						if (menuerrorcolor.a == static_cast<sf::Uint8>(0))
						{
							enternewerror = false;
						}
					}
				}
				window.draw(ntext);
				window.draw(newname);
			}
			window.draw(button_2_text);
			window.draw(button_3_text);
			if (!visible) visible = (color1.a == static_cast<sf::Uint8>(0) && color67.a == static_cast<sf::Uint8>(255) && colorminus1.a == static_cast<sf::Uint8>(0));
			return;
		}
		Manage1(false);
		Manage67(false);
		Manageminus1(false);
		window.draw(f14_text);
		if (gamestate != 3) {
			window.draw(button_1_text);
		}
		else
		{
			window.draw(resbutton1_text); window.draw(resbutton2_text); window.draw(resbutton1_shape); window.draw(resbutton2_shape);
			if (fullscreen) {
				resbutton1_shape.setFillColor(menuwidthffillcolor);
				resbutton2_shape.setFillColor(menuheightffillcolor);
			}
			else {
				if (resbutton1_focus) resbutton1_shape.setFillColor(menuwidthsfillcolor);
				else resbutton1_shape.setFillColor(menuwidthfillcolor);
				if (resbutton2_focus) resbutton2_shape.setFillColor(menuheightsfillcolor);
				else resbutton2_shape.setFillColor(menuheightfillcolor);
			}
		}
		window.draw(button_2_text);
		window.draw(button_3_text);
		if (!visible) visible = (color1.a == static_cast<sf::Uint8>(0) && color67.a == static_cast<sf::Uint8>(0) && colorminus1.a == static_cast<sf::Uint8>(0));
		break;
	}
}

/*
@Author: LightTab2
The MIT License(MIT)

Copyright(c) 2016 LightTab2 azorro12@gmail.com
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and / or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "Cmain.h"
sf::Color color1(255, 255, 255, 0);
sf::Color color67(255, 255, 255, 0);
sf::Color colorminus1(255, 255, 255, 0);

void Cmain::Reset() //this function is here, because it needs to change colorminus1
{
	scenario.text.setString(L"");
	scenario.choice.clear();
	scenario.cgoto = scenario.sgoto = scenario.dgoto = 0;
	std::wofstream save(L"../../bin/Saves/" + profiles[selectionp].getString().toWideString() + L"_" + stories[selections].getString().toWideString() + L".txt");
	scenario.loadtextonly = false;
	LoadSave();
	resetsb = false;
	scenario.choicesel = -1;
	colorminus1.a = 0;
	resets.setColor(colorminus1);
	sf::Color c = textcolor;
	c.a = colorminus1.a;
	scenario.statcolor.a = colorminus1.a;
	lsetPos = static_cast<float>(smaxup);
	for (auto &i : scenario.i_stats)
	{
		i.t.setFillColor(scenario.statcolor);
		i.s.setColor(colorminus1);
	}
	for (auto &o : scenario.io_stats)
	{
		for (auto &t : o.t) t.setFillColor(scenario.statcolor);
		o.s.setColor(colorminus1);
	}
	for (auto &i : scenario.Ints)
	{
		i.t.setFillColor(c);
	}
	for (auto &s : scenario.s_stats)
	{
		s.t.setFillColor(c);
	}
	//could've done at manageminus1: if (colorminus1.a != 0) Drawminus1(); But performance...
}

inline void Cmain::Manage67(const bool add) //this code could've been better in aspect of transparency, but performance is the prior here
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
		for (size_t index = 0U ; index != stories.size(); ++index) {
			if (selections == index) stories[index].setFillColor(menustoriesselectcolor);
			else stories[index].setFillColor(menustoriescolor);
		}
	}
	else
	{
		menuprofilescolor.a = menuprofilesselectcolor.a = color67.a;
		for (size_t index = 0U; index != profiles.size(); ++index) {
			if (selectionp == index) profiles[index].setFillColor(menuprofilesselectcolor);
			else profiles[index].setFillColor(menuprofilescolor);
		}
	}
	profilesmenu.setOutlineColor(menuprofilesmenuoutlinecolor);
	profilesmenu.setFillColor(menuprofilesmenufillcolor);
	arrowdn.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(color67.a * (arrowed_dn ? 0.35 : 1))));
	arrowup.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(color67.a * (arrowed_up ? 0.35 : 1))));
}

inline void Cmain::Manage1(const bool add)
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
	textcolor.a = textchoicecolor.a = textchoiceunavaiblecolor.a = scenario.typeboxcolor.a = scenario.typeboxtextcolor.a = scenario.gaintextcolor.a = color1.a;
	textchoicefillcolor.a = static_cast<sf::Uint8>(choicefactor * color1.a);
	scenario.typeboxfillcolor.a = static_cast<sf::Uint8>(typeboxfactor * color1.a);
	showstats.setColor(color1);
	sliders.setColor(color1);
	bars.setColor(color1);
	for (size_t index = 0U; index != scenario.choice.size(); ++index)
	{
		Choice &c = scenario.choice[index];
		if (!c.avaible && c.hidden) continue;
		if (c.avaible)
		{
			if (index == scenario.choicesel) c.cs.setFillColor(textchoicefillcolor);
			c.cs.setOutlineColor(textchoicecolor);
			c.c.setOutlineColor(textchoicecolor);
			c.text.setFillColor(textchoicecolor);
		}
		else
		{
			c.cs.setOutlineColor(textchoiceunavaiblecolor);
			c.c.setOutlineColor(textchoiceunavaiblecolor);
			c.text.setFillColor(textchoiceunavaiblecolor);
		}
	}
	for (size_t index = 0U; index != scenario.typeboxes.size(); ++index)
	{
		TypeBox &t = scenario.typeboxes[index];
		if (index == scenario.typesel) t.rt.setFillColor(scenario.typeboxfillcolor);
		else t.rt.setFillColor(sf::Color::Transparent);
		t.t.setFillColor(scenario.typeboxtextcolor);
		t.rt.setOutlineColor(scenario.typeboxcolor);
	}
	scenario.next.setColor(color1);
	scenario.text.setFillColor(textcolor);
	//gaintext
	for (auto &g : scenario.gaintext)
	{
		sf::Color color = g.getFillColor();
		color.a = scenario.gaintextcolor.a;
		g.setFillColor(color);
	}
}

inline void Cmain::Manageminus1(const bool add)
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
	resets.setColor(colorminus1);
	sf::Color c = textcolor;
	c.a = colorminus1.a;
	scenario.statcolor.a = colorminus1.a;
	for (auto &i : scenario.i_stats)
	{
		if (i.hidden) continue;
		i.t.setFillColor(scenario.statcolor);
		i.s.setColor(colorminus1);
	}
	for (auto &o : scenario.io_stats)
	{
		if (o.hidden) continue;
		for (auto &t : o.t) t.setFillColor(scenario.statcolor);
		o.s.setColor(colorminus1);
	}
	for (auto &i : scenario.Ints)
	{
		if (i.hidden) continue;
		i.t.setFillColor(c);
	}
	for (auto &s : scenario.s_stats)
	{
		if (s.hidden) continue;
		s.t.setFillColor(c);
	}
}

inline void Cmain::Draw67()
{
	if (k_delete || enternew) return;
	if (gwhich)
	{
		for (size_t x = 0; x != stories.size() && x != menucapacity; x++)
			window.draw(stories[arroweds + x]);
	}
	else
	{
		for (size_t x = 0; x != profiles.size() && x != menucapacity; x++)
			window.draw(profiles[arrowedp + x]);
	}
	window.draw(arrowdn);
	window.draw(arrowup);
	window.draw(profilesmenu);
}

inline void Cmain::Draw1()
{
	window.draw(scenario.text);
	for (const auto &c : scenario.choice)
	{
		if (!c.avaible && c.hidden) continue;
		window.draw(c.text);
		window.draw(c.c);
		window.draw(c.cs);
	}
	for (const auto &t : scenario.typeboxes)
	{
		window.draw(t.rt);
		window.draw(t.t);
	}
	window.draw(michaupase³ke³);
	if (scenario.drawnext) window.draw(scenario.next);
	window.draw(showstats);
	if (scenario.slideratv) {
		window.draw(bars);
		window.draw(sliders);
	}
	for (const auto &g : scenario.gaintext) window.draw(g);
}

inline void Cmain::Drawminus1()
{
	if (resetsb)
	{
		window.draw(button_2_text);
		window.draw(button_3_text);
		window.draw(ctext);
		return;
	}
	for (auto &i : scenario.i_stats)
	{
		if (i.hidden) continue;
		window.draw(i.s);
		window.draw(i.t);
	}
	for (auto &o : scenario.io_stats)
	{
		if (o.hidden) continue;
		window.draw(o.s);
		for (auto &t : o.t) window.draw(t);
	}
	for (auto &i : scenario.Ints)
	{
		if (i.hidden) continue;
		window.draw(i.t);
	}
	for (auto &s : scenario.s_stats)
	{
		if (s.hidden) continue;
		window.draw(s.t);
	}
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

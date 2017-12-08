/*
@Author: LightTab2
The MIT License(MIT)

Copyright(c) 2016 LightTab2 azorro12@gmail.com
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and / or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "Cmain.h"
sf::Color color1(255U, 255U, 255U, 0U);
sf::Color color67(255U, 255U, 255U, 0U);
sf::Color colorminus1(255U, 255U, 255U, 0U);

void Cmain::Reset() //this function is here, because it needs to change colorminus1
{
	scenario.text.setString(L"");
	scenario.choice.clear();
	scenario.cgoto = scenario.sgoto = scenario.dgoto = scenario.ttignore = 0;
	scenario.loadtextonly = false;
	scenario.ssreload = true;
	scenario.i_stats.clear();
	scenario.io_stats.clear();
	scenario.s_stats.clear();
	scenario.Ints.clear();
	scenario.path = "../../bin/Scripts/" + stories[selections].getString() + ".txt";
	scenario.allowdebugging = true; 
	if (!scenario.Parse(false)) DeleteStory();
	resetsb = false;
	scenario.typesel = scenario.choicesel = -1;
	colorminus1.a = 0;
	resets.setColor(colorminus1);
	scenario.statcolor.a = colorminus1.a;
	lsetPos = static_cast<float>(smaxup);
	scenario.customtxt.clear();
	scenario.ssreload = true;

	/*for (auto &i : scenario.i_stats)
	{
		i.second.t.setFillColor(scenario.statcolor);
		i.second.s.setColor(colorminus1);
	}
	for (auto &o : scenario.io_stats)
	{
		for (auto &t : o.second.t) t.setFillColor(scenario.statcolor);
		o.second.s.setColor(colorminus1);
	}
	for (auto &i : scenario.Ints) i.second.t.setFillColor(c);
	for (auto &s : scenario.s_stats) s.second.t.setFillColor(c);
	*/
}

void Cmain::Manage67() //this code could've been done a lot better
{
	menuprofilesmenuoutlinecolor.a = color67.a;
	menuprofilesmenufillcolor.a = static_cast<sf::Uint8>(color67.a * profilesmenufillfactor);
	if (gwhich)
	{
		menustoriescolor.a = menustoriesselectcolor.a = color67.a;
		for (size_t index = 0U; index != stories.size(); ++index) {
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
	arrowdn.setColor(std::move(sf::Color(255U, 255U, 255U, static_cast<sf::Uint8>(color67.a * (arrowed_dn ? 0.35 : 1U)))));
	arrowup.setColor(std::move(sf::Color(255U, 255U, 255U, static_cast<sf::Uint8>(color67.a * (arrowed_up ? 0.35 : 1U)))));
}

void Cmain::Manage1()
{
	textcolor.a = textchoicecolor.a = textchoiceunavailablecolor.a = scenario.typeboxcolor.a = scenario.typeboxtextcolor.a = color1.a;
	textchoicefillcolor.a = static_cast<sf::Uint8>(choicefactor * color1.a);
	scenario.typeboxfillcolor.a = static_cast<sf::Uint8>(typeboxfactor * color1.a);
	scenario.typeboxfillselcolor.a = static_cast<sf::Uint8>(typeboxfactor2 * color1.a);
	scenario.typeboxunavailablefillcolor.a = static_cast<sf::Uint8>(typeboxunavailablefactor * color1.a);
	scenario.typeboxunavailablefillselcolor.a = static_cast<sf::Uint8>(typeboxunavailablefactor2 * color1.a);
	showstats.setColor(color1);
	sliders.setColor(color1);
	bars.setColor(color1);
	for (size_t index = 0U; index != scenario.choice.size(); ++index)
	{
		Choice &c = scenario.choice[index];
		if (c.hidden && !c.available) continue;
		if (c.available)
		{
			if (index == scenario.choicesel) c.cs.setFillColor(textchoicefillcolor);
			c.cs.setOutlineColor(textchoicecolor);
			c.c.setOutlineColor(textchoicecolor);
			c.text.setFillColor(textchoicecolor);
		}
		else
		{
			c.cs.setOutlineColor(textchoiceunavailablecolor);
			c.c.setOutlineColor(textchoiceunavailablecolor);
			c.text.setFillColor(textchoiceunavailablecolor);
		}
	}
	for (size_t index = 0U; index != scenario.typeboxes.size(); ++index)
	{
		TypeBox &t = scenario.typeboxes[index];
		if (index == scenario.typesel)
		{
			if ((!t.limits.first || t.s->size() < t.limits.first) && t.s->size() > t.minchars) t.rt.setFillColor(scenario.typeboxfillselcolor);
			else t.rt.setFillColor(scenario.typeboxunavailablefillselcolor);
		}
		else {
			if ((!t.limits.first || t.s->size() < t.limits.first) && t.s->size() > t.minchars) t.rt.setFillColor(scenario.typeboxfillcolor);
			else t.rt.setFillColor(scenario.typeboxunavailablefillcolor);
		}
		t.t.setFillColor(scenario.typeboxtextcolor);
		t.rt.setOutlineColor(scenario.typeboxcolor);
	}
	scenario.next.setColor(color1);
	scenario.text.setFillColor(textcolor);
	//gaintext
	for (auto &ct : scenario.customtxt)
	{
		sf::Color color = ct.t.getFillColor();
		color.a = color1.a * ct.afactor;
		ct.t.setFillColor(color);
	}
}

inline void Cmain::Manageminus1()
{
	resets.setColor(colorminus1);
	sf::Color c = textcolor;
	c.a = colorminus1.a;
	scenario.statcolor.a = colorminus1.a;
	for (auto &i : scenario.i_stats)
	{
		if (i.second.hidden) continue;
		i.second.t.setFillColor(scenario.statcolor);
		i.second.s.setColor(colorminus1);
	}
	for (auto &o : scenario.io_stats)
	{
		if (o.second.hidden) continue;
		for (auto &t : o.second.t) t.setFillColor(scenario.statcolor);
		o.second.s.setColor(colorminus1);
	}
	for (auto &i : scenario.Ints)
	{
		if (i.second.hidden) continue;
		i.second.t.setFillColor(c);
	}
	for (auto &s : scenario.s_stats)
	{
		if (s.second.hidden) continue;
		s.second.t.setFillColor(c);
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
		if (!c.available && c.hidden) continue;
		window.draw(c.text);
		window.draw(c.c);
		window.draw(c.cs);
	}
	for (const auto &t : scenario.typeboxes)
	{
		window.draw(t.rt);
		window.draw(t.t);
	}
	for (const auto &ct : scenario.customtxt) window.draw(ct.t);
	window.draw(michaupase³ke³);
	if (scenario.DrawNext) window.draw(scenario.next);
	window.draw(showstats);
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
		window.draw(ctext);
		return;
	}
	for (auto &i : scenario.i_stats)
	{
		if (i.second.hidden) continue;
		window.draw(i.second.s);
		window.draw(i.second.t);
	}
	for (auto &o : scenario.io_stats)
	{
		if (o.second.hidden) continue;
		window.draw(o.second.s);
		for (auto &t : o.second.t) window.draw(t);
	}
	for (auto &i : scenario.Ints)
	{
		if (i.second.hidden) continue;
		window.draw(i.second.t);
	}
	for (auto &s : scenario.s_stats)
	{
		if (s.second.hidden) continue;
		window.draw(s.second.t);
	}
	window.draw(resets);
}

void Cmain::PrepareMenu()
{
	sf::Clock timer; timer.restart();
	if (gamestate == -1) {
			if (color1.a) {
				if (color1.a < 3U) color1.a = 0U;
				else color1.a -= 2U;
				Manage1();
			}

			if (color67.a) {
				Draw67();
				if (color67.a < 3U) color67.a = 0U;
				else  color67.a -= 2U;
				Manage67();
			}

			if (colorminus1.a < 255U) {
				if (colorminus1.a > 253U) colorminus1.a = 255U;
				else colorminus1.a += 2U;
				Manageminus1();
			}

			visible = (color1.a == 0U && color67.a == 0U && colorminus1.a == 255U);
		if (color1.a) Draw1();
		if (color67.a) Draw67();
		Drawminus1();
	}
	else if (gamestate == 1) {
		if (!visible) {
				if (color67.a) {
					if (color67.a < 3U) color67.a = 0U;
					else color67.a -= 2U;
					Manage67();
				}

				if (color1.a < 255U) {
					if (color1.a > 253U) color1.a = 255U;
					else color1.a += 2U;
					Manage1();
				}

				if (colorminus1.a) {
					if (colorminus1.a < 3U) colorminus1.a = 0U;
					else colorminus1.a -= 2U;
					Manageminus1();
				}

				visible = (color1.a == 255U && color67.a == 0U && colorminus1.a == 0U);
			if (color67.a) Draw67();
			if (colorminus1.a) Drawminus1(); 
		}
		Draw1();
	}
	else if (gamestate == 6 || gamestate == 7) {
			setupMenu();
			if (!visible) {
					if (color1.a) {
						if (color1.a < 3U) color1.a = 0U;
						else color1.a -= 2U;
						Manage1();
					}

					if (color67.a < 255U) {
						if (color67.a > 253U) color67.a = 255U;
						else color67.a += 2U;
						Manage67();
					}

					if (colorminus1.a) {
						if (colorminus1.a < 3U) colorminus1.a = 0U;
						else colorminus1.a -= 2U;
						Manageminus1();
					}

					visible = (!color1.a && color67.a == 255U && !colorminus1.a);
				if (color1.a) Draw1();
				if (colorminus1.a) Drawminus1();
			}
			Draw67();
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
		}
	else
	{
		if (!visible) {
				if (color1.a) {
					if (color1.a < 3U) color1.a = 0U;
					else color1.a -= 2U;
					Manage1();
				}

				if (color67.a) {
					if (color67.a < 3U) color67.a = 0U;
					else color67.a -= 2U;
					Manage67();
				}

				if (colorminus1.a) {
					Drawminus1();
					if (colorminus1.a < 3U) colorminus1.a = 0U;
					else colorminus1.a -= 2U;
					Manageminus1();
				}

				visible = (!color1.a && !color67.a && !colorminus1.a);
			if (color1.a) Draw1();
			if (color67.a) Draw67();
			if (colorminus1.a) Drawminus1();
		}
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
				if (resbutton1_focus) resbutton1_shape.setFillColor(menuwidthselfillcolor);
				else resbutton1_shape.setFillColor(menuwidthfillcolor);
				if (resbutton2_focus) resbutton2_shape.setFillColor(menuheightselfillcolor);
				else resbutton2_shape.setFillColor(menuheightfillcolor);
			}
		}
		window.draw(button_2_text);
		window.draw(button_3_text);
	}
	if (timer.getElapsedTime().asMicroseconds() < 825) std::this_thread::sleep_for(std::chrono::microseconds(825 - timer.getElapsedTime().asMicroseconds()));
}

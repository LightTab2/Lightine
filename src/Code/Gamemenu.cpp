/*
@Author: LightTab2
The MIT License(MIT)

Copyright(c) 2016 LightTab2 azorro12@gmail.com
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and / or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "Cmain.h"

inline void Cmain::ssb()
{
	if (Contains(shwstats))
	{
		visible = false; gamestate = -1; button_3_text.setString("Back"); button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w - static_cast<int>(round(button_3_text.getGlobalBounds().width + 60.f * w / 800.f)), h - static_cast<int>(round(h / 600.f * 90.f))))); button_2_text.setString("Yes");
	}
}
void Cmain::MainEvent()
{
	while (window.pollEvent(mainevent))
	{
		mousepos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		switch (mainevent.type)
		{
		case sf::Event::Closed:
			quit = true;
			SaveOptions();
			break;
		case sf::Event::KeyPressed:
			if (mainevent.key.code == sf::Keyboard::Escape) {
				if (gamestate == 0 && !prov) { visible = false; prov = true; gamestate = 1; }
				else if (gamestate == 1 && !prov) { visible = false; prov = true; gamestate = 0; stigger = false; if (scenario.typesel != -1) { if (scenario.typeboxes[scenario.typesel].rt.getFillColor() == scenario.typeboxunavailablefillselcolor) scenario.typeboxes[scenario.typesel].rt.setFillColor(scenario.typeboxunavailablefillcolor); else scenario.typeboxes[scenario.typesel].rt.setFillColor(scenario.typeboxfillcolor); scenario.typesel = -1;}
				}
				else if (gamestate == 2) { gamestate = 0; button_1_text.setString("Resume"); button_2_text.setString("Options"); button_3_text.setString("Save Options"); button_1_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_1_text.getGlobalBounds().width) / 2, static_cast<int>(round(h / 600.f * 35.f))))); button_2_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_2_text.getGlobalBounds().width) / 2, h / 2 - static_cast<int>(round(h / 600.f * 40.f))))); button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_3_text.getGlobalBounds().width) / 2, h - static_cast<int>(round(h / 600.f * 90.f))))); }
				else if (gamestate == 3) { if (fullone.empty()) fullone = "800"; if (fulltwo.empty()) fulltwo = "600"; if (static_cast<unsigned int>(stoi(fullone)) > desktop.x) fullone = std::to_string(desktop.x); else if (stoi(fullone) < 800) fullone = "800"; if (static_cast<unsigned int>(stoi(fulltwo)) > desktop.y) fulltwo = std::to_string(desktop.y); else if (stoi(fulltwo) < 600) fulltwo = "600"; resbutton1_text.setString(fullone); resbutton2_text.setString(fulltwo); if (resbutton1_focus || resbutton2_focus) { resbutton1_focus = false; resbutton2_focus = false; } else { gamestate = 2; button_1_text.setString("Graphics"); button_2_text.setString("Audio"); button_3_text.setString("Back"); button_1_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_1_text.getGlobalBounds().width) / 2, static_cast<int>(round(h / 600.f * 35.f))))); button_2_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_2_text.getGlobalBounds().width) / 2, h / 2 - static_cast<int>(round(h / 600.f * 40.f))))); button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_3_text.getGlobalBounds().width) / 2, h - static_cast<int>(round(h / 600.f * 90.f)))));   SaveOptions(); } }
				else if (gamestate == 4) { gamestate = 2; button_1_text.setString("Graphics"); button_2_text.setString("Audio"); button_3_text.setString("Back"); button_1_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_1_text.getGlobalBounds().width) / 2, static_cast<int>(round(h / 600.f * 35.f))))); button_2_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_2_text.getGlobalBounds().width) / 2, h / 2 - static_cast<int>(round(h / 600.f * 40.f))))); button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_3_text.getGlobalBounds().width) / 2, h - static_cast<int>(round(h / 600.f * 90.f)))));   SaveOptions(); }
				else if (gamestate == 5) { gamestate = 0; button_1_text.setString("Resume"); button_2_text.setString("Options"); button_3_text.setString("Save Options"); button_1_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_1_text.getGlobalBounds().width) / 2, static_cast<int>(round(h / 600.f * 35.f))))); button_2_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_2_text.getGlobalBounds().width) / 2, h / 2 - static_cast<int>(round(h / 600.f * 40.f))))); button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_3_text.getGlobalBounds().width) / 2, h - static_cast<int>(round(h / 600.f * 90.f))))); }
				else if (gamestate == 6 || gamestate == 7) {
					if (enternew) {
						if (enternewerror) {
							enternewerror_t.setFillColor(sf::Color(menuerrorcolor.r, menuerrorcolor.g, menuerrorcolor.b, static_cast<sf::Uint8>(0))); enternewerror = false;
						}
						enternew = false; newname.setString(""); gwhich ? scheck = true : pcheck = true;
					}
					else if (k_delete) {
						k_delete = false; gwhich ? scheck = true : pcheck = true;
					}
					else { visible = false; gamestate = 5; errclock.restart(); LoadSave(); button_1_text.setString("Change Profile"); button_2_text.setString("Change Story"); button_3_text.setString("Back"); button_1_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_1_text.getGlobalBounds().width) / 2, static_cast<int>(round(h / 600.f * 35.f))))); button_2_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_2_text.getGlobalBounds().width) / 2, h / 2 - static_cast<int>(round(h / 600.f * 40.f))))); button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_3_text.getGlobalBounds().width) / 2, h - static_cast<int>(round(h / 600.f * 90.f)))));   gwhich ? scheck = true : pcheck = true; }
				}
				else if (gamestate == -1) {
					if (resetsb) {
						resetsb = false;
						button_3_text.setString("Back");
						button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w - static_cast<int>(button_3_text.getGlobalBounds().width) - static_cast<int>(round(60.f * w / 800.f)), h - static_cast<int>(round(h / 600.f * 90.f)))));
						disbutton = false;
						disrandomnameLOL = true;
					}
					else {
						visible = false; gamestate = 1; button_1_text.setString("Resume"); button_2_text.setString("Options"); button_3_text.setString("Save Options"); button_1_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_1_text.getGlobalBounds().width) / 2, static_cast<int>(round(h / 600.f * 35.f))))); button_2_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_2_text.getGlobalBounds().width) / 2, h / 2 - static_cast<int>(round(h / 600.f * 40.f))))); button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_3_text.getGlobalBounds().width) / 2, h - static_cast<int>(round(h / 600.f * 90.f)))));   sviewchange(lsetPos);
					}
				}
				disbutton = false;
				disrandomnameLOL = true;
				button_1 = button_1_text.getGlobalBounds(); button_2 = button_2_text.getGlobalBounds(); button_3 = button_3_text.getGlobalBounds();
			}
			else if (mainevent.key.code == sf::Keyboard::BackSpace) {
				if (gamestate == 3 && !fullscreen) {
					if (resbutton1_focus && fullone.length() != 0U) { fullone.pop_back(); resbutton1_text.setString(fullone); }
					else if (resbutton2_focus && fulltwo.length() != 0U) { fulltwo.pop_back(); resbutton2_text.setString(fulltwo); }
				}
				else if (enternew && !newname.getString().isEmpty())
				{
					auto t = newname.getString();
					if (t.getSize() > 1)
					{
						if (t[t.getSize() - 1U] == '\n')
						{
							t.erase(t.getSize() - 2, 2);
						}
						else t.erase(t.getSize() - 1);
					}
					else t.clear();
					newname.setString(t);
					newname.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(newname.getGlobalBounds().width) / 2, h / 2 - static_cast<int>(round(ctext.getGlobalBounds().height*0.6f)))));
				}
				else if (gamestate == 1 && scenario.typesel != -1)
				{
					auto &t = scenario.typeboxes[scenario.typesel];
					if (t.DeleteChar())
					{
						auto box = t.rt.getSize();
						t.rt.setSize(sf::Vector2f(box.x, box.y - scenario.Tsize));
						for (int x = scenario.typesel + 1; x != scenario.typeboxes.size(); ++x)
						{
							box = scenario.typeboxes[x].rt.getPosition();
							scenario.typeboxes[x].rt.setPosition(box.x, box.y - scenario.Tsize);
							box = scenario.typeboxes[x].t.getPosition();
							scenario.typeboxes[x].t.setPosition(box.x, box.y - scenario.Tsize);
						}
						for (auto &c : scenario.choice)
						{
							box = c.c.getPosition();
							c.c.setPosition(box.x, box.y - scenario.Tsize);
							box = c.cs.getPosition();
							c.cs.setPosition(box.x, box.y - scenario.Tsize);
							box = c.text.getPosition();
							c.text.setPosition(box.x, box.y - scenario.Tsize);
						}
						box = scenario.next.getPosition();
						scenario.next.setPosition(box.x, box.y - scenario.Tsize);
						scenario.dmargin -= static_cast<int>(scenario.Tsize);
						box = sliders.getPosition();
						sliders.setPosition(box.x, round(box.y * ((scenario.dmargin + scenario.Tsize) / scenario.dmargin)));
						if (static_cast<int>(round(window.mapCoordsToPixel(sliders.getPosition()).y)) > smaxdown)
							sliders.setPosition(window.mapPixelToCoords(sf::Vector2i(static_cast<int>(round(box.x)), static_cast<int>(round(smaxdown - sliders.getGlobalBounds().height)))));
						slidersb = sliders.getGlobalBounds();
						scenario.ssreload = true;
					}
					if (t.s->size() > t.minchars) t.rt.setFillColor(scenario.typeboxfillselcolor);
					else t.rt.setFillColor(scenario.typeboxunavailablefillselcolor);
				}
			}
			else if (mainevent.key.code == sf::Keyboard::LAlt || mainevent.key.code == sf::Keyboard::RAlt) alt = true;
			else if (mainevent.key.code == sf::Keyboard::F4 && alt)
			{
				quit = true;
				SaveOptions();
			}
			else if (mainevent.key.code == sf::Keyboard::Return) {
				if (gamestate == 3 && !fullscreen) {
					resbutton1_focus = false; resbutton2_focus = false;
					if (fullone.empty()) fullone = "800"; 
					if (fulltwo.empty()) fulltwo = "600";
					if (static_cast<unsigned int>(stoi(fullone)) > desktop.x) fullone = std::to_string(desktop.x);
					else if (stoi(fullone) < 800) fullone = "800";
					if (static_cast<unsigned int>(stoi(fulltwo)) > desktop.y) fulltwo = std::to_string(desktop.y);
					else if (stoi(fulltwo) < 600) fulltwo = "600"; 
					resbutton1_text.setString(fullone);
					resbutton2_text.setString(fulltwo);
				}
				else if (gamestate > 5 && enternew)
					CreateNew();
			}
			break;
		case sf::Event::KeyReleased:
			if (mainevent.key.code == sf::Keyboard::Escape) prov = false;
			else if (mainevent.key.code == sf::Keyboard::LAlt) alt = false;
			else if (mainevent.key.code == sf::Keyboard::Delete)
			{
				if (!enternew)
				{
					k_delete = true;
					gwhich ? scheck = true : pcheck = true;
					disrandomnameLOL = disbutton = true;
				}
			}
			else if (mainevent.key.code == sf::Keyboard::Up)
			{
				if (gamestate == 6 && !k_delete && !enternew)
				{
					if (!profiles.empty() && round(menucapacity / 2U) <= (profiles.size() - 1U) - selectionp && arrowedp > 0)
					{
						pcheck = true;
						arrowedp -= 1;
					}
					if (selectionp > 0)
					{
						selectionp -= 1;
						pcheck = true;
					}
				}
				else if (gamestate == 7 && !k_delete && !enternew)
				{
					if (!stories.empty() && round(menucapacity / 2U) <= (stories.size() - 1U) - selections && arroweds > 0)
					{
						scheck = true;
						arroweds -= 1;
					}
					if (selections > 0)
					{
						selections -= 1;
						scheck = true;
					}
				}
			}
			else if (mainevent.key.code == sf::Keyboard::Down)
			{
				if (gamestate == 6 && !k_delete && !enternew)
				{
					if (static_cast<unsigned int>(selectionp) >= menucapacity / 2U && arrowedp < arrowedp_margin)
					{
						pcheck = true;
						arrowedp += 1;
					}
					if (!profiles.empty() && static_cast<unsigned int>(selectionp) < profiles.size() - 1U)
					{
						selectionp += 1;
						pcheck = true;
					}
				}
				else if (gamestate == 7 && !k_delete && !enternew)
				{
					if (static_cast<unsigned int>(selections) >= menucapacity / 2U && arroweds < arroweds_margin)
					{
						scheck = true;
						arroweds += 1;
					}
					if (!stories.empty() && static_cast<unsigned int>(selections) < stories.size() - 1U)
					{
						selections += 1;
						scheck = true;
					}
				}
			}
			break;
		case sf::Event::MouseWheelScrolled:
			if (!stigger)
			{
				if (textcolor.a != 255 && textcolor.a != 0) break;
				if (scenario.slideratv)
				{
					if (gamestate == 1) {
						lsetPos -= mainevent.mouseWheelScroll.delta * static_cast<float>(smax) / static_cast<float>(scenario.scrolltimes); //delta (1 or -1) is the move of slider
						sviewchange(lsetPos);
					}
					else if (gamestate == -1 && !resetsb)
					{
						ssetPos -= mainevent.mouseWheelScroll.delta * static_cast<float>(smax) / static_cast<float>(scenario.scrolltimes);
						sviewchange(ssetPos);
					}
				}
			}
			if (gamestate == 6) {
				selectionp -= static_cast<int>(mainevent.mouseWheelScroll.delta);
				arrowedp = selectionp - static_cast<int>(menucapacity) / 2;
				if (arrowedp < 0) arrowedp = 0;
				else if (arrowedp > arrowedp_margin) arrowedp = arrowedp_margin;
				if (selectionp < 0) selectionp = 0;
				else if (static_cast<unsigned int>(selectionp) >= profiles.size()) selectionp = profiles.empty() ? 0 : (static_cast<int>(profiles.size()) - 1);
				pcheck = true;
			}
			else if (gamestate == 7)
			{
				selections -= static_cast<int>(mainevent.mouseWheelScroll.delta);
				arroweds = selections - static_cast<int>(menucapacity) / 2;
				if (arroweds < 0) arroweds = 0;
				else if (arroweds > arroweds_margin) arroweds = arroweds_margin;
				if (selections < 0) selections = 0;
				else if (static_cast<unsigned int>(selections) >= stories.size()) selections = stories.empty() ? 0 : (static_cast<int>(stories.size()) - 1);
				scheck = true;
			}
			break;
		case sf::Event::MouseButtonPressed:
			if (mainevent.key.code == sf::Mouse::Left) {
				clicked = true;
				onClick();
			}
			break;
		case sf::Event::MouseButtonReleased:
			if (mainevent.key.code == sf::Mouse::Left) {
				onRelease();
				clicked = false;
			}
			break;
		case sf::Event::TextEntered:
			if (gamestate == 3 && fullscreen != true)
			{
				if (mainevent.text.unicode > 47U && mainevent.text.unicode < 58U) {
					if (resbutton1_focus) {
						if (fullone.length() != 4) {
							fullone += mainevent.text.unicode;
							resbutton1_text.setString(fullone);
						}
					}
					else if (resbutton2_focus) {
						if (fulltwo.length() != 4) {
							fulltwo += mainevent.text.unicode;
							resbutton2_text.setString(fulltwo);
						}
					}
				}
			}
			else if (enternew && (gamestate == 6 || gamestate == 7))
			{
				const sf::Uint32 &achar = mainevent.text.unicode;
				if (achar > 31U && achar != 34U &&
					achar != 42U && achar != 47U && achar != 58U &&
					achar != 60U && achar != 62U && achar != 63U &&
					achar != 92U && achar != 124U && achar != 127U) {
					auto t = newname.getString() + achar;
					newname.setString(t);
					if ((newname.getGlobalBounds().width) > (w - w / 12.f))
					{
						t.insert(t.getSize() - 1U, L'\n');
						newname.setString(t);
					}
					newname.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(newname.getGlobalBounds().width) / 2, h / 2 - static_cast<int>(round(ctext.getGlobalBounds().height*0.6f)))));
				}
			}
			else if (gamestate == 1 && scenario.typesel != -1)
			{
				if (!iswprint(mainevent.text.unicode)) break;
				auto &t = scenario.typeboxes[scenario.typesel];
				if (!t.limits.first || t.s->size() < t.limits.first)
				{
					if (t.InsertChar(mainevent.text.unicode))
					{
						auto box = t.rt.getSize();
						t.rt.setSize(sf::Vector2f(box.x, box.y + scenario.Tsize));
						for (int x = scenario.typesel + 1; x != scenario.typeboxes.size(); ++x)
						{
							box = scenario.typeboxes[x].rt.getPosition();
							scenario.typeboxes[x].rt.setPosition(box.x, box.y + scenario.Tsize);
							box = scenario.typeboxes[x].t.getPosition();
							scenario.typeboxes[x].t.setPosition(box.x, box.y + scenario.Tsize);
						}
						for (auto &c : scenario.choice)
						{
							box = c.c.getPosition();
							c.c.setPosition(box.x, box.y + scenario.Tsize);
							box = c.cs.getPosition();
							c.cs.setPosition(box.x, box.y + scenario.Tsize);
							box = c.text.getPosition();
							c.text.setPosition(box.x, box.y + scenario.Tsize);
						}
						box = scenario.next.getPosition();
						scenario.next.setPosition(box.x, box.y + scenario.Tsize);
						scenario.dmargin += static_cast<int>(scenario.Tsize);
						box = sliders.getPosition();
						sliders.setPosition(box.x, round(box.y * ((scenario.dmargin - scenario.Tsize) / scenario.dmargin)));
						if (static_cast<int>(sliders.getPosition().y) < smaxup) sliders.setPosition(box.x, static_cast<float>(smaxup));
						slidersb = sliders.getGlobalBounds();
					}
					if ((!visible || t.rt.getFillColor() != scenario.typeboxfillselcolor) && t.s->size() > t.minchars) t.rt.setFillColor(scenario.typeboxfillselcolor);
					scenario.ssreload = true;
				}
				else t.rt.setFillColor(scenario.typeboxunavailablefillselcolor);
			}
			break;
		}
	}
}
void Cmain::onRelease()
{
	switch (gamestate)
	{
	case -1:
		if (stigger) {
			stigger = false;
			slidersb = sliders.getGlobalBounds();
		}
		if (resetsb) {
			if (Contains(button_2)) {
				sviewchange(0);
				Reset();
				gamestate = 1;
				visible = false;
				button_1_text.setString("Resume");
				button_2_text.setString("Options");
				button_3_text.setString("Save Options");
				button_1_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_1_text.getGlobalBounds().width) / 2, static_cast<int>(round(h / 600.f * 35.f)))));
				button_2_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_2_text.getGlobalBounds().width) / 2, h / 2 - static_cast<int>(round(h / 600.f * 40.f)))));
				button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_3_text.getGlobalBounds().width) / 2, h - static_cast<int>(round(h / 600.f * 90.f)))));
				disbutton = false;
				disrandomnameLOL = true;
			}
			else if (Contains(button_3)) {
				resetsb = false;
				button_3_text.setString("Back");
					button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w - static_cast<int>(button_3_text.getGlobalBounds().width) - static_cast<int>(round(60.f * w / 800.f)), h - static_cast<int>(round(h / 600.f * 90.f)))));
				disbutton = false;
				disrandomnameLOL = true;
			}
		}
		/*else if (Contains(button_3)) {
			visible = false;
			gamestate = 1;
			button_3_text.setString("Save Options"); button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_3_text.getGlobalBounds().width / 2.f), h - static_cast<int>(round(h / 600.f * 90.f)))));
			button_2_text.setString("Options"); button_2_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_2_text.getGlobalBounds().width / 2.f), h / 2 - static_cast<int>(round(h / 600.f * 40.f)))));
			sviewchange(lsetPos);
		}*/ //wtf why did I do something that stupid? This bug had existed like since Stat system implementation. Let this comment be a memorial for my dumbness
		break;
	case 0:
		if (Contains(button_1)) { visible = false; gamestate = 1; }
		else if (Contains(button_2)) {
			gamestate = 2; button_1_text.setString("Graphics"); button_2_text.setString("Audio"); button_3_text.setString("Back"); button_1_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_1_text.getGlobalBounds().width) / 2, static_cast<int>(round(h / 600.f * 35.f))))); button_2_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_2_text.getGlobalBounds().width) / 2, h / 2 - static_cast<int>(round(h / 600.f * 40.f))))); button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_3_text.getGlobalBounds().width) / 2, h - static_cast<int>(round(h / 600.f * 90.f)))));
		}
		else if (Contains(button_3)) {
			gamestate = 5; button_1_text.setString("Change Profile"); button_2_text.setString("Change Story"); button_3_text.setString("Back"); button_1_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_1_text.getGlobalBounds().width) / 2, static_cast<int>(round(h / 600.f * 35.f))))); button_2_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_2_text.getGlobalBounds().width) / 2, h / 2 - static_cast<int>(round(h / 600.f * 40.f))))); button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_3_text.getGlobalBounds().width) / 2, h - static_cast<int>(round(h / 600.f * 90.f)))));
		}
		break;
	case 1:
		if (stigger) {
			stigger = false;
			slidersb = sliders.getGlobalBounds();
		}
		else if (scenario.DrawNext && Contains(scenario.Bnext))
		{
			if (scenario.choiceneed == true && scenario.choicesel == -1) break;
			for (auto &t : scenario.typeboxes)
				if (std::move(t.rt.getFillColor()) == scenario.typeboxunavailablefillcolor || std::move(t.rt.getFillColor()) == scenario.typeboxunavailablefillselcolor) return; //std::move is redundant probably. Not sure tho
			sviewchange(0);
			if (scenario.choicesel > -1)
			{
				scenario.cgoto = scenario.sgoto = scenario.choice[scenario.choicesel].gto;
				scenario.dgoto = scenario.choice[scenario.choicesel].dgto;
				scenario.ttignore = scenario.choice[scenario.choicesel].ttignore;
			}
			else { scenario.cgoto = scenario.sgoto; scenario.dgoto = 0; }
			if (!scenario.Parse(false)) DeleteStory();
		}
		break;
	case 2:
		if (Contains(button_1)) {
			gamestate = 3; button_1_text.setString(""); button_2_text.setString("Fullscreen"); button_3_text.setString("Apply"); button_1_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_1_text.getGlobalBounds().width) / 2, static_cast<int>(round(h / 600.f * 35.f))))); button_2_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_2_text.getGlobalBounds().width) / 2, h / 2 - static_cast<int>(round(h / 600.f * 40.f))))); button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_3_text.getGlobalBounds().width) / 2, h - static_cast<int>(round(h / 600.f * 90.f)))));
		}
		else if (Contains(button_2)) {
			gamestate = 4; button_1_text.setString("Music"); button_2_text.setString("Sound"); button_3_text.setString("Apply"); button_1_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_1_text.getGlobalBounds().width) / 2, static_cast<int>(round(h / 600.f * 35.f))))); button_2_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_2_text.getGlobalBounds().width) / 2, h / 2 - static_cast<int>(round(h / 600.f * 40.f))))); button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_3_text.getGlobalBounds().width) / 2, h - static_cast<int>(round(h / 600.f * 90.f)))));
		}
		else if (Contains(button_3)) {
			gamestate = 0; button_1_text.setString("Resume"); button_2_text.setString("Options"); button_3_text.setString("Save Options"); button_1_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_1_text.getGlobalBounds().width) / 2, static_cast<int>(round(h / 600.f * 35.f))))); button_2_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_2_text.getGlobalBounds().width) / 2, h / 2 - static_cast<int>(round(h / 600.f * 40.f))))); button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_3_text.getGlobalBounds().width) / 2, h - static_cast<int>(round(h / 600.f * 90.f)))));
		}
		break;
	case 3:
		if (Contains(button_2)) {
			if (!fullscreen) { resbutton1_focus = false; resbutton2_focus = false; fullscreen = true; int cw = desktop.x; int ch = desktop.y; fullone = std::to_string(cw); fulltwo = std::to_string(ch); resbutton1_text.setString(fullone); resbutton2_text.setString(fulltwo); }
			else fullscreen = false;
		}
		else if (Contains(button_3)) {
			resbutton1_focus = false; resbutton2_focus = false; SaveOptions(); gamestate = 2; button_1_text.setString("Graphics"); button_2_text.setString("Audio"); button_3_text.setString("Back"); button_1_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_1_text.getGlobalBounds().width) / 2, static_cast<int>(round(h / 600.f * 35.f))))); button_2_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_2_text.getGlobalBounds().width) / 2, h / 2 - static_cast<int>(round(h / 600.f * 40.f))))); button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_3_text.getGlobalBounds().width) / 2, h - static_cast<int>(round(h / 600.f * 90.f)))));
		}
		break;
	case 4:
		if (Contains(button_1)) music = !music;
		else if (Contains(button_2)) sound = !sound;
		else if (Contains(button_3)) {
			gamestate = 2; button_1_text.setString("Graphics"); button_2_text.setString("Audio"); button_3_text.setString("Back"); button_1_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_1_text.getGlobalBounds().width) / 2, static_cast<int>(round(h / 600.f * 35.f))))); button_2_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_2_text.getGlobalBounds().width) / 2, h / 2 - static_cast<int>(h / 600.f * 40.f)))); button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_3_text.getGlobalBounds().width) / 2, h - static_cast<int>(round(h / 600.f * 90.f))))); SaveOptions();
		}
		break;
	case 5:
		if (Contains(button_1)) {
			visible = false; gamestate = 6; button_2_text.setString("New"); button_3_text.setPosition(profilesmenu.getGlobalBounds().left, profilesmenu.getGlobalBounds().top + profilesmenu.getGlobalBounds().height); button_2_text.setPosition(profilesmenu.getGlobalBounds().left + profilesmenu.getGlobalBounds().width - button_2_text.getGlobalBounds().width, profilesmenu.getGlobalBounds().top + profilesmenu.getGlobalBounds().height);
			pcheck = true;
		}
		else if (Contains(button_2)) {
			visible = false; gamestate = 7; button_2_text.setString("New"); button_3_text.setPosition(profilesmenu.getGlobalBounds().left, profilesmenu.getGlobalBounds().top + profilesmenu.getGlobalBounds().height); button_2_text.setPosition(profilesmenu.getGlobalBounds().left + profilesmenu.getGlobalBounds().width - button_2_text.getGlobalBounds().width, profilesmenu.getGlobalBounds().top + profilesmenu.getGlobalBounds().height);
			scheck = true;
		}
		else if (Contains(button_3)) {
			gamestate = 0; button_1_text.setString("Resume"); button_2_text.setString("Options"); button_3_text.setString("Save Options"); button_1_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_1_text.getGlobalBounds().width) / 2, static_cast<int>(round(h / 600.f * 35.f))))); button_2_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_2_text.getGlobalBounds().width) / 2, h / 2 - static_cast<int>(round(h / 600.f * 40.f))))); button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_3_text.getGlobalBounds().width) / 2, h - static_cast<int>(round(h / 600.f * 90.f)))));
		}
		break;
	case 6:
		if (k_delete) {
			if (Contains(button_2)) {
				k_delete = false;
				pcheck = true;
			}
			else if (Contains(button_3))
				DeleteProfile();
		}
		else if (enternew) {
			if (Contains(button_2)) CreateNew();
			else if (Contains(button_3)) {
				if (enternewerror) {
					enternewerror_t.setFillColor(sf::Color(menuerrorcolor.r, menuerrorcolor.g, menuerrorcolor.b, static_cast<sf::Uint8>(0))); enternewerror = false;
				}
				enternew = false; newname.setString(""); pcheck = true;
			}
		}
		else if (Contains(button_2)) {
			enternew = true; pcheck = true;
		}
		else if (Contains(button_3)) {
			visible = false; gamestate = 5; LoadSave(); button_1_text.setString("Change Profile"); button_2_text.setString("Change Story"); button_3_text.setString("Back"); button_1_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_1_text.getGlobalBounds().width) / 2, static_cast<int>(round(h / 600.f * 35.f))))); button_2_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_2_text.getGlobalBounds().width) / 2, h / 2 - static_cast<int>(round(h / 600.f * 40.f))))); button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_3_text.getGlobalBounds().width) / 2, h - static_cast<int>(round(h / 600.f * 90.f))))); pcheck = true;
		}
		break;
	case 7:
		if (k_delete) {
			if (Contains(button_2)) {
				k_delete = false;
				scheck = true;
			}
			else if (Contains(button_3))
				DeleteStory();
		}
		else if (enternew) {
			if (Contains(button_2))
				CreateNew();
			else if (Contains(button_3)) {
				if (enternewerror) {
					enternewerror_t.setFillColor(sf::Color(menuerrorcolor.r, menuerrorcolor.g, menuerrorcolor.b, static_cast<sf::Uint8>(0))); enternewerror = false;
				}
				enternew = false; newname.setString(""); scheck = true;
			}
		}
		else if (Contains(button_2)) {
			enternew = true; scheck = true;
		}
		else if (Contains(button_3)) {
			visible = false; gamestate = 5; LoadSave(); button_1_text.setString("Change Profile"); button_2_text.setString("Change Story"); button_3_text.setString("Back"); button_1_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_1_text.getGlobalBounds().width) / 2, static_cast<int>(round(h / 600.f * 35.f))))); button_2_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_2_text.getGlobalBounds().width) / 2, h / 2 - static_cast<int>(round(h / 600.f * 40.f))))); button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_3_text.getGlobalBounds().width) / 2, h - static_cast<int>(round(h / 600.f * 90.f))))); scheck = true;
		}
		break;
	}
	disrandomnameLOL = true;
	button_1 = button_1_text.getGlobalBounds();
	button_2 = button_2_text.getGlobalBounds();
	button_3 = button_3_text.getGlobalBounds();
}

void Cmain::onClick()
{
	switch (gamestate)
	{
	case -1:
		if (scenario.slideratv && Contains(slidersb)) {
			smouseposy = static_cast<int>(round(mousepos.y - slidersb.top));
			stigger = true;
		}
		else if (Contains(resets_b)) {
			resetsb = true;
			button_3_text.setString("No");
			button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w - static_cast<int>(round(button_3_text.getGlobalBounds().width + 60.f * w / 800.f)), h - static_cast<int>(round(h / 600.f * 90.f)))));
			button_2_text.setPosition(window.mapPixelToCoords(sf::Vector2i(static_cast<int>(round(60.f * w / 800.f)), h - static_cast<int>(round(h / 600.f * 90.f)))));
		}
		break;
	case 1:
		if (!stigger && scenario.slideratv && Contains(slidersb)) {
			smouseposy = static_cast<int>(mousepos.y - slidersb.top);
			stigger = true;
			return;
		}
			ssb();
			for (unsigned int x = 0; x < scenario.choice.size(); ++x)
				if (Contains(scenario.choice[x].c.getGlobalBounds()) || Contains(scenario.choice[x].cs.getGlobalBounds()))
				{
					if (!scenario.choice[x].available) break;
					for (Choice &d : scenario.choice) d.cs.setFillColor(sf::Color::Transparent);
					scenario.choice[x].cs.setFillColor(textchoicefillcolor);
					scenario.choicesel = x;
					return;
				}
			for (unsigned int x = 0; x < scenario.typeboxes.size(); ++x)
				if (Contains(scenario.typeboxes[x].rt.getGlobalBounds()))
				{
					auto &t = scenario.typeboxes[x];
					for (TypeBox &d : scenario.typeboxes) {
						if ((!d.limits.first || d.s->size() < d.limits.first) && d.s->size() > d.minchars) d.rt.setFillColor(scenario.typeboxfillcolor);
						else d.rt.setFillColor(scenario.typeboxunavailablefillcolor);
					}
					if ((!t.limits.first || t.s->size() < t.limits.first) && t.s->size() > t.minchars) t.rt.setFillColor(scenario.typeboxfillselcolor);
					else t.rt.setFillColor(scenario.typeboxunavailablefillselcolor);
					scenario.typesel = x;
					return; //flow ends here
				}
			if (scenario.typesel != -1) {
				if (scenario.typeboxes[scenario.typesel].rt.getFillColor() == scenario.typeboxunavailablefillselcolor) scenario.typeboxes[scenario.typesel].rt.setFillColor(scenario.typeboxunavailablefillcolor);
				else scenario.typeboxes[scenario.typesel].rt.setFillColor(scenario.typeboxfillcolor);
				scenario.typesel = -1;
			}
		break;
	case 3:
		if (Contains(resbutton1)) { resbutton1_focus = true; resbutton2_focus = false; if (fullone.empty()) fullone = "800"; if (fulltwo.empty()) fulltwo = "600"; if (static_cast<unsigned int>(stoi(fullone)) > desktop.x) fullone = std::to_string(desktop.x); else if (stoi(fullone) < 800) fullone = "800"; if (static_cast<unsigned int>(stoi(fulltwo)) > desktop.y) fulltwo = std::to_string(desktop.y); else if (stoi(fulltwo) < 600) fulltwo = "600"; resbutton1_text.setString(fullone); resbutton2_text.setString(fulltwo); }
		else if (Contains(resbutton2)) { resbutton1_focus = false; resbutton2_focus = true; if (fullone.empty()) fullone = "800"; if (fulltwo.empty()) fulltwo = "600"; if (static_cast<unsigned int>(stoi(fullone)) > desktop.x) fullone = std::to_string(desktop.x); else if (stoi(fullone) < 800) fullone = "800"; if (static_cast<unsigned int>(stoi(fulltwo)) > desktop.y) fulltwo = std::to_string(desktop.y); else if (stoi(fulltwo) < 600) fulltwo = "600"; resbutton1_text.setString(fullone); resbutton2_text.setString(fulltwo); }	
		else {
			resbutton1_focus = false; resbutton2_focus = false;
			if (fullone.empty()) fullone = "800";
			if (static_cast<unsigned int>(stoi(fullone)) > desktop.x) fullone = std::to_string(desktop.x); 
			else if (stoi(fullone) < 800) fullone = "800"; 
			if (fulltwo.empty()) fulltwo = "600";
			if (static_cast<unsigned int>(stoi(fulltwo)) > desktop.y) fulltwo = std::to_string(desktop.y);
			else if (stoi(fulltwo) < 600) fulltwo = "600"; 
			resbutton1_text.setString(fullone);
			resbutton2_text.setString(fulltwo);
		}
		break;
	case 6:
		if (!k_delete && !enternew) {
			if (Contains(arrowdn_b)) {
				if (static_cast<unsigned int>(selectionp) >= menucapacity / 2U && arrowedp < arrowedp_margin)
					arrowedp += 1;
				if (!profiles.empty() && static_cast<unsigned int>(selectionp) < (profiles.size() - 1U)) {
					selectionp += 1;
				}
				pcheck = true;
			}
			else if (Contains(arrowup_b)) {
				if (!profiles.empty() && menucapacity / 2U <= (profiles.size() - 1U) - selectionp && arrowedp > 0) 
					arrowedp -= 1;
				if (selectionp > 0) {
					selectionp -= 1;
				}
				pcheck = true;
			}
			else {
				for (int repeated = 0U; repeated != menucapacity && repeated != profiles.size(); ++repeated) {
					if (Contains(profiles[arrowedp + repeated].getGlobalBounds()) && selectionp != (arrowedp + repeated)) {
						selectionp = arrowedp + repeated;
						arrowedp += repeated - menucapacity / 2U;
						if (arrowedp < 0) arrowedp = 0;
						else if (arrowedp > arrowedp_margin) arrowedp = arrowedp_margin;
						pcheck = true;
						return;
					}
				}
			}
		}
		break;
	case 7:
		if (!k_delete && !enternew) {
			if (Contains(arrowdn_b)) {
				if (static_cast<unsigned int>(selections) >= menucapacity / 2U && arroweds < arroweds_margin)
					arroweds += 1;
				if (!stories.empty() && static_cast<unsigned int>(selections) < (stories.size() - 1U)) {
					selections += 1;
				}
				scheck = true;
			}
			else if (Contains(arrowup_b)) {
				if (!stories.empty() && menucapacity / 2U <= (stories.size() - 1U - selections) && arroweds > 0)
					arroweds -= 1;
				if (selections > 0) {
					selections -= 1;
				}
				scheck = true;
			}
			else {
				for (size_t repeated = 0U; repeated != menucapacity && repeated != stories.size(); ++repeated) {
					if (Contains(stories[arroweds + repeated].getGlobalBounds()) && selections != (arroweds + repeated)) {
						selections = arroweds + static_cast<int>(repeated);
						arroweds += static_cast<int>(repeated - menucapacity / 2U);
						if (arroweds < 0) arroweds = 0;
						else if (arroweds > arroweds_margin) arroweds = arroweds_margin;
						scheck = true;
						return;
					}
				}
			}
		}
		break;
	}
}
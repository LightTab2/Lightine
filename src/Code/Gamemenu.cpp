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
	if (Contains(shwstats))////
	{
		if (scenario.additional.empty() || scenario.sempty || scenario.pempty) return;
		visible = false; gamestate = -1; button_3_text.setString("Back"); button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w - static_cast<int>(button_3_text.getGlobalBounds().width + 60.f * w / 800.f), h - static_cast<int>(h / 600.f * 90.f)))); button_2_text.setString("No");
	}
}
void Cmain::MainEvent()
{
	while (window.pollEvent(mainevent))
	{
		mousepos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		switch (mainevent.type)
		{
		case sf::Event::KeyPressed:
			if (mainevent.key.code == sf::Keyboard::Escape) {
				if (gamestate == 0 && !prov) { visible = false; prov = true; gamestate = 1; }
				else if (gamestate == 1 && !prov) { visible = false; prov = true; gamestate = 0; stigger = false; }
				else if (gamestate == 2) { gamestate = 0; button_1_text.setString("Resume"); button_2_text.setString("Options"); button_3_text.setString("Save Options"); button_1_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_1_text.getGlobalBounds().width) / 2, static_cast<int>(h / 600.f * 35.f)))); button_2_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_2_text.getGlobalBounds().width) / 2, h / 2 - static_cast<int>(h / 600.f * 40.f)))); button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_3_text.getGlobalBounds().width) / 2, h - static_cast<int>(h / 600.f * 90.f)))); button_1 = button_1_text.getGlobalBounds(); button_2 = button_2_text.getGlobalBounds(); button_3 = button_3_text.getGlobalBounds(); }
				else if (gamestate == 3) { if (static_cast<unsigned int>(stoi(fullone)) > desktop.x) { fullone = std::to_string(desktop.x); resbutton1_text.setString(fullone); } else if (stoi(fullone) < 800) { fullone = "800"; resbutton1_text.setString(fullone); } if (static_cast<unsigned int>(stoi(fulltwo)) > desktop.y) { fulltwo = std::to_string(desktop.y); resbutton2_text.setString(fulltwo); } else if (stoi(fulltwo) < 600) { fulltwo = "600"; resbutton2_text.setString(fulltwo); } if (resbutton1_focus || resbutton2_focus) { resbutton1_focus = false; resbutton2_focus = false; } else { gamestate = 2; button_1_text.setString("Graphics"); button_2_text.setString("Audio"); button_3_text.setString("Back"); button_1_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_1_text.getGlobalBounds().width) / 2, static_cast<int>(h / 600.f * 35.f)))); button_2_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_2_text.getGlobalBounds().width) / 2, h / 2 - static_cast<int>(h / 600.f * 40.f)))); button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_3_text.getGlobalBounds().width) / 2, h - static_cast<int>(h / 600.f * 90.f)))); button_1 = button_1_text.getGlobalBounds(); button_2 = button_2_text.getGlobalBounds(); button_3 = button_3_text.getGlobalBounds(); SaveOptions(); } }
				else if (gamestate == 4) { gamestate = 2; button_1_text.setString("Graphics"); button_2_text.setString("Audio"); button_3_text.setString("Back"); button_1_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_1_text.getGlobalBounds().width) / 2, static_cast<int>(h / 600.f * 35.f)))); button_2_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_2_text.getGlobalBounds().width) / 2, h / 2 - static_cast<int>(h / 600.f * 40.f)))); button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_3_text.getGlobalBounds().width) / 2, h - static_cast<int>(h / 600.f * 90.f)))); button_1 = button_1_text.getGlobalBounds(); button_2 = button_2_text.getGlobalBounds(); button_3 = button_3_text.getGlobalBounds(); SaveOptions(); }
				else if (gamestate == 5) { gamestate = 0; button_1_text.setString("Resume"); button_2_text.setString("Options"); button_3_text.setString("Save Options"); button_1_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_1_text.getGlobalBounds().width) / 2, static_cast<int>(h / 600.f * 35.f)))); button_2_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_2_text.getGlobalBounds().width) / 2, h / 2 - static_cast<int>(h / 600.f * 40.f)))); button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_3_text.getGlobalBounds().width) / 2, h - static_cast<int>(h / 600.f * 90.f)))); button_1 = button_1_text.getGlobalBounds(); button_2 = button_2_text.getGlobalBounds(); button_3 = button_3_text.getGlobalBounds(); }
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
				else { visible = false; gamestate = 5; errclock.restart(); button_1_text.setString("Change Profile"); button_2_text.setString("Change Story"); button_3_text.setString("Back"); button_1_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_1_text.getGlobalBounds().width) / 2, static_cast<int>(h / 600.f * 35.f)))); 	button_2_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_2_text.getGlobalBounds().width) / 2, h / 2 - static_cast<int>(h / 600.f * 40.f)))); button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_3_text.getGlobalBounds().width) / 2, h - static_cast<int>(h / 600.f * 90.f)))); button_1 = button_1_text.getGlobalBounds(); button_2 = button_2_text.getGlobalBounds(); button_3 = button_3_text.getGlobalBounds(); gwhich ? scheck = true : pcheck = true; SaveOptions(); } }
				else if (gamestate == -1) {
					if (resetsb) {
						resetsb = false;
						button_3_text.setString("Back");
						button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w - static_cast<int>(button_3_text.getGlobalBounds().width) - static_cast<int>(60.f * w / 800.f), h - static_cast<int>(h / 600.f * 90.f))));
						disbutton = false;
						disrandomnameLOL = true;
					}
					else {
						visible = false; gamestate = 1; button_1_text.setString("Resume"); button_2_text.setString("Options"); button_3_text.setString("Save Options"); button_1_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_1_text.getGlobalBounds().width) / 2, static_cast<int>(h / 600.f * 35.f)))); button_2_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_2_text.getGlobalBounds().width) / 2, h / 2 - static_cast<int>(h / 600.f * 40.f)))); button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_3_text.getGlobalBounds().width) / 2, h - static_cast<int>(h / 600.f * 90.f)))); button_1 = button_1_text.getGlobalBounds(); button_2 = button_2_text.getGlobalBounds(); button_3 = button_3_text.getGlobalBounds(); sviewchange(lsetPos);
					}
				}
				disbutton = false;
				disrandomnameLOL = true;
			}
			else if (mainevent.key.code == sf::Keyboard::BackSpace) {
				if (gamestate == 3 && !fullscreen) {
					if (resbutton1_focus && fullone.length() != 0U) { fullone.pop_back(); resbutton1_text.setString(fullone); }
					else if (resbutton2_focus && fulltwo.length() != 0U) { fulltwo.pop_back(); resbutton2_text.setString(fulltwo); }
				}
				else if (enternew && !newname.getString().isEmpty())
				{
					newname.setString(newname.getString().substring(0, newname.getString().getSize() - 1));
					newname.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(newname.getGlobalBounds().width) / 2, h / 2 - static_cast<int>(ctext.getGlobalBounds().height*0.6f))));
				}
			}
			else if (mainevent.key.code == sf::Keyboard::Return) {
				if (gamestate == 3 && !fullscreen) {
					resbutton1_focus = false; resbutton2_focus = false;
					if (static_cast<unsigned int>(stoi(fullone)) > desktop.x) { fullone = std::to_string(desktop.x); resbutton1_text.setString(fullone); }
					else if (stoi(fullone) < 800) { fullone = "800"; resbutton1_text.setString(fullone); }
					if (static_cast<unsigned int>(stoi(fulltwo)) > desktop.y) { fulltwo = std::to_string(desktop.y); resbutton2_text.setString(fulltwo); }
					else if (stoi(fulltwo) < 600) { fulltwo = "600"; resbutton2_text.setString(fulltwo); }
				}
				else if (gamestate > 5 && enternew)
					CreateNew();
			}
			else if (mainevent.key.code == sf::Keyboard::LAlt || mainevent.key.code == sf::Keyboard::RAlt) alt = true;
			if (mainevent.key.code == sf::Keyboard::F4)
			{
				if (alt)
				{
					quit = true;
					SaveOptions();
				}
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
					if (floor(menucapacity / 2U) <= (profiles.size() - 1U) - selectionp && arrowedp > 0)
					{
						pcheck = true;
						arrowedp -= 1;
					}
					if (selectionp > 0)
					{
						selectionp -= 1;
						if (!scenario.sempty && !scenario.pempty) scenario.savefile = L"bin/Saves/" + profiles[selectionp].getString().toWideString() + L"_" + stories[selections].getString().toWideString() + L".txt";
						pcheck = true;
					}
				}
				else if (gamestate == 7 && !k_delete && !enternew)
				{
					if (floor(menucapacity / 2U) <= (stories.size() - 1U) - selections && arroweds > 0)
					{
						scheck = true;
						arroweds -= 1;
					}
					if (selections > 0)
					{
						selections -= 1;
						if (!scenario.sempty && !scenario.pempty)  scenario.savefile = L"bin/Saves/" + profiles[selectionp].getString().toWideString() + L"_" + stories[selections].getString().toWideString() + L".txt";
						scheck = true;
					}
				}
			}
			else if (mainevent.key.code == sf::Keyboard::Down)
			{
				if (gamestate == 6 && !k_delete && !enternew)
				{
					if (selectionp >= menucapacity / 2U && arrowedp < arrowedp_margin)
					{
						pcheck = true;
						arrowedp += 1;
					}
					if (selectionp < profiles.size() - 1U)
					{
						selectionp += 1;
						if (!scenario.sempty && !scenario.pempty)  scenario.savefile = L"bin/Saves/" + profiles[selectionp].getString().toWideString() + L"_" + stories[selections].getString().toWideString() + L".txt";
						pcheck = true;
					}
				}
				else if (gamestate == 7 && !k_delete && !enternew)
				{
					if (selections >= menucapacity / 2U && arroweds < arroweds_margin)
					{
						scheck = true;
						arroweds += 1;
					}
					if (selections < stories.size() - 1U)
					{
						selections += 1;
						if (!scenario.sempty && !scenario.pempty)  scenario.savefile = L"bin/Saves/" + profiles[selectionp].getString().toWideString() + L"_" + stories[selections].getString().toWideString() + L".txt";
						scheck = true;
					}
				}
			}
			break;
		case sf::Event::MouseWheelScrolled:
			if (!stigger)
			{
				if (scenario.slideratv)
				{
					if (gamestate == 1) {
						lsetPos -= mainevent.mouseWheelScroll.delta * static_cast<float>(smax) / static_cast<float>(scenario.st); //delta (1 or -1) is the move of slider
						sviewchange(lsetPos);
					}
					else if (gamestate == -1)
					{
						ssetPos -= mainevent.mouseWheelScroll.delta * static_cast<float>(smax) / static_cast<float>(scenario.st);
						sviewchange(ssetPos);
					}
				}
			}
			if (gamestate == 6){
				selectionp -= mainevent.mouseWheelScroll.delta;
				arrowedp = selectionp - static_cast<int>(menucapacity)/2; //the cast is done automatically
				if (arrowedp < 0) arrowedp = 0;
				else if (arrowedp > arrowedp_margin) arrowedp = arrowedp_margin;
				if (selectionp < 0) selectionp = 0;
				else if (selectionp >= profiles.size()) selectionp = profiles.size() - 1; 
				if (!scenario.sempty && !scenario.pempty) scenario.savefile = L"bin/Saves/" + profiles[selectionp].getString().toWideString() + L"_" + stories[selections].getString().toWideString() + L".txt";
				pcheck = true;
				LoadSave();
			}
			else if (gamestate == 7)
			{
				selections -= mainevent.mouseWheelScroll.delta;
				arroweds = selections - static_cast<int>(menucapacity)/2; //the cast is done automatically
				if (arroweds < 0) arroweds = 0;
				else if (arroweds > arroweds_margin) arroweds = arroweds_margin;
				if (selections < 0) selections = 0;
				else if (selections >= stories.size()) selections = stories.size() - 1;
				if (!scenario.sempty && !scenario.pempty) scenario.savefile = L"bin/Saves/" + profiles[selectionp].getString().toWideString() + L"_" + stories[selections].getString().toWideString() + L".txt";
				scheck = true;
				scenario.path = "bin/Scripts/" + stories[selections].getString() + ".txt";
				LoadSave();
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
						if (fullone.length() < 4) {
							fullone += mainevent.text.unicode;
							resbutton1_text.setString(fullone);
						}
					}
					else if (resbutton2_focus) {
						if (fulltwo.length() < 4) {
							fulltwo += mainevent.text.unicode;
							resbutton2_text.setString(fulltwo);
						}
					}
				}
			}
			else if (enternew && (gamestate == 6 || gamestate == 7))
			{
				const sf::Uint32 &achar = mainevent.text.unicode;
				if (newname.getString().getSize() < 13U && achar > 31U && achar < 127U && achar != 47U && achar != 92U && achar != 58U && achar != 42U && achar != 63U && achar != 34U && achar != 60U && achar != 62U && achar != 124U) {
					newname.setString(newname.getString() + achar);
					newname.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(newname.getGlobalBounds().width) / 2, h / 2 - static_cast<int>(ctext.getGlobalBounds().height*0.6f))));
				}
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
				resetsb = false;
				button_3_text.setString("Back");
				button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w - static_cast<int>(button_3_text.getGlobalBounds().width) - static_cast<int>(60.f * w / 800.f), h - static_cast<int>(h / 600.f * 90.f))));
				disbutton = false;
				disrandomnameLOL = true;
			}
			else if (Contains(button_3)) {
				Reset();
				gamestate = 1;
				visible = false;
				button_1_text.setString("Resume"); 
				button_2_text.setString("Options"); 
				button_3_text.setString("Save Options"); 
				button_1_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_1_text.getGlobalBounds().width) / 2, static_cast<int>(h / 600.f * 35.f)))); 
				button_2_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_2_text.getGlobalBounds().width) / 2, h / 2 - static_cast<int>(h / 600.f * 40.f)))); 
				button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_3_text.getGlobalBounds().width) / 2, h - static_cast<int>(h / 600.f * 90.f))));
				disbutton = false;
				disrandomnameLOL = true;
				sviewchange(lsetPos);
			}
		}
		else if (Contains(button_3)) {
			visible = false;
			gamestate = 1;
			button_3_text.setString("Save Options"); button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_3_text.getGlobalBounds().width / 2.f), h - static_cast<int>(h / 600.f * 90.f))));
			button_2_text.setString("Options"); button_2_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_2_text.getGlobalBounds().width / 2.f), h / 2 - static_cast<int>(h / 600.f * 40.f))));
			sviewchange(lsetPos);
		}
		break;
	case 0:
		if (Contains(button_1)) { visible = false; gamestate = 1; }
		else if (Contains(button_2)) {
			gamestate = 2; button_1_text.setString("Graphics"); button_2_text.setString("Audio"); button_3_text.setString("Back"); button_1_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_1_text.getGlobalBounds().width) / 2, static_cast<int>(h / 600.f * 35.f)))); button_2_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_2_text.getGlobalBounds().width) / 2, h / 2 - static_cast<int>(h / 600.f * 40.f)))); button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_3_text.getGlobalBounds().width) / 2, h - static_cast<int>(h / 600.f * 90.f))));
		}
		else if (Contains(button_3)) {
			gamestate = 5; button_1_text.setString("Change Profile"); button_2_text.setString("Change Story"); button_3_text.setString("Back"); button_1_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_1_text.getGlobalBounds().width) / 2, static_cast<int>(h / 600.f * 35.f)))); 	button_2_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_2_text.getGlobalBounds().width) / 2, h / 2 - static_cast<int>(h / 600.f * 40.f)))); button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_3_text.getGlobalBounds().width) / 2, h - static_cast<int>(h / 600.f * 90.f))));
		}
		break;
	case 1:
		if (stigger) {
			stigger = false;
			slidersb = sliders.getGlobalBounds();
		}
		break;
	case 2:
		if (Contains(button_1)) {
			gamestate = 3; button_1_text.setString(""); button_2_text.setString("Fullscreen"); button_3_text.setString("Apply"); button_1_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_1_text.getGlobalBounds().width) / 2, static_cast<int>(h / 600.f * 35.f)))); button_2_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_2_text.getGlobalBounds().width) / 2, h / 2 - static_cast<int>(h / 600.f * 40.f)))); button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_3_text.getGlobalBounds().width) / 2, h - static_cast<int>(h / 600.f * 90.f))));
		}
		else if (Contains(button_2)) {
			gamestate = 4; button_1_text.setString("Music"); button_2_text.setString("Sound"); button_3_text.setString("Apply"); button_1_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_1_text.getGlobalBounds().width) / 2, static_cast<int>(h / 600.f * 35.f)))); button_2_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_2_text.getGlobalBounds().width) / 2, h / 2 - static_cast<int>(h / 600.f * 40.f)))); button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_3_text.getGlobalBounds().width) / 2, h - static_cast<int>(h / 600.f * 90.f))));
		}
		else if (Contains(button_3)) {
			gamestate = 0; button_1_text.setString("Resume"); button_2_text.setString("Options"); button_3_text.setString("Save Options"); button_1_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_1_text.getGlobalBounds().width) / 2, static_cast<int>(h / 600.f * 35.f)))); button_2_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_2_text.getGlobalBounds().width) / 2, h / 2 - static_cast<int>(h / 600.f * 40.f)))); button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_3_text.getGlobalBounds().width) / 2, h - static_cast<int>(h / 600.f * 90.f))));
		}
		break;
	case 3:
		if (Contains(button_2)) {
			if (!fullscreen) { resbutton1_focus = false; resbutton2_focus = false; fullscreen = true; int cw = desktop.x; int ch = desktop.y; fullone = std::to_string(cw); fulltwo = std::to_string(ch); resbutton1_text.setString(fullone); resbutton2_text.setString(fulltwo); }
			else fullscreen = false;
		}
		else if (Contains(button_3)) {
			resbutton1_focus = false; resbutton2_focus = false; gamestate = 2; button_1_text.setString("Graphics"); button_2_text.setString("Audio"); button_3_text.setString("Back"); button_1_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_1_text.getGlobalBounds().width) / 2, static_cast<int>(h / 600.f * 35.f)))); 	button_2_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_2_text.getGlobalBounds().width) / 2, h / 2 - static_cast<int>(h / 600.f * 40.f)))); button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_3_text.getGlobalBounds().width) / 2, h - static_cast<int>(h / 600.f * 90.f)))); SaveOptions();
		}
		break;
	case 4:
		if (Contains(button_1)) music = !music;
		else if (Contains(button_2)) sound = !sound;
		else if (Contains(button_3)) {
			gamestate = 2; button_1_text.setString("Graphics"); button_2_text.setString("Audio"); button_3_text.setString("Back"); button_1_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_1_text.getGlobalBounds().width) / 2, static_cast<int>(h / 600.f * 35.f)))); button_2_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_2_text.getGlobalBounds().width) / 2, h / 2 - static_cast<int>(h / 600.f * 40.f)))); button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_3_text.getGlobalBounds().width) / 2, h - static_cast<int>(h / 600.f * 90.f)))); SaveOptions();
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
			gamestate = 0; button_1_text.setString("Resume"); button_2_text.setString("Options"); button_3_text.setString("Save Options"); button_1_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_1_text.getGlobalBounds().width) / 2, static_cast<int>(h / 600.f * 35.f)))); button_2_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_2_text.getGlobalBounds().width) / 2, h / 2 - static_cast<int>(h / 600.f * 40.f)))); button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_3_text.getGlobalBounds().width) / 2, h - static_cast<int>(h / 600.f * 90.f))));
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
			visible = false; gamestate = 5; button_1_text.setString("Change Profile"); button_2_text.setString("Change Story"); button_3_text.setString("Back"); button_1_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_1_text.getGlobalBounds().width) / 2, static_cast<int>(h / 600.f * 35.f)))); button_2_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_2_text.getGlobalBounds().width) / 2, h / 2 - static_cast<int>(h / 600.f * 40.f)))); button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_3_text.getGlobalBounds().width) / 2, h - static_cast<int>(h / 600.f * 90.f)))); pcheck = true; SaveOptions();
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
			visible = false; gamestate = 5; button_1_text.setString("Change Profile"); button_2_text.setString("Change Story"); button_3_text.setString("Back"); button_1_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_1_text.getGlobalBounds().width) / 2, static_cast<int>(h / 600.f * 35.f)))); button_2_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_2_text.getGlobalBounds().width) / 2, h / 2 - static_cast<int>(h / 600.f * 40.f)))); button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_3_text.getGlobalBounds().width) / 2, h - static_cast<int>(h / 600.f * 90.f)))); button_1 = button_1_text.getGlobalBounds(); button_2 = button_2_text.getGlobalBounds(); button_3 = button_3_text.getGlobalBounds(); scheck = true; SaveOptions();
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
			smouseposy = mousepos.y - static_cast<int>(slidersb.top);
			stigger = true;
		}
		else if (Contains(resets_b)) {
			resetsb = true;
			button_3_text.setString("Yes");
			button_3_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w - static_cast<int>(button_3_text.getGlobalBounds().width + 60.f * w / 800.f), h - static_cast<int>(h / 600.f * 90.f))));
			button_2_text.setPosition(window.mapPixelToCoords(sf::Vector2i(static_cast<int>(60.f * w / 800.f), h - static_cast<int>(h / 600.f * 90.f))));
		}
		break;
	case 1:
		if (!stigger && scenario.slideratv && Contains(slidersb)) {
			smouseposy = mousepos.y - static_cast<int>(slidersb.top);
			stigger = true;
		}
		{
			int x = 0;
			for (Choice &a : scenario.choice) {
				if (a.avaible) {
					if (Contains(a.c.getGlobalBounds()))
					{
						for (Choice &d : scenario.choice) d.cs.setFillColor(sf::Color(static_cast<sf::Uint8>(0), static_cast<sf::Uint8>(0), static_cast<sf::Uint8>(0), static_cast<sf::Uint8>(0)));
						a.cs.setFillColor(textchoicefillcolor);
						scenario.choicesel = x;
						break;
					}
					else if (Contains(a.cs.getGlobalBounds()))
					{
						for (Choice &d : scenario.choice) d.cs.setFillColor(sf::Color(static_cast<sf::Uint8>(0), static_cast<sf::Uint8>(0), static_cast<sf::Uint8>(0), static_cast<sf::Uint8>(0)));
						a.cs.setFillColor(textchoicefillcolor);
						scenario.choicesel = x;
						break;
					}
				}
				x++;
			}
		}
		ssb();
		break;
	case 3:
		if (Contains(resbutton1)) { resbutton1_focus = true; resbutton2_focus = false; if (static_cast<unsigned int>(stoi(fulltwo)) > desktop.y) { fulltwo = std::to_string(desktop.y); resbutton2_text.setString(fulltwo); } else if (stoi(fulltwo) < 600) { fulltwo = "600"; resbutton2_text.setString(fulltwo); } }
		else if (Contains(resbutton2)) { resbutton1_focus = false; resbutton2_focus = true; if (static_cast<unsigned int>(stoi(fullone)) > desktop.x) { fullone = std::to_string(desktop.x); resbutton1_text.setString(fullone); } else if (stoi(fullone) < 800) { fullone = "800"; resbutton1_text.setString(fullone); } }
		else {
			resbutton1_focus = false; resbutton2_focus = false;
			if (fullone.length() != 0U) {
				if (static_cast<unsigned int>(stoi(fullone)) > desktop.x) {
					fullone = std::to_string(desktop.x); resbutton1_text.setString(fullone);
				}
				else if (stoi(fullone) < 800) { fullone = "800"; resbutton1_text.setString(fullone); }
			}
			else {
				fullone = "800"; resbutton1_text.setString(fullone);
			}
			if (fulltwo.length() != 0U){
				if (static_cast<unsigned int>(stoi(fulltwo)) > desktop.y) {
					fulltwo = std::to_string(desktop.y); resbutton2_text.setString(fulltwo);
				}
				else if (stoi(fulltwo) < 600) { fulltwo = "600"; resbutton2_text.setString(fulltwo); }
			}
			else {
				fulltwo = "600"; resbutton2_text.setString(fulltwo);
			}
		}
		break;
	case 6:
		if (!k_delete && !enternew) {
			if (Contains(arrowdn_b)) {
				if (selectionp >= menucapacity / 2U && arrowedp < arrowedp_margin)
					arrowedp += 1;
				if (selectionp < profiles.size() - 1U) {
					selectionp += 1;
				}
				pcheck = true;
				LoadSave();
			}
			else if (Contains(arrowup_b)) {
				if (menucapacity / 2U <= (profiles.size() - 1U) - selectionp && arrowedp > 0) 
					arrowedp -= 1;
				if (selectionp > 0) {
					selectionp -= 1;
					if (!scenario.sempty && !scenario.pempty) scenario.savefile = L"bin/Saves/" + profiles[selectionp].getString().toWideString() + L"_" + stories[selections].getString().toWideString() + L".txt";
				}
				pcheck = true;
				LoadSave();
			}
			else {
				for (unsigned int repeated = 0U, size = profiles.size(); repeated < menucapacity && repeated < size; ++repeated) {
					if (Contains(profiles[arrowedp + repeated].getGlobalBounds()) && selectionp != repeated) {
						selectionp = arrowedp + repeated;
						if (!scenario.sempty && !scenario.pempty) scenario.savefile = L"bin/Saves/" + profiles[selectionp].getString().toWideString() + L"_" + stories[selections].getString().toWideString() + L".txt";
						arrowedp += repeated - menucapacity / 2U;
						if (arrowedp < 0) arrowedp = 0;
						else if (arrowedp > arrowedp_margin) arrowedp = arrowedp_margin;
						pcheck = true;
						LoadSave();
					}
				}
			}
		}
		break;
	case 7:
		if (!k_delete && !enternew) {
			if (Contains(arrowdn_b)) {
				if (selections >= menucapacity / 2U && arroweds < arroweds_margin)
					arroweds += 1;
				if (selections < stories.size() - 1U) {
					selections += 1;
					if (!scenario.sempty && !scenario.pempty) scenario.savefile = L"bin/Saves/" + profiles[selectionp].getString().toWideString() + L"_" + stories[selections].getString().toWideString() + L".txt";
				}
				scheck = true;
				scenario.path = "bin/Scripts/" + stories[selections].getString() + ".txt";
				LoadSave();
			}
			else if (Contains(arrowup_b)) {
				if (floor(menucapacity / 2U) <= (stories.size() - 1U) - selections && arroweds > 0)
					arroweds -= 1;
				if (selections > 0) {
					selections -= 1;
					if (!scenario.sempty && !scenario.pempty) scenario.savefile = L"bin/Saves/" + profiles[selectionp].getString().toWideString() + L"_" + stories[selections].getString().toWideString() + L".txt";
				}
				scheck = true;
				scenario.path = "bin/Scripts/" + stories[selections].getString() + ".txt";
				LoadSave();
			}
			else {
				for (unsigned int repeated = 0U, size = stories.size(); repeated < menucapacity && repeated < size; ++repeated) {
					if (Contains(stories[arroweds + repeated].getGlobalBounds()) && selections != repeated) {
						selections = arroweds + repeated;
						if (!scenario.sempty && !scenario.pempty) scenario.savefile = L"bin/Saves/" + profiles[selectionp].getString().toWideString() + L"_" + stories[selections].getString().toWideString() + L".txt";
						arroweds += repeated - menucapacity / 2U;
						if (arroweds < 0) arroweds = 0;
						else if (arroweds > arroweds_margin) arroweds = arroweds_margin;
						scheck = true;
						scenario.path = "bin/Scripts/" + stories[selections].getString() + ".txt";
						LoadSave();
					}
				}
			}
		}
		break;
	}
}
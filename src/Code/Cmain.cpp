/*
@Author: LightTab2
The MIT License(MIT)

Copyright(c) 2016 LightTab2 azorro12@gmail.com
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and / or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "Cmain.h"
#include <ctime>
#include <windows.h>
//Personal challenge - multithreading in Fades.cpp

unsigned int priorlimit = 5;
Cmain::Cmain()
{
	CreateDirectory(L"bin", NULL);
	CreateDirectory(L"bin/Fonts", NULL);
	CreateDirectory(L"bin/Images", NULL);
	CreateDirectory(L"bin/Logs", NULL);
	CreateDirectory(L"bin/Saves", NULL);
	CreateDirectory(L"bin/Scripts", NULL);
		LoadOptions(); //reading from ini
		Background_texture.loadFromFile("bin/Images/gradient.png");
		michaupase�ke�_t.loadFromFile("bin/Images/margin.png");
		scenario.next_t.loadFromFile("bin/Images/Next.png");
		font.loadFromFile("bin/Fonts/Fontformenu.ttf");
		font2.loadFromFile("bin/Fonts/Fontforgametext.ttf");
		slider.loadFromFile("bin/Images/Slider.png");
		bar.loadFromFile("bin/Images/Bar.png");
		arrowup_t.loadFromFile("bin/Images/ArrowUP.png");
		arrowdn_t.loadFromFile("bin/Images/Arrow.png");
		reset_t.loadFromFile("bin/Images/Reset.png");
		//textures loaded
		f14_text.setString("Press Alt + F4 to quit");
		enternewerror_t.setString("Error: There's already an object with the same name");
		shwstats_t.loadFromFile("bin/Images/Show.png");
		button_1_text.setString("Lightine");
		button_2_text.setString("Options");
		button_3_text.setString("Save Options");
		ctext.setString("Are you sure?");
		//strings set
		scenario.tekst.setFont(font2);
		button_1_text.setFont(font);
		button_2_text.setFont(font);
		button_3_text.setFont(font);
		resbutton1_text.setFont(font);
		resbutton2_text.setFont(font);
		ctext.setFont(font);
		f14_text.setFont(font);
		enternewerror_t.setFont(font);
		//fonts set
		Background.setTexture(Background_texture);
		michaupase�ke�.setTexture(michaupase�ke�_t);
		scenario.next.setTexture(scenario.next_t);
		sliders.setTexture(slider);
		bars.setTexture(bar);
		arrowup.setTexture(arrowup_t);
		arrowdn.setTexture(arrowdn_t);
		showstats.setTexture(shwstats_t);
		resets.setTexture(reset_t);
		//textures set
		button_1_text.setFillColor(menucolor);
		scenario.tekst.setFillColor(textcolor);
		button_2_text.setFillColor(menucolor);
		button_3_text.setFillColor(menucolor);
		resbutton1_text.setFillColor(menuwidthcolor);
		resbutton2_text.setFillColor(menuheightcolor);
		ctext.setFillColor(menucolor);
		f14_text.setFillColor(menuhelpcolor);
		resbutton1_shape.setFillColor(menuwidthfillcolor);
		resbutton2_shape.setFillColor(menuheightfillcolor);
		resbutton1_shape.setOutlineColor(menuwidthoutlinecolor);
		resbutton2_shape.setOutlineColor(menuheightoutlinecolor);
		profilesmenu.setFillColor(menuprofilesmenufillcolor);
		profilesmenu.setOutlineColor(menuprofilesmenuoutlinecolor); 
		arrowdn.setColor(sf::Color(static_cast<sf::Uint8>(255), static_cast<sf::Uint8>(255), static_cast<sf::Uint8>(255), static_cast<sf::Uint8>(0)));
		arrowup.setColor(arrowdn.getColor());
		//colors set
		scenario.textcolor.reset(&textcolor);
		sSaveOptions();
}

Cmain::~Cmain()
{
	scenario.textcolor.release();
	scenario.textchoiceunavaiblecolor.release();
}

void Cmain::sSaveOptions()	//anyone who would like to analyze this code... it's not necessary, just add something at the end of it; read its comment
{
	fullone = std::to_string(w);	//resbutton1's string
	fulltwo = std::to_string(h);	//resbutton2's string
	cfullone = fullone;
	cfulltwo = fulltwo;
	cfullscreen = fullscreen;
	cselectionp = selectionp;
	cselections = selections;
	csound = sound;
	cmusic = music;
	//control variables set
	createWindow();

	scenario.owd = w - w / 18;
	if (w < 1200) scenario.tekst.setCharacterSize(fontsize1);
	else if (w < 1600) scenario.tekst.setCharacterSize(fontsize2);
	else scenario.tekst.setCharacterSize(fontsize3);
	scenario.tekst.setString(L"WMP�ʹ�jpgqiL"); //Setting the most wide and long characters
	ctext.setCharacterSize(h / 10 + h / 120);
	button_1_text.setCharacterSize(h / 10 + h / 120);
	button_2_text.setCharacterSize(h / 10 + h / 120);
	button_3_text.setCharacterSize(h / 10 + h / 120);
	resbutton1_text.setCharacterSize(h / 10 + h / 120);
	resbutton2_text.setCharacterSize(h / 10 + h / 120);
	f14_text.setCharacterSize(h / 30);
	profilesmenu.setOutlineThickness(h / 150);
	resbutton1_shape.setOutlineThickness(h / 300);
	resbutton2_shape.setOutlineThickness(h / 300);
	help_text = f14_text;
	help_text.setString("Press Delete to remove");
	f14_text.setPosition(w - floor(help_text.getGlobalBounds().width + 6.f * w/800.f), h - floor(f14_text.getGlobalBounds().height + 2.f * h/600.f));
	help_text.setPosition(w - floor(help_text.getGlobalBounds().width + 6.f * w / 800.f), h - floor(f14_text.getGlobalBounds().height + 2.f * h / 600.f));

	newname = ntext = ctext;
	newname.setFillColor(menucolor);
	newname.setString("");
	newname.setPosition(w / 2 - floor(newname.getGlobalBounds().width / 2), h / 2 - floor(ctext.getGlobalBounds().height *0.6f));
	ntext.setString("Enter name:");
	ntext.setPosition(w / 2 - floor(ntext.getGlobalBounds().width / 2), h / 2 - floor(ntext.getGlobalBounds().height*2));
	enternewerror_t.setCharacterSize(h / 30);
	enternewerror_t.setPosition(w / 2 - floor(enternewerror_t.getGlobalBounds().width / 2), h / 2 - floor(ntext.getGlobalBounds().height*2 + enternewerror_t.getGlobalBounds().height * 1.4f));
	enternewerror_t.setFillColor(menuerrorcolor);

	std::string	sizer = "0000";	//Like resbuttons were already filled
	resbutton1_text.setString(sizer);
	resbutton2_text.setString(sizer);
	resbutton1_shape.setSize(sf::Vector2f(floor(resbutton1_text.getGlobalBounds().width + 4.f * (w + h) / 1400.f), floor(resbutton1_text.getGlobalBounds().height + 3.f * w / 800.f)));
	resbutton2_shape.setSize(sf::Vector2f(floor(resbutton2_text.getGlobalBounds().width + 4.f * (w + h) / 1400.f), floor(resbutton2_text.getGlobalBounds().height + 3.f * w / 800.f)));

	Background.setScale(1, 1);
	Background.setScale(w / Background.getGlobalBounds().width, h / Background.getGlobalBounds().height);
	bars.setScale(w / 800.f, h / 600.f);
	sliders.setScale(bars.getScale().x, bars.getScale().x);
	michaupase�ke�.setScale((w + h) / 1400.f, (w + h) / 1400.f);
	arrowup.setScale((w + h) / 12200.f, (w + h) / 11200.f);
	arrowdn.setScale(arrowup.getScale());
	scenario.next.setScale(arrowup.getScale().x*2.f, arrowup.getScale().y*2.f);
	resets.setScale((w + h) / 5600.f, michaupase�ke�.getScale().y/4.f);
	showstats.setScale(resets.getScale());
	Background.setPosition(0, 0);
	michaupase�ke�.setPosition(0, 0);
	ctext.setPosition(w / 2 - floor(ctext.getGlobalBounds().width / 2), h / 2 - floor(ctext.getGlobalBounds().height*2));
	button_1_text.setString("Resume"); button_2_text.setString("Options"); button_3_text.setString("Save Options");
	button_1_text.setPosition(w / 2 - floor(button_1_text.getGlobalBounds().width / 2), floor(h / 600.f * 35.f));
	button_2_text.setPosition(w / 2 - floor(button_2_text.getGlobalBounds().width / 2), h / 2 - floor(h / 600.f * 40.f));
	button_3_text.setPosition(w / 2 - floor(button_3_text.getGlobalBounds().width / 2), h - floor(h / 600.f * 90.f));
	resbutton1_text.setPosition(w / 2 - floor(w / 800.f * 120.f + resbutton1_shape.getGlobalBounds().width), floor(h / 600.f * 25.f));
	resbutton1_shape.setPosition(floor(resbutton1_text.getGlobalBounds().left - 4.f * (w + h) / 1400.f), floor(resbutton1_text.getGlobalBounds().top - 2.f * h / 600.f));
	resbutton2_text.setPosition(w / 2 + floor(w / 800.f * 120.f), floor(h / 600.f * 25.f));
	resbutton2_shape.setPosition(floor(resbutton2_text.getGlobalBounds().left - 4.f * (w + h) / 1400.f), floor(resbutton2_text.getGlobalBounds().top - 2.f * h / 600.f));
	resbutton1_text.setString(fullone);
	resbutton2_text.setString(fulltwo);
	profilesmenu.setSize(sf::Vector2f(floor(0.75f * w), round(h * 0.95f - 2 * arrowup.getGlobalBounds().height)));
	profilesmenu.setPosition(round(w * 0.125f), round((h - profilesmenu.getSize().y)/2));
	arrowup.setPosition(profilesmenu.getPosition().x + round((profilesmenu.getGlobalBounds().width - arrowup.getGlobalBounds().width)/2.f), profilesmenu.getGlobalBounds().top - round(arrowup.getGlobalBounds().height + 4.f * h / 600.f));
	arrowdn.setPosition(arrowup.getPosition().x, profilesmenu.getGlobalBounds().top + profilesmenu.getGlobalBounds().height + round(4.f * h / 600.f));
	bars.setPosition(round(w - bars.getGlobalBounds().width), 0);
	smaxdown = h - static_cast<int>(h / 600.f * 8.f);
	sliders.setPosition(round(bars.getPosition().x + floor(w / 800.f * 6.f)), floor(h / 600.f * 11.f));
	smaxup = static_cast<int>(h / 600.f * 11.f);
	showstats.setPosition(round(w - showstats.getGlobalBounds().width - bars.getGlobalBounds().width - floor(w / 800.f * 40.f)), 0);
	showstats.setColor(sf::Color(255, 255, 255, 0));
	resets.setPosition(w + floor((showstats.getGlobalBounds().width - resets.getGlobalBounds().width) / 2) - showstats.getGlobalBounds().width - bars.getGlobalBounds().width - floor(w / 800.f * 40.f), 0);
	resets.setColor(sf::Color(255,255,255,0));
	showstats.setColor(resets.getColor());
	resbutton1 = resbutton1_shape.getGlobalBounds();
	resbutton2 = resbutton2_shape.getGlobalBounds();
	resets_b = resets.getGlobalBounds();
	shwstats = showstats.getGlobalBounds();
	arrowup_b = arrowup.getGlobalBounds();
	arrowdn_b = arrowdn.getGlobalBounds();
	slidersb = sliders.getGlobalBounds();
	button_1 = button_1_text.getGlobalBounds();
	button_2 = button_2_text.getGlobalBounds();
	button_3 = button_3_text.getGlobalBounds();
	pos[0] = static_cast<sf::Vector2i>(button_1_text.getPosition());
	pos[1] = static_cast<sf::Vector2i>(button_2_text.getPosition());
	pos[2] = static_cast<sf::Vector2i>(button_3_text.getPosition());
	pos[3] = static_cast<sf::Vector2i>(profilesmenu.getPosition());
	pos[4] = static_cast<sf::Vector2i>(f14_text.getPosition());
	pos[5] = static_cast<sf::Vector2i>(help_text.getPosition());
	pos[6] = static_cast<sf::Vector2i>(arrowup.getPosition());
	pos[7] = static_cast<sf::Vector2i>(arrowdn.getPosition());
	pos[8] = static_cast<sf::Vector2i>(ctext.getPosition());
	pos[9] = static_cast<sf::Vector2i>(enternewerror_t.getPosition());
	pos[10] = static_cast<sf::Vector2i>(newname.getPosition());
	pos[11] = static_cast<sf::Vector2i>(ntext.getPosition());
	pos[12] = static_cast<sf::Vector2i>(showstats.getPosition());
	pos[13] = static_cast<sf::Vector2i>(resbutton1_text.getPosition());
	pos[14] = static_cast<sf::Vector2i>(resbutton1_shape.getPosition());
	pos[15] = static_cast<sf::Vector2i>(resbutton2_text.getPosition());
	pos[16] = static_cast<sf::Vector2i>(resbutton2_shape.getPosition());
	pos[17] = static_cast<sf::Vector2i>(resets.getPosition());
	smax = smaxdown - smaxup - static_cast<int>(slidersb.height);
	scenario.th = static_cast<int>(scenario.tekst.getGlobalBounds().height) * 1.15f;
	getSaveData();
	//else scenario.mfile << "Error: there are no stories accessible (add some in game's menu)" << std::endl;
	scenario.path = "bin/Scripts/" + stories[selections].getString() + ".txt";
	LoadSave();
	resbutton1_focus = resbutton2_focus = clicked = resetsb = false;
	pcheck = scheck = true;
	lsetPos = ssetPos = smaxup;
}

void Cmain::SaveOptions()
{
	int cw, ch;
	ch = h;
	cw = w;
	//duplicates current variables, so 
	if (fullscreen) w = desktop.x;
	else w = scenario.stoicheck(fullone, 0);
	if (w < 800) w = 800;
	else if (static_cast<unsigned int>(w) > desktop.x) w = desktop.x;
	if (fullscreen) h = desktop.y;
	else h = scenario.stoicheck(fulltwo, 0);
	if (h < 600) h = 600;
	else if (static_cast<unsigned int>(h) > desktop.y) h = desktop.y;
	scenario.sw = w;
	scenario.sh = h;
	scenario.w1 = w / 18;
	scenario.w2 = w / 12;

	if (cfullscreen != fullscreen || w != cw || h != ch) 
	{
		window.close();
		sSaveOptions();
		SaveToFile();
	}
	else if (cselections != selections || cselectionp != selectionp || cmusic != music || csound != sound)
		SaveToFile();
}

inline void Cmain::createWindow()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = antialias;
	if (fullscreen) window.create(sf::VideoMode(w, h), "Lightine", sf::Style::Fullscreen, settings);
	else window.create(sf::VideoMode(w, h), "Lightine", sf::Style::Close, settings);
	window.setFramerateLimit(framelimit);
}

void Cmain::Intro()
{
	button_1_text.setString("Lightine");
	button_1_text.setCharacterSize(h / 5);
	button_1_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_1_text.getGlobalBounds().width) / 2, static_cast<int>(h / 600.f * 35.f))));
	button_1_text.setFillColor(sf::Color(menuclickcolor.r, menuclickcolor.g, menuclickcolor.b, static_cast<sf::Uint8>(0)));
	//changes button 1 so it's bigger and somewhere else
	sf::Text general;
	general.setFont(font);
	general.setCharacterSize(round((w + h) / 175.f));
	general.setFillColor(sf::Color(menuclickcolor.r, menuclickcolor.g, menuclickcolor.b, static_cast<sf::Uint8>(0)));
	std::wstring str = L"Copyright (c) 2016 LightTab2 azorro12@gmail.com";
	general.setString(str);
	int gh = general.getGlobalBounds().height * 1.15f, ghe = button_1_text.getGlobalBounds().top + button_1_text.getGlobalBounds().height * 1.25f;
	std::vector<sf::Text> cprght;
	cprght.push_back(general);
	ghe += gh;
	str = L"The software is licensed under MIT LICENSE, for more details see LICENSE.TXT";
	general.setString(str);
	general.setPosition(round(w * 0.005f), static_cast<float>(ghe)); //ignore warn
	cprght.push_back(general);
	ghe += gh;
	str = L"It couldn't be made without SFML";
	general.setString(str);
	general.setPosition(round(w * 0.005f), static_cast<float>(ghe)); //ignore warn
	cprght.push_back(general);
	ghe += 4 * gh;
	sf::Texture sfml; sfml.loadFromFile("bin/Images/sfml-logo-big.png");
	sf::Sprite sfml_s; sfml_s.setTexture(sfml); sfml_s.setScale((h+w)/5600.f, (h + w)/5600.f);
	sfml_s.setPosition(round(w * 0.005f), static_cast<float>(ghe));
	sfml_s.setColor(sf::Color(sf::Uint8(0), sf::Uint8(0), sf::Uint8(0), sf::Uint8(0)));
	ghe += 5 * gh + sfml_s.getGlobalBounds().height;
	str = L"Adittionaly I want to thank for resources I used:"; 
	general.setString(str);
	general.setPosition(round(w * 0.005f), static_cast<float>(ghe)); //ignore warn
	cprght.push_back(general);
	ghe += gh;
	int check2 = w * 0.975f;
	std::wifstream credits(L"bin/Credits.txt");
	while (std::getline(credits, str))
	{
		general.setPosition(round(w * 0.005f), static_cast<float>(ghe));
		general.setString(str);
		std::wstring strr;
		if (general.getGlobalBounds().left + general.getGlobalBounds().width < check2 || str.find(L' ') == std::wstring::npos) { cprght.push_back(general); ghe += gh; }
		else
		{
			std::size_t pos = 0;
			for (;;) {
				if ((pos = str.find(L' ', pos + 1)) == std::wstring::npos) { general.setString(str); if (general.getGlobalBounds().left + general.getGlobalBounds().width > check2) goto skip; general.setPosition(round(w * 0.005f), static_cast<float>(ghe)); cprght.push_back(general); ghe += gh; break; }
				general.setString(str.substr(0, pos));
				if (general.getGlobalBounds().left + general.getGlobalBounds().width > check2)
				{
				skip:general.setString(str.substr(0, (pos = str.rfind(L' ', pos - 1) + 1)));
					str.erase(0, pos);
					general.setPosition(round(w * 0.005f), static_cast<float>(ghe));
					cprght.push_back(general);
					ghe += gh;
  				}
			}
		}
	} 
	for (;;)
	{
		button_1_text.setFillColor(sf::Color(menuclickcolor.r, menuclickcolor.g, menuclickcolor.b, static_cast<sf::Uint8>(button_1_text.getFillColor().a + 1)));
		sfml_s.setColor(sf::Color(sf::Uint8(255), sf::Uint8(255), sf::Uint8(255), button_1_text.getFillColor().a));
		for (sf::Text &t : cprght) t.setFillColor(button_1_text.getFillColor());
		window.clear();
		window.draw(Background);
		window.draw(button_1_text);
		window.draw(sfml_s);
		for (sf::Text &t : cprght) window.draw(t);
		window.display();
		if (button_1_text.getFillColor().a == static_cast<sf::Uint8>(255))
		{
			Sleep(1500);
			button_1_text.setString("Resume");
			button_1_text.setCharacterSize(h / 10 + h / 120);
			button_1_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_1_text.getGlobalBounds().width / 2), static_cast<int>(h / 600.f * 35.f))));
			button_1 = button_1_text.getGlobalBounds();
			return; //go back to previous form
		}
	}
}

void Cmain::getSaveData()
{
	std::ifstream file;
	file.open("bin/Stories.txt");
	std::string insert; //Buffer for reading profiles
	sf::Text insert_text = newname;	
	insert_text.setFillColor(menustoriescolor);
	arrowedp = arroweds = 0;
	//reset zmiennych
	positions.clear();

	profiles.clear();
	
	stories.clear();
	for (;;)
	{
		if (!std::getline(file, insert)) break;
		insert_text.setString(insert);
		stories.push_back(insert_text);
	}
	if (selections >= stories.size()) selections = stories.size() - 1;
	insert_text.setFillColor(menuprofilescolor);
	file.close();
	file.open("bin/Profiles.txt");
	for (;;)
	{
		if (!std::getline(file, insert)) break;
		insert_text.setString(insert);
		profiles.push_back(insert_text);
	}
	if (selectionp >= profiles.size()) selectionp = profiles.size() - 1;
	if (profiles.empty()) scenario.pempty = true;
	else if (stories.empty()) { scenario.pempty = false; scenario.sempty = true; }
	else scenario.savefile = L"bin/Saves/" + profiles[selectionp].getString().toWideString() + L"_" + stories[selections].getString().toWideString() + L".txt";

	insert_text.setString("1234567890GgpPqQyYWwMmxXzZAaBb");
	int th = insert_text.getGlobalBounds().height * 1.15f;
	for (menucapacity = 0U; (profilesmenu.getPosition().y + profilesmenu.getGlobalBounds().height) > (insert_text.getPosition().y + floor(10.f * h / 600.f) + 2 * th); menucapacity += 1U)
	{
		positions.push_back(sf::Vector2f(profilesmenu.getPosition().x + floor(8.f * w/800.f), profilesmenu.getPosition().y + floor(5.f * h / 600.f) + th * menucapacity));
		insert_text.setPosition(positions.back());
	}
	arroweds_margin = stories.size() - menucapacity;
	arrowedp_margin = profiles.size() - menucapacity;
	if (arroweds_margin < 0) arroweds_margin = 0;
	if (arrowedp_margin < 0) arrowedp_margin = 0;
	arrowedp = selectionp - static_cast<int>(menucapacity/2U); //the cast is done automatically
	if (arrowedp < 0) arrowedp = 0;
	else if (arrowedp > arrowedp_margin) arrowedp = arrowedp_margin;
	arroweds = selections - static_cast<int>(menucapacity/2U); //the cast is done automatically
	if (arroweds < 0) arroweds = 0;
	else if (arroweds > arroweds_margin) arroweds = arroweds_margin;

}

void Cmain::setupMenu()
{
	if ((gwhich = (gamestate == 7)))
	{
		if (!scheck) return;
		for (unsigned int repeated = 0U, size = stories.size(); repeated < menucapacity && repeated < size; ++repeated)
		{
			stories[arroweds + repeated].setPosition(window.mapPixelToCoords(sf::Vector2i(positions[repeated])));
			if (selections == arroweds + repeated) stories[arroweds + repeated].setFillColor(menustoriesselectcolor);
			else stories[arroweds + repeated].setFillColor(menustoriescolor);
		}
		if (selections == 0) arrowed_up = true;
		else arrowed_up = false; 
		if (selections == stories.size() - 1U) arrowed_dn = true;
		else arrowed_dn = false;
		scheck = false;
	}
	else
	{
		if (!pcheck) return;
		for (unsigned int repeated = 0U, size = profiles.size(); repeated < menucapacity && repeated < size; ++repeated)
		{
			profiles[arrowedp + repeated].setPosition(window.mapPixelToCoords(sf::Vector2i(positions[repeated])));
			if (selectionp == arrowedp + repeated) profiles[arrowedp + repeated].setFillColor(menuprofilesselectcolor);
			else profiles[arrowedp + repeated].setFillColor(menuprofilescolor);
		}
		if (selectionp == 0U) arrowed_up = true;
		else arrowed_up = false;
		if (selectionp == profiles.size() - 1U) arrowed_dn = true;
		else arrowed_dn = false;
		pcheck = false;
	}
	if (k_delete) button_3_text.setString("Yes");
	else button_3_text.setString("Back");
	if (enternew) button_2_text.setString("Create");
	else if (k_delete) button_2_text.setString("No");
	else button_2_text.setString("New");
	button_2_text.setPosition(profilesmenu.getGlobalBounds().left + profilesmenu.getGlobalBounds().width - button_2_text.getGlobalBounds().width, profilesmenu.getGlobalBounds().top + profilesmenu.getGlobalBounds().height);
	button_3_text.setPosition(profilesmenu.getGlobalBounds().left, profilesmenu.getGlobalBounds().top + profilesmenu.getGlobalBounds().height);
	button_2 = button_2_text.getGlobalBounds();
	button_3 = button_3_text.getGlobalBounds();
	if (visible)
	{
		if (arrowed_dn) arrowdn.setColor(sf::Color(arrowdn.getColor().r, arrowdn.getColor().g, arrowdn.getColor().b, static_cast<sf::Uint8>(90)));
		else arrowdn.setColor(sf::Color(arrowdn.getColor().r, arrowdn.getColor().g, arrowdn.getColor().b, static_cast<sf::Uint8>(255)));
		if (arrowed_up) arrowup.setColor(sf::Color(arrowup.getColor().r, arrowup.getColor().g, arrowup.getColor().b, static_cast<sf::Uint8>(90)));
		else arrowup.setColor(sf::Color(arrowup.getColor().r, arrowup.getColor().g, arrowup.getColor().b, static_cast<sf::Uint8>(255)));
	}
}

void Cmain::CreateNew()
{
	std::string name; //name of new profile/story (all characters are lower)
	for (char &c : newname.getString().toAnsiString()) name.push_back(tolower(c)); //getting all chars to lower(can't create 2 files with the same name in Windows)
	enternewerror = false;
	if (!name.empty())
	{
		if (gwhich)
		{
			std::ofstream sfile("bin/Stories.txt", std::ios::trunc);
			std::string oldname;
			for (auto &s : stories)
			{
				oldname.clear();
				sfile << s.getString().toAnsiString() << std::endl;
				for (char &c : s.getString().toAnsiString()) oldname.push_back(tolower(c)); //getting all chars to lower
				if (oldname == name) enternewerror = true;
			}
			if (enternewerror)
			{
				enternewerror_t.setFillColor(sf::Color(menuerrorcolor.r, menuerrorcolor.g, menuerrorcolor.b, 255));
				errclock.restart();
				return;
			}
			stories.push_back(newname);
			newname.setString("");
			for (auto &s : profiles)
			{
				std::ofstream file("bin/Saves/" + s.getString().toAnsiString() + "_" + stories.back().getString().toAnsiString() + ".txt");
			}
			if (stories.size() > menucapacity) {
				arroweds += 1;
				arroweds_margin += 1;
			}
			scheck = true;
			enternew = false;
		}
		else
		{
			std::ofstream pfile("bin/Profiles.txt", std::ios::trunc);
			std::string oldname;
			for (auto &p : profiles) //checking if there's already a profile with the same name
			{
				oldname.clear();
				pfile << p.getString().toAnsiString() << std::endl;
				for (char &c : p.getString().toAnsiString()) oldname.push_back(tolower(c)); //getting all chars to lower
				if (oldname == name) enternewerror = true;
			}
			if (enternewerror)
			{
				enternewerror_t.setFillColor(sf::Color(menuerrorcolor.r, menuerrorcolor.g, menuerrorcolor.b, 255));
				errclock.restart();
				return;
			}
			profiles.push_back(newname);
			newname.setString("");
			for (auto &s : stories)
			{
				std::ofstream file("bin/Saves/" + profiles.back().getString().toAnsiString() + "_" + s.getString().toAnsiString() + ".txt");
			}
			if (profiles.size() > menucapacity) {
				arrowedp += 1;
				arrowedp_margin += 1;
			}
			pcheck = true;
			enternew = false;
		}
		if (profiles.empty()) scenario.pempty = true;
		else if (stories.empty()) { scenario.pempty = false; scenario.sempty = true; }
		else
		{
			scenario.pempty = scenario.sempty = false;
			scenario.path = "bin/Scripts/" + stories[selections].getString() + ".txt";
			LoadSave();
		}
	}
}

void Cmain::LoadOptions()
{
	std::ifstream reader("bin/Options.ini");
	std::string buffer;

	std::getline(reader, buffer);
	buffer.erase(0U, 13U);
	fullscreen = scenario.stoicheck(buffer);

	std::getline(reader, buffer);
	buffer.erase(0U, 8U);
	if (!fullscreen) w = scenario.stoicheck(buffer, 800);
	else w = desktop.x;
	if (w < 800) w = 800;
	else if (static_cast<unsigned int>(w) > desktop.x) w = desktop.x;

	std::getline(reader, buffer);
	buffer.erase(0U, 9U);
	if (!fullscreen) h = scenario.stoicheck(buffer, 600);
	else h = desktop.y;
	if (h < 600) h = 600;
	else if (static_cast<unsigned int>(h) > desktop.y) h = desktop.y;

	scenario.sw = w;
	scenario.sh = h;
	scenario.w1 = w / 18;
	scenario.w2 = w / 12;

	std::getline(reader, buffer);
	buffer.erase(0U, 8U);
	music = scenario.stoicheck(buffer, 1);

	std::getline(reader, buffer);
	buffer.erase(0U, 8U);
	sound = scenario.stoicheck(buffer, 1);

	std::getline(reader, buffer);
	buffer.erase(0U, 12U);
	fontsize1 = scenario.stoicheck(buffer, 44);

	std::getline(reader, buffer);
	buffer.erase(0U, 12U);
	fontsize2 = scenario.stoicheck(buffer, 58);

	std::getline(reader, buffer);
	buffer.erase(0U, 12U);
	fontsize3 = scenario.stoicheck(buffer, 76);

	std::getline(reader, buffer);
	buffer.erase(0U, 18U);
	selectionp = scenario.stoicheck(buffer);

	std::getline(reader, buffer);
	buffer.erase(0U, 16U);
	selections = scenario.stoicheck(buffer);

	std::getline(reader, buffer);
	buffer.erase(0U, 15U);
	antialias = scenario.stoicheck(buffer, 4);

	std::getline(reader, buffer);
	buffer.erase(0U, 17U);
	framelimit = scenario.stoicheck(buffer, 300);

	std::getline(reader, buffer);
	buffer.erase(0U, 13U);
	priorlimit = scenario.stoicheck(buffer, 5);

	std::getline(reader, buffer); buffer.erase(0U, 14U);
	textcolor.r = scenario.stoicheck(buffer, 0);
	std::getline(reader, buffer); buffer.erase(0U, 14U);
	textcolor.g = scenario.stoicheck(buffer, 0);
	std::getline(reader, buffer); buffer.erase(0U, 14U);
	textcolor.b = scenario.stoicheck(buffer, 0);
	textcolor.a = 0;

	std::getline(reader, buffer); buffer.erase(0U, 14U);
	menucolor.r = scenario.stoicheck(buffer, 188);
	std::getline(reader, buffer); buffer.erase(0U, 14U);
	menucolor.g = scenario.stoicheck(buffer, 188);
	std::getline(reader, buffer); buffer.erase(0U, 14U);
	menucolor.b = scenario.stoicheck(buffer, 228);

	std::getline(reader, buffer); buffer.erase(0U, 20U);
	menuselectcolor.r = scenario.stoicheck(buffer, 129);
	std::getline(reader, buffer); buffer.erase(0U, 20U);
	menuselectcolor.g = scenario.stoicheck(buffer, 129);
	std::getline(reader, buffer); buffer.erase(0U, 20U);
	menuselectcolor.b = scenario.stoicheck(buffer, 239);

	std::getline(reader, buffer); buffer.erase(0U, 19U);
	menuclickcolor.r = scenario.stoicheck(buffer, 67);
	std::getline(reader, buffer); buffer.erase(0U, 19U);
	menuclickcolor.g = scenario.stoicheck(buffer, 67);
	std::getline(reader, buffer); buffer.erase(0U, 19U);
	menuclickcolor.b = scenario.stoicheck(buffer, 249);

	std::getline(reader, buffer); buffer.erase(0U, 16U);
	menuoncolor.r = scenario.stoicheck(buffer, 121);
	std::getline(reader, buffer); buffer.erase(0U, 16U);
	menuoncolor.g = scenario.stoicheck(buffer, 195);
	std::getline(reader, buffer); buffer.erase(0U, 16U);
	menuoncolor.b = scenario.stoicheck(buffer, 120);

	std::getline(reader, buffer); buffer.erase(0U, 22U);
	menuonselectcolor.r = scenario.stoicheck(buffer, 81);
	std::getline(reader, buffer); buffer.erase(0U, 22U);
	menuonselectcolor.g = scenario.stoicheck(buffer, 225);
	std::getline(reader, buffer); buffer.erase(0U, 22U);
	menuonselectcolor.b = scenario.stoicheck(buffer, 70);

	std::getline(reader, buffer); buffer.erase(0U, 22U);
	menuonclickcolor.r = scenario.stoicheck(buffer, 34);
	std::getline(reader, buffer); buffer.erase(0U, 22U);
	menuonclickcolor.g = scenario.stoicheck(buffer, 255);
	std::getline(reader, buffer); buffer.erase(0U, 22U);
	menuonclickcolor.b = scenario.stoicheck(buffer, 38);

	std::getline(reader, buffer); buffer.erase(0U, 20U);
	menudangercolor.r = scenario.stoicheck(buffer, 225);
	std::getline(reader, buffer); buffer.erase(0U, 20U);
	menudangercolor.g = scenario.stoicheck(buffer, 141);
	std::getline(reader, buffer); buffer.erase(0U, 20U);
	menudangercolor.b = scenario.stoicheck(buffer, 150);

	std::getline(reader, buffer); buffer.erase(0U, 26U);
	menudangerselectcolor.r = scenario.stoicheck(buffer, 236);
	std::getline(reader, buffer); buffer.erase(0U, 26U);
	menudangerselectcolor.g = scenario.stoicheck(buffer, 91);
	std::getline(reader, buffer); buffer.erase(0U, 26U);
	menudangerselectcolor.b = scenario.stoicheck(buffer, 100);

	std::getline(reader, buffer); buffer.erase(0U, 25U);
	menudangerclickcolor.r = scenario.stoicheck(buffer, 255);
	std::getline(reader, buffer); buffer.erase(0U, 25U);
	menudangerclickcolor.g = scenario.stoicheck(buffer, 41);
	std::getline(reader, buffer); buffer.erase(0U, 25U);
	menudangerclickcolor.b = scenario.stoicheck(buffer, 51);

	std::getline(reader, buffer); buffer.erase(0U, 22U);
	menunodangercolor.r = scenario.stoicheck(buffer, 121);
	std::getline(reader, buffer); buffer.erase(0U, 22U);
	menunodangercolor.g = scenario.stoicheck(buffer, 195);
	std::getline(reader, buffer); buffer.erase(0U, 22U);
	menunodangercolor.b = scenario.stoicheck(buffer, 120);

	std::getline(reader, buffer); buffer.erase(0U, 28U);
	menunodangerselectcolor.r = scenario.stoicheck(buffer, 81);
	std::getline(reader, buffer); buffer.erase(0U, 28U);
	menunodangerselectcolor.g = scenario.stoicheck(buffer, 225);
	std::getline(reader, buffer); buffer.erase(0U, 28U);
	menunodangerselectcolor.b = scenario.stoicheck(buffer, 70);

	std::getline(reader, buffer); buffer.erase(0U, 27U);
	menunodangerclickcolor.r = scenario.stoicheck(buffer, 34);
	std::getline(reader, buffer); buffer.erase(0U, 27U);
	menunodangerclickcolor.g = scenario.stoicheck(buffer, 255);
	std::getline(reader, buffer); buffer.erase(0U, 27U);
	menunodangerclickcolor.b = scenario.stoicheck(buffer, 38);

	std::getline(reader, buffer); buffer.erase(0U, 19U);
	menuwidthcolor.r = scenario.stoicheck(buffer, 121);
	std::getline(reader, buffer); buffer.erase(0U, 19U);
	menuwidthcolor.g = scenario.stoicheck(buffer, 121);
	std::getline(reader, buffer); buffer.erase(0U, 19U);
	menuwidthcolor.b = scenario.stoicheck(buffer, 235);

	std::getline(reader, buffer); buffer.erase(0U, 26U);
	menuwidthoutlinecolor.r = scenario.stoicheck(buffer, 0);
	std::getline(reader, buffer); buffer.erase(0U, 26U);
	menuwidthoutlinecolor.g = scenario.stoicheck(buffer, 0);
	std::getline(reader, buffer); buffer.erase(0U, 26U);
	menuwidthoutlinecolor.b = scenario.stoicheck(buffer, 0);

	std::getline(reader, buffer); buffer.erase(0U, 23U);
	menuwidthfillcolor.r = scenario.stoicheck(buffer, 0);
	std::getline(reader, buffer); buffer.erase(0U, 23U);
	menuwidthfillcolor.g = scenario.stoicheck(buffer, 0);
	std::getline(reader, buffer); buffer.erase(0U, 23U);
	menuwidthfillcolor.b = scenario.stoicheck(buffer, 0);
	std::getline(reader, buffer); buffer.erase(0U, 23U);
	menuwidthfillcolor.a = scenario.stoicheck(buffer, 0);

	std::getline(reader, buffer); buffer.erase(0U, 24U);
	menuwidthsfillcolor.r = scenario.stoicheck(buffer, 50);
	std::getline(reader, buffer); buffer.erase(0U, 24U);
	menuwidthsfillcolor.g = scenario.stoicheck(buffer, 50);
	std::getline(reader, buffer); buffer.erase(0U, 24U);
	menuwidthsfillcolor.b = scenario.stoicheck(buffer, 100);
	std::getline(reader, buffer); buffer.erase(0U, 24U);
	menuwidthsfillcolor.a = scenario.stoicheck(buffer, 100);

	std::getline(reader, buffer); buffer.erase(0U, 24U);
	menuwidthffillcolor.r = scenario.stoicheck(buffer, 205);
	std::getline(reader, buffer); buffer.erase(0U, 24U);
	menuwidthffillcolor.g = scenario.stoicheck(buffer, 30);
	std::getline(reader, buffer); buffer.erase(0U, 24U);
	menuwidthffillcolor.b = scenario.stoicheck(buffer, 70);
	std::getline(reader, buffer); buffer.erase(0U, 24U);
	menuwidthffillcolor.a = scenario.stoicheck(buffer, 125);

	std::getline(reader, buffer); buffer.erase(0U, 19U);
	menuheightcolor.r = scenario.stoicheck(buffer, 121);
	std::getline(reader, buffer); buffer.erase(0U, 19U);
	menuheightcolor.g = scenario.stoicheck(buffer, 121);
	std::getline(reader, buffer); buffer.erase(0U, 19U);
	menuheightcolor.b = scenario.stoicheck(buffer, 235);

	std::getline(reader, buffer); buffer.erase(0U, 26U);
	menuheightoutlinecolor.r = scenario.stoicheck(buffer, 0);
	std::getline(reader, buffer); buffer.erase(0U, 26U);
	menuheightoutlinecolor.g = scenario.stoicheck(buffer, 0);
	std::getline(reader, buffer); buffer.erase(0U, 26U);
	menuheightoutlinecolor.b = scenario.stoicheck(buffer, 0);

	std::getline(reader, buffer); buffer.erase(0U, 23U);
	menuheightfillcolor.r = scenario.stoicheck(buffer, 0);
	std::getline(reader, buffer); buffer.erase(0U, 23U);
	menuheightfillcolor.g = scenario.stoicheck(buffer, 0);
	std::getline(reader, buffer); buffer.erase(0U, 23U);
	menuheightfillcolor.b = scenario.stoicheck(buffer, 0);
	std::getline(reader, buffer); buffer.erase(0U, 23U);
	menuheightfillcolor.a = scenario.stoicheck(buffer, 0);

	std::getline(reader, buffer); buffer.erase(0U, 24U);
	menuheightsfillcolor.r = scenario.stoicheck(buffer, 50);
	std::getline(reader, buffer); buffer.erase(0U, 24U);
	menuheightsfillcolor.g = scenario.stoicheck(buffer, 50);
	std::getline(reader, buffer); buffer.erase(0U, 24U);
	menuheightsfillcolor.b = scenario.stoicheck(buffer, 100);
	std::getline(reader, buffer); buffer.erase(0U, 24U);
	menuheightsfillcolor.a = scenario.stoicheck(buffer, 100);

	std::getline(reader, buffer); buffer.erase(0U, 24U);
	menuheightffillcolor.r = scenario.stoicheck(buffer, 205);
	std::getline(reader, buffer); buffer.erase(0U, 24U);
	menuheightffillcolor.g = scenario.stoicheck(buffer, 30);
	std::getline(reader, buffer); buffer.erase(0U, 24U);
	menuheightffillcolor.b = scenario.stoicheck(buffer, 70);
	std::getline(reader, buffer); buffer.erase(0U, 24U);
	menuheightffillcolor.a = scenario.stoicheck(buffer, 125);

	std::getline(reader, buffer); buffer.erase(0U, 33U);
	menuprofilesmenuoutlinecolor.r = scenario.stoicheck(buffer, 0);
	std::getline(reader, buffer); buffer.erase(0U, 33U);
	menuprofilesmenuoutlinecolor.g = scenario.stoicheck(buffer, 0);
	std::getline(reader, buffer); buffer.erase(0U, 33U);
	menuprofilesmenuoutlinecolor.b = scenario.stoicheck(buffer, 0);
	menuprofilesmenuoutlinecolor.a = 0;

	std::getline(reader, buffer); buffer.erase(0U, 30U);
	menuprofilesmenufillcolor.r = scenario.stoicheck(buffer, 0);
	std::getline(reader, buffer); buffer.erase(0U, 30U);
	menuprofilesmenufillcolor.g = scenario.stoicheck(buffer, 0);
	std::getline(reader, buffer); buffer.erase(0U, 30U);
	menuprofilesmenufillcolor.b = scenario.stoicheck(buffer, 0);
	std::getline(reader, buffer); buffer.erase(0U, 30U);
	menuprofilesmenufillcolor.a = 0;
	profilesmenufillfactor = scenario.stoicheck(buffer, 0) / 255.f;


	std::getline(reader, buffer); buffer.erase(0U, 22U);
	menuprofilescolor.r = scenario.stoicheck(buffer, 121);
	std::getline(reader, buffer); buffer.erase(0U, 22U);
	menuprofilescolor.g = scenario.stoicheck(buffer, 121);
	std::getline(reader, buffer); buffer.erase(0U, 22U);
	menuprofilescolor.b = scenario.stoicheck(buffer, 235);
	menuprofilescolor.a = 0;

	std::getline(reader, buffer); buffer.erase(0U, 28U);
	menuprofilesselectcolor.r = scenario.stoicheck(buffer, 121);
	std::getline(reader, buffer); buffer.erase(0U, 28U);
	menuprofilesselectcolor.g = scenario.stoicheck(buffer, 235);
	std::getline(reader, buffer); buffer.erase(0U, 28U);
	menuprofilesselectcolor.b = scenario.stoicheck(buffer, 121);
	menuprofilesselectcolor.a = 0;

	std::getline(reader, buffer); buffer.erase(0U, 21U);
	menustoriescolor.r = scenario.stoicheck(buffer, 121);
	std::getline(reader, buffer); buffer.erase(0U, 21U);
	menustoriescolor.g = scenario.stoicheck(buffer, 121);
	std::getline(reader, buffer); buffer.erase(0U, 21U);
	menustoriescolor.b = scenario.stoicheck(buffer, 235);
	menustoriescolor.a = 0;

	std::getline(reader, buffer); buffer.erase(0U, 27U);
	menustoriesselectcolor.r = scenario.stoicheck(buffer, 121);
	std::getline(reader, buffer); buffer.erase(0U, 27U);
	menustoriesselectcolor.g = scenario.stoicheck(buffer, 235);
	std::getline(reader, buffer); buffer.erase(0U, 27U);
	menustoriesselectcolor.b = scenario.stoicheck(buffer, 121);
	menustoriesselectcolor.a = 0;

	//std::getline(reader, buffer); buffer.erase(0U, 22U);
	//menusoutlinecolor.r = scenario.stoicheck(buffer, 0);
	//std::getline(reader, buffer); buffer.erase(0U, 22U);
	//menusoutlinecolor.g = scenario.stoicheck(buffer, 0);
	//std::getline(reader, buffer); buffer.erase(0U, 22U);
	//menusoutlinecolor.b = scenario.stoicheck(buffer, 0);

	std::getline(reader, buffer); buffer.erase(0U, 19U);
	menuerrorcolor.r = scenario.stoicheck(buffer, 221);
	std::getline(reader, buffer); buffer.erase(0U, 19U);
	menuerrorcolor.g = scenario.stoicheck(buffer, 21);
	std::getline(reader, buffer); buffer.erase(0U, 19U);
	menuerrorcolor.b = scenario.stoicheck(buffer, 125);

	std::getline(reader, buffer); buffer.erase(0U, 14U);
	statcolor.r = scenario.stoicheck(buffer, 235);
	std::getline(reader, buffer); buffer.erase(0U, 14U);
	statcolor.g = scenario.stoicheck(buffer, 239);
	std::getline(reader, buffer); buffer.erase(0U, 14U);
	statcolor.b = scenario.stoicheck(buffer, 240);
	statcolor.a = 0;

	std::getline(reader, buffer); buffer.erase(0U, 18U);
	statgaincolor.r = scenario.stoicheck(buffer, 255);
	std::getline(reader, buffer); buffer.erase(0U, 18U);
	statgaincolor.g = scenario.stoicheck(buffer, 82);
	std::getline(reader, buffer); buffer.erase(0U, 18U);
	statgaincolor.b = scenario.stoicheck(buffer, 88);

	std::getline(reader, buffer); buffer.erase(0U, 18U);
	statlosscolor.r = scenario.stoicheck(buffer, 147);
	std::getline(reader, buffer); buffer.erase(0U, 18U);
	statlosscolor.g = scenario.stoicheck(buffer, 146);
	std::getline(reader, buffer); buffer.erase(0U, 18U);
	statlosscolor.b = scenario.stoicheck(buffer, 146);

	std::getline(reader, buffer); buffer.erase(0U, 20U);
	textchoicecolor.r = scenario.stoicheck(buffer, 0);
	std::getline(reader, buffer); buffer.erase(0U, 20U);
	textchoicecolor.g = scenario.stoicheck(buffer, 0);
	std::getline(reader, buffer); buffer.erase(0U, 20U);
	textchoicecolor.b = scenario.stoicheck(buffer, 0);
	textchoicecolor.a = 0;

	std::getline(reader, buffer); buffer.erase(0U, 29U);
	textchoiceunavaiblecolor.r = scenario.stoicheck(buffer, 100);
	std::getline(reader, buffer); buffer.erase(0U, 29U);
	textchoiceunavaiblecolor.g = scenario.stoicheck(buffer, 100);
	std::getline(reader, buffer); buffer.erase(0U, 29U);
	textchoiceunavaiblecolor.b = scenario.stoicheck(buffer, 100);
	textchoiceunavaiblecolor.a = 0;
	scenario.textchoiceunavaiblecolor.reset(&textchoiceunavaiblecolor);

	std::getline(reader, buffer); buffer.erase(0U, 23U);
	textchoicefillcolor.r = scenario.stoicheck(buffer, 0);
	std::getline(reader, buffer); buffer.erase(0U, 23U);
	textchoicefillcolor.g = scenario.stoicheck(buffer, 0);
	std::getline(reader, buffer); buffer.erase(0U, 23U);
	textchoicefillcolor.b = scenario.stoicheck(buffer, 255);
	std::getline(reader, buffer); buffer.erase(0U, 23U);
	textchoicefillcolor.a = 0;
	choicefactor = scenario.stoicheck(buffer, 125) / 255.f;

	std::getline(reader, buffer); buffer.erase(0U, 18U);
	menuhelpcolor.r = scenario.stoicheck(buffer, 120);
	std::getline(reader, buffer); buffer.erase(0U, 18U);
	menuhelpcolor.g = scenario.stoicheck(buffer, 101);
	std::getline(reader, buffer); buffer.erase(0U, 18U);
	menuhelpcolor.b = scenario.stoicheck(buffer, 238);
}

void Cmain::SaveToFile()
{
	std::ofstream myfile("bin/Options.ini", std::ios::trunc);
	myfile << "fullscreen = " << fullscreen
		<< "\nwidth = " << fullone
		<< "\nheight = " << fulltwo
		<< "\nmusic = " << music
		<< "\nsound = " << sound
		<< "\nfontsize1 = " << fontsize1
		<< "\nfontsize2 = " << fontsize2
		<< "\nfontsize3 = " << fontsize3
		<< "\nCurrent Profile = " << selectionp
		<< "\nCurrent Story = " << selections
		<< "\nAntialiasing = " << antialias
		<< "\nFramerateLimit = " << framelimit
		<< "\nPriorLimit = " << priorlimit
		<< "\ntextcolor.r = " << static_cast<int>(textcolor.r)
		<< "\ntextcolor.g = " << static_cast<int>(textcolor.g)
		<< "\ntextcolor.b = " << static_cast<int>(textcolor.b)
		<< "\nmenucolor.r = " << static_cast<int>(menucolor.r)
		<< "\nmenucolor.g = " << static_cast<int>(menucolor.g)
		<< "\nmenucolor.b = " << static_cast<int>(menucolor.b)
		<< "\nmenuselectcolor.r = " << static_cast<int>(menuselectcolor.r)
		<< "\nmenuselectcolor.g = " << static_cast<int>(menuselectcolor.g)
		<< "\nmenuselectcolor.b = " << static_cast<int>(menuselectcolor.b)
		<< "\nmenuclickcolor.r = " << static_cast<int>(menuclickcolor.r)
		<< "\nmenuclickcolor.g = " << static_cast<int>(menuclickcolor.g)
		<< "\nmenuclickcolor.b = " << static_cast<int>(menuclickcolor.b)
		<< "\nmenuoncolor.r = " << static_cast<int>(menuoncolor.r)
		<< "\nmenuoncolor.g = " << static_cast<int>(menuoncolor.g)
		<< "\nmenuoncolor.b = " << static_cast<int>(menuoncolor.b)
		<< "\nmenuonselectcolor.r = " << static_cast<int>(menuonselectcolor.r)
		<< "\nmenuonselectcolor.g = " << static_cast<int>(menuonselectcolor.g)
		<< "\nmenuonselectcolor.b = " << static_cast<int>(menuonselectcolor.b)
		<< "\nmenuonclickcolor.r = " << static_cast<int>(menuonclickcolor.r)
		<< "\nmenuonclickcolor.g = " << static_cast<int>(menuonclickcolor.g)
		<< "\nmenuonclickcolor.b = " << static_cast<int>(menuonclickcolor.b)
		<< "\nmenudangercolor.r = " << static_cast<int>(menudangercolor.r)
		<< "\nmenudangercolor.g = " << static_cast<int>(menudangercolor.g)
		<< "\nmenudangercolor.b = " << static_cast<int>(menudangercolor.b)
		<< "\nmenudangerselectcolor.r = " << static_cast<int>(menudangerselectcolor.r)
		<< "\nmenudangerselectcolor.g = " << static_cast<int>(menudangerselectcolor.g)
		<< "\nmenudangerselectcolor.b = " << static_cast<int>(menudangerselectcolor.b)
		<< "\nmenudangerclickcolor.r = " << static_cast<int>(menudangerclickcolor.r)
		<< "\nmenudangerclickcolor.g = " << static_cast<int>(menudangerclickcolor.g)
		<< "\nmenudangerclickcolor.b = " << static_cast<int>(menudangerclickcolor.b)
		<< "\nmenunodangercolor.r = " << static_cast<int>(menunodangercolor.r)
		<< "\nmenunodangercolor.g = " << static_cast<int>(menunodangercolor.g)
		<< "\nmenunodangercolor.b = " << static_cast<int>(menunodangercolor.b)
		<< "\nmenunodangerselectcolor.r = " << static_cast<int>(menunodangerselectcolor.r)
		<< "\nmenunodangerselectcolor.g = " << static_cast<int>(menunodangerselectcolor.g)
		<< "\nmenunodangerselectcolor.b = " << static_cast<int>(menunodangerselectcolor.b)
		<< "\nmenunodangerclickcolor.r = " << static_cast<int>(menunodangerclickcolor.r)
		<< "\nmenunodangerclickcolor.g = " << static_cast<int>(menunodangerclickcolor.g)
		<< "\nmenunodangerclickcolor.b = " << static_cast<int>(menunodangerclickcolor.b)
		<< "\nmenuwidthcolor.r = " << static_cast<int>(menuwidthcolor.r)
		<< "\nmenuwidthcolor.g = " << static_cast<int>(menuwidthcolor.g)
		<< "\nmenuwidthcolor.b = " << static_cast<int>(menuwidthcolor.b)
		<< "\nmenuwidthoutlinecolor.r = " << static_cast<int>(menuwidthoutlinecolor.r)
		<< "\nmenuwidthoutlinecolor.g = " << static_cast<int>(menuwidthoutlinecolor.g)
		<< "\nmenuwidthoutlinecolor.b = " << static_cast<int>(menuwidthoutlinecolor.b)
		<< "\nmenuwidthfillcolor.r = " << static_cast<int>(menuwidthfillcolor.r)
		<< "\nmenuwidthfillcolor.g = " << static_cast<int>(menuwidthfillcolor.g)
		<< "\nmenuwidthfillcolor.b = " << static_cast<int>(menuwidthfillcolor.b)
		<< "\nmenuwidthfillcolor.a = " << static_cast<int>(menuwidthfillcolor.a)
		<< "\nmenuwidthsfillcolor.r = " << static_cast<int>(menuwidthsfillcolor.r)
		<< "\nmenuwidthsfillcolor.g = " << static_cast<int>(menuwidthsfillcolor.g)
		<< "\nmenuwidthsfillcolor.b = " << static_cast<int>(menuwidthsfillcolor.b)
		<< "\nmenuwidthsfillcolor.a = " << static_cast<int>(menuwidthsfillcolor.a)
		<< "\nmenuwidthffillcolor.r = " << static_cast<int>(menuwidthffillcolor.r)
		<< "\nmenuwidthffillcolor.g = " << static_cast<int>(menuwidthffillcolor.g)
		<< "\nmenuwidthffillcolor.b = " << static_cast<int>(menuwidthffillcolor.b)
		<< "\nmenuwidthffillcolor.a = " << static_cast<int>(menuwidthffillcolor.a)
		<< "\nmenuheightcolor.r = " << static_cast<int>(menuheightcolor.r)
		<< "\nmenuheightcolor.g = " << static_cast<int>(menuheightcolor.g)
		<< "\nmenuheightcolor.b = " << static_cast<int>(menuheightcolor.b)
		<< "\nmenuheightoutlinecolor.r = " << static_cast<int>(menuheightoutlinecolor.r)
		<< "\nmenuheightoutlinecolor.g = " << static_cast<int>(menuheightoutlinecolor.g)
		<< "\nmenuheightoutlinecolor.b = " << static_cast<int>(menuheightoutlinecolor.b)
		<< "\nmenuheightfillcolor.r = " << static_cast<int>(menuheightfillcolor.r)
		<< "\nmenuheightfillcolor.g = " << static_cast<int>(menuheightfillcolor.g)
		<< "\nmenuheightfillcolor.b = " << static_cast<int>(menuheightfillcolor.b)
		<< "\nmenuheightfillcolor.a = " << static_cast<int>(menuheightfillcolor.a)
		<< "\nmenuheightsfillcolor.r = " << static_cast<int>(menuheightsfillcolor.r)
		<< "\nmenuheightsfillcolor.g = " << static_cast<int>(menuheightsfillcolor.g)
		<< "\nmenuheightsfillcolor.b = " << static_cast<int>(menuheightsfillcolor.b)
		<< "\nmenuheightsfillcolor.a = " << static_cast<int>(menuheightsfillcolor.a)
		<< "\nmenuheightffillcolor.r = " << static_cast<int>(menuheightffillcolor.r)
		<< "\nmenuheightffillcolor.g = " << static_cast<int>(menuheightffillcolor.g)
		<< "\nmenuheightffillcolor.b = " << static_cast<int>(menuheightffillcolor.b)
		<< "\nmenuheightffillcolor.a = " << static_cast<int>(menuheightffillcolor.a)
		<< "\nmenuprofilesmenuoutlinecolor.r = " << static_cast<int>(menuprofilesmenuoutlinecolor.r)
		<< "\nmenuprofilesmenuoutlinecolor.g = " << static_cast<int>(menuprofilesmenuoutlinecolor.g)
		<< "\nmenuprofilesmenuoutlinecolor.b = " << static_cast<int>(menuprofilesmenuoutlinecolor.b)
		<< "\nmenuprofilesmenufillcolor.r = " << static_cast<int>(menuprofilesmenufillcolor.r)
		<< "\nmenuprofilesmenufillcolor.g = " << static_cast<int>(menuprofilesmenufillcolor.g)
		<< "\nmenuprofilesmenufillcolor.b = " << static_cast<int>(menuprofilesmenufillcolor.b)
		<< "\nmenuprofilesmenufillcolor.a = " << static_cast<int>(round(profilesmenufillfactor * 255.f))
		<< "\nmenuprofilescolor.r = " << static_cast<int>(menuprofilescolor.r)
		<< "\nmenuprofilescolor.g = " << static_cast<int>(menuprofilescolor.g)
		<< "\nmenuprofilescolor.b = " << static_cast<int>(menuprofilescolor.b)
		<< "\nmenuprofilesselectcolor.r = " << static_cast<int>(menuprofilesselectcolor.r)
		<< "\nmenuprofilesselectcolor.g = " << static_cast<int>(menuprofilesselectcolor.g)
		<< "\nmenuprofilesselectcolor.b = " << static_cast<int>(menuprofilesselectcolor.b)
		<< "\nmenustoriescolor.r = " << static_cast<int>(menustoriescolor.r)
		<< "\nmenustoriescolor.g = " << static_cast<int>(menustoriescolor.g)
		<< "\nmenustoriescolor.b = " << static_cast<int>(menustoriescolor.b)
		<< "\nmenustoriesselectcolor.r = " << static_cast<int>(menustoriesselectcolor.r)
		<< "\nmenustoriesselectcolor.g = " << static_cast<int>(menustoriesselectcolor.g)
		<< "\nmenustoriesselectcolor.b = " << static_cast<int>(menustoriesselectcolor.b)
		//<< "\nmenusoutlinecolor.r = " << static_cast<int>(menusoutlinecolor.r)
		//<< "\nmenusoutlinecolor.g = " << static_cast<int>(menusoutlinecolor.g)
		//<< "\nmenusoutlinecolor.b = " << static_cast<int>(menusoutlinecolor.b)
		<< "\nmenuerrorcolor.r = " << static_cast<int>(menuerrorcolor.r)
		<< "\nmenuerrorcolor.g = " << static_cast<int>(menuerrorcolor.g)
		<< "\nmenuerrorcolor.b = " << static_cast<int>(menuerrorcolor.b)
		<< "\nstatcolor.r = " << static_cast<int>(statcolor.r)
		<< "\nstatcolor.g = " << static_cast<int>(statcolor.g)
		<< "\nstatcolor.b = " << static_cast<int>(statcolor.b)
		<< "\nstatgaincolor.r = " << static_cast<int>(statgaincolor.r)
		<< "\nstatgaincolor.g = " << static_cast<int>(statgaincolor.g)
		<< "\nstatgaincolor.b = " << static_cast<int>(statgaincolor.b)
		<< "\nstatlosscolor.r = " << static_cast<int>(statlosscolor.r)
		<< "\nstatlosscolor.g = " << static_cast<int>(statlosscolor.g)
		<< "\nstatlosscolor.b = " << static_cast<int>(statlosscolor.b)
		<< "\ntextchoicecolor.r = " << static_cast<int>(textchoicecolor.r)
		<< "\ntextchoicecolor.g = " << static_cast<int>(textchoicecolor.g)
		<< "\ntextchoicecolor.b = " << static_cast<int>(textchoicecolor.b)
		<< "\ntextchoiceunavaiblecolor.r = " << static_cast<int>(textchoiceunavaiblecolor.r)
		<< "\ntextchoiceunavaiblecolor.g = " << static_cast<int>(textchoiceunavaiblecolor.g)
		<< "\ntextchoiceunavaiblecolor.b = " << static_cast<int>(textchoiceunavaiblecolor.b)
		<< "\ntextchoicefillcolor.r = " << static_cast<int>(textchoicefillcolor.r)
		<< "\ntextchoicefillcolor.g = " << static_cast<int>(textchoicefillcolor.g)
		<< "\ntextchoicefillcolor.b = " << static_cast<int>(textchoicefillcolor.b)
		<< "\ntextchoicefillcolor.a = " << static_cast<int>(round(choicefactor * 255.f))
		<< "\nmenuhelpcolor.r = " << static_cast<int>(menuhelpcolor.r)
		<< "\nmenuhelpcolor.g = " << static_cast<int>(menuhelpcolor.g)
		<< "\nmenuhelpcolor.b = " << static_cast<int>(menuhelpcolor.b)
		<< std::endl;
	myfile.close();
}
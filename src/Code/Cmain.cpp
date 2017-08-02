/*
@Author: LightTab2
The MIT License(MIT)

Copyright(c) 2016 LightTab2 azorro12@gmail.com
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and / or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "Cmain.h"

unsigned int priorlimit = 5U;
std::wstring ScenarioParser::apath;
Cmain::Cmain()
{
	try {
<<<<<<< HEAD
	if (!font.loadFromFile("../../bin/Fonts/Fontformenu.ttf")) throw w_err(L"Missing file from directory \"bin/Images/Fontformenu.ttf\"");
	button_1_text.setFont(font);
	button_1_text.setString("Lightine");

	CreateDirectory(L"../../bin", NULL);
	LoadOptions(); //reading from ini
	createWindow();
	sf::Image bck; bck.create(w, h, std::move(sf::Color(247U, 244U, 241U)));
	sf::Texture bck_t; bck_t.loadFromImage(bck);
	Background.setTexture(bck_t);
	std::thread load([&]()
	{
		CreateDirectory(L"../../bin/Fonts", NULL);
		CreateDirectory(L"../../bin/Images", NULL);
		CreateDirectory(L"../../bin/Saves", NULL);
		PWSTR p;
		if (SHGetKnownFolderPath(FOLDERID_RoamingAppData, KF_FLAG_DEFAULT, NULL, &p) != S_OK) throw w_err(L"Couldn't open Aplication Data! Try running as administator"); //the permission isn't needed, but who knows if this doesn't work?
		ScenarioParser::apath = std::wstring(p) + L"\\Lightine";
		CoTaskMemFree(p);
		CreateDirectory(L"../../bin/Scripts", NULL);
		CreateDirectory(ScenarioParser::apath.c_str(), NULL);
		scenario.w = &w; scenario.h = &h;
		if (!Background_texture.loadFromFile("../../bin/Images/gradient.png")) throw w_err(L"Missing file: \"bin/Images/gradient.png\"");
		if (!michaupasełkeł_t.loadFromFile("../../bin/Images/margin.png")) throw w_err(L"Missing file from directory \"bin/Images/margin.png\"");
		if (!scenario.next_t.loadFromFile("../../bin/Images/Next.png")) throw w_err(L"Missing file from directory \"bin/Images/Next.png\"");
=======
	CreateDirectory(L"../../bin", NULL);
	CreateDirectory(L"../../bin/Fonts", NULL);
	CreateDirectory(L"../../bin/Images", NULL);
	CreateDirectory(L"../../bin/Logs", NULL);
	CreateDirectory(L"../../bin/Saves", NULL);
	PWSTR p;
	if (SHGetKnownFolderPath(FOLDERID_RoamingAppData, KF_FLAG_DEFAULT, NULL, &p) != S_OK) throw w_err(L"Couldn't open Aplication Data! Try running as administator"); //the permission isn't needed, but who knows if this doesn't work?
	ScenarioParser::apath = std::wstring(p) + L"\\Lightine";
	CoTaskMemFree(p);
	CreateDirectory(L"../../bin/Scripts", NULL);
	CreateDirectory(ScenarioParser::apath.c_str(), NULL);
	LoadOptions(); //reading from ini
	scenario.w = &w; scenario.h = &h;
		if (!Background_texture.loadFromFile("../../bin/Images/gradient.png")) throw w_err(L"Missing file: \"bin/Images/gradient.png\"");
		if (!michaupasełkeł_t.loadFromFile("../../bin/Images/margin.png")) throw w_err(L"Missing file from directory \"bin/Images/margin.png\"");
		if (!scenario.next_t.loadFromFile("../../bin/Images/Next.png")) throw w_err(L"Missing file from directory \"bin/Images/Next.png\"");
		if (!font.loadFromFile("../../bin/Fonts/Fontformenu.ttf")) throw w_err(L"Missing file from directory \"bin/Images/Fontformenu.ttf\"");
>>>>>>> 962c618769e951108e54dadcdc7dac935fcb7185
		if (!font2.loadFromFile("../../bin/Fonts/Fontforgametext.ttf")) throw w_err(L"Missing file from directory \"bin/Images/Fontforgametext.ttf\"");
		if (!slider.loadFromFile("../../bin/Images/Slider.png")) throw w_err(L"Missing file from directory \"bin/Images/Slider.png\"");
		if (!bar.loadFromFile("../../bin/Images/Bar.png")) throw w_err(L"Missing file from directory \"bin/Images/Bar.png\"");
		if (!arrowup_t.loadFromFile("../../bin/Images/ArrowUP.png")) throw w_err(L"Missing file from directory \"bin/Images/ArrowUP.png\"");
		if (!arrowdn_t.loadFromFile("../../bin/Images/Arrow.png")) throw w_err(L"Missing file from directory \"bin/Images/Arrow.png\"");
		if (!reset_t.loadFromFile("../../bin/Images/Reset.png")) throw w_err(L"Missing file from directory \"bin/Images/Reset.png\"");
		if (!shwstats_t.loadFromFile("../../bin/Images/Show.png")) throw w_err(L"Missing file from directory \"bin/Images/Show.png\"");
<<<<<<< HEAD
		//textures loaded
		scenario.textchoiceunavailablecolor = &textchoiceunavailablecolor;
		f14_text.setString("Press Alt + F4 to quit");
		enternewerror_t.setString("Error: There's already an object with the same name");
		button_2_text.setString("Options");
		button_3_text.setString("Save Options");
		ctext.setString("Are you sure?");
		//strings set
		button_2_text.setFont(font);
		button_3_text.setFont(font);
		resbutton1_text.setFont(font);
		resbutton2_text.setFont(font);
		ctext.setFont(font);
		f14_text.setFont(font);
		enternewerror_t.setFont(font);
		//fonts set
		Background.setTexture(Background_texture);
		michaupasełkeł.setTexture(michaupasełkeł_t);
		scenario.next.setTexture(scenario.next_t);
		sliders.setTexture(slider);
		bars.setTexture(bar);
		arrowup.setTexture(arrowup_t);
		arrowdn.setTexture(arrowdn_t);
		showstats.setTexture(shwstats_t);
		resets.setTexture(reset_t);
		//textures set
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
		arrowdn.setColor(std::move(sf::Color(255U, 255U, 255U, 0)));
		arrowup.setColor(arrowdn.getColor()); //colors set
	});
	Intro();
	load.join();	
	button_1_text.setFillColor(menucolor);
	scenario.text.setFont(font2);
	scenario.text.setFillColor(textcolor);
=======
	//textures loaded
	scenario.textchoiceunavaiblecolor = &textchoiceunavaiblecolor;
	f14_text.setString("Press Alt + F4 to quit");
	enternewerror_t.setString("Error: There's already an object with the same name");
	button_1_text.setString("Lightine");
	button_2_text.setString("Options");
	button_3_text.setString("Save Options");
	ctext.setString("Are you sure?");
	//strings set
	scenario.text.setFont(font2);
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
	michaupasełkeł.setTexture(michaupasełkeł_t);
	scenario.next.setTexture(scenario.next_t);
	sliders.setTexture(slider);
	bars.setTexture(bar);
	arrowup.setTexture(arrowup_t);
	arrowdn.setTexture(arrowdn_t);
	showstats.setTexture(shwstats_t);
	resets.setTexture(reset_t);
	//textures set
	button_1_text.setFillColor(menucolor);
	scenario.text.setFillColor(textcolor);
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
>>>>>>> 962c618769e951108e54dadcdc7dac935fcb7185
	sSaveOptions();
	}
	catch (w_err err)
	{
		quit = true;
		MessageBox(NULL, err.msg.c_str(), NULL, MB_ICONERROR);
		return;
	}
	catch (...)
	{
		quit = true;
		MessageBox(NULL, L"Unknown critical error", NULL, MB_ICONERROR);
		return;
	}
}

void Cmain::sSaveOptions()	//anyone who would like to analyze this code... it's not necessary, just add something at the end of it; read its comment
{
 	fullone = std::to_string(w);	//resbutton1's string
	fulltwo = std::to_string(h);	//resbutton2's string
	cfullone = fullone;
	cfulltwo = fulltwo;
	cfullscreen = fullscreen;
	csound = sound;
	cmusic = music;
	//control variables set
	createWindow();

	if (w < 1200) scenario.text.setCharacterSize(fontsize1);
	else if (w < 1600) scenario.text.setCharacterSize(fontsize2);
	else if (w < 2200) scenario.text.setCharacterSize(fontsize3);
	else scenario.text.setCharacterSize(static_cast<unsigned int>(round(fontsize3 + fontsize1 * (w-2000)/ 800.f)));
<<<<<<< HEAD
	int &&size = h / 10 + h / 120; float &&scale = (w + h) / 1400.f;
	ctext.setCharacterSize(size);
	button_1_text.setCharacterSize(size);
	button_2_text.setCharacterSize(size);
	button_3_text.setCharacterSize(size);
	resbutton1_text.setCharacterSize(size);
	resbutton2_text.setCharacterSize(size);
=======
	ctext.setCharacterSize(h / 10 + h / 120);
	button_1_text.setCharacterSize(h / 10 + h / 120);
	button_2_text.setCharacterSize(h / 10 + h / 120);
	button_3_text.setCharacterSize(h / 10 + h / 120);
	resbutton1_text.setCharacterSize(h / 10 + h / 120);
	resbutton2_text.setCharacterSize(h / 10 + h / 120);
>>>>>>> 962c618769e951108e54dadcdc7dac935fcb7185
	f14_text.setCharacterSize(h / 30);
	profilesmenu.setOutlineThickness(static_cast<float>(h / 150));
	resbutton1_shape.setOutlineThickness(static_cast<float>(h / 300));
	resbutton2_shape.setOutlineThickness(static_cast<float>(h / 300));
	help_text = f14_text;
	help_text.setString("Press Delete to remove");
	f14_text.setOrigin(0, f14_text.getLocalBounds().top);
<<<<<<< HEAD
	f14_text.setPosition(w - round(help_text.getGlobalBounds().width + 6.f * scale), h - round(f14_text.getGlobalBounds().height + 2.f * scale));
	help_text.setOrigin(0, help_text.getLocalBounds().top);
	help_text.setPosition(w - round(help_text.getGlobalBounds().width + 6.f * scale), h - round(f14_text.getGlobalBounds().height + 2.f * scale));
=======
	f14_text.setPosition(w - round(help_text.getGlobalBounds().width + 6.f * w/800.f), h - round(f14_text.getGlobalBounds().height + 2.f * h/600.f));
	help_text.setOrigin(0, help_text.getLocalBounds().top);
	help_text.setPosition(w - round(help_text.getGlobalBounds().width + 6.f * w / 800.f), h - round(f14_text.getGlobalBounds().height + 2.f * h / 600.f));
>>>>>>> 962c618769e951108e54dadcdc7dac935fcb7185

	newname = ntext = ctext;
	newname.setFillColor(menuinsertcolor);
	newname.setString("");
	newname.setPosition(w / 2 - newname.getGlobalBounds().width / 2, h / 2 - round(ctext.getGlobalBounds().height *0.6f));
	ntext.setString("Enter name:");
	ntext.setPosition(w / 2 - ntext.getGlobalBounds().width / 2, h / 2 - ntext.getGlobalBounds().height*2);
	enternewerror_t.setCharacterSize(h / 30);
	enternewerror_t.setPosition(w / 2 - round(enternewerror_t.getGlobalBounds().width / 2), h / 2 - round(ntext.getGlobalBounds().height*2 + enternewerror_t.getGlobalBounds().height * 1.4f));
	enternewerror_t.setFillColor(menuerrorcolor);

	std::string	sizer = "0000";	//Like resbuttons were already filled
	resbutton1_text.setString(sizer);
	resbutton2_text.setString(sizer);
<<<<<<< HEAD
	resbutton1_shape.setSize(std::move(sf::Vector2f(round(resbutton1_text.getGlobalBounds().width + 4.f * scale), round(resbutton1_text.getGlobalBounds().height + 3.f * scale))));
	resbutton2_shape.setSize(std::move(sf::Vector2f(round(resbutton2_text.getGlobalBounds().width + 4.f * scale), round(resbutton2_text.getGlobalBounds().height + 3.f * scale))));
=======
	resbutton1_shape.setSize(sf::Vector2f(round(resbutton1_text.getGlobalBounds().width + 4.f * (w + h) / 1400.f), round(resbutton1_text.getGlobalBounds().height + 3.f * w / 800.f)));
	resbutton2_shape.setSize(sf::Vector2f(round(resbutton2_text.getGlobalBounds().width + 4.f * (w + h) / 1400.f), round(resbutton2_text.getGlobalBounds().height + 3.f * w / 800.f)));
>>>>>>> 962c618769e951108e54dadcdc7dac935fcb7185

	Background.setScale(1, 1);
	Background.setScale(w / Background.getGlobalBounds().width, h / Background.getGlobalBounds().height);
	bars.setScale(w / 800.f, h / 600.f);
	sliders.setScale(bars.getScale().x, bars.getScale().x);
<<<<<<< HEAD
	michaupasełkeł.setScale(w / 800.f, scale);
	arrowup.setScale(scale/8.f, scale/7.f);
	arrowdn.setScale(arrowup.getScale());
	scenario.next.setScale(arrowup.getScale().x*2.f, arrowup.getScale().y*2.f);
	scenario.Bnext = scenario.next.getGlobalBounds();
	resets.setScale(scale/4.f, michaupasełkeł.getScale().y/4.f);
=======
	michaupasełkeł.setScale(w / 800.f, (w + h) / 1400.f);
	arrowup.setScale((w + h) / 12200.f, (w + h) / 11200.f);
	arrowdn.setScale(arrowup.getScale());
	scenario.next.setScale(arrowup.getScale().x*2.f, arrowup.getScale().y*2.f);
	scenario.Bnext = scenario.next.getGlobalBounds();
	resets.setScale((w + h) / 5600.f, michaupasełkeł.getScale().y/4.f);
>>>>>>> 962c618769e951108e54dadcdc7dac935fcb7185
	showstats.setScale(resets.getScale());
	Background.setPosition(0, 0);
	michaupasełkeł.setPosition(0, 0);
	ctext.setPosition(w / 2 - ctext.getGlobalBounds().width / 2, h / 2 - ctext.getGlobalBounds().height*2);
	button_1_text.setString("Resume"); button_2_text.setString("Options"); button_3_text.setString("Save Options");
<<<<<<< HEAD
	button_1_text.setPosition(w / 2 - button_1_text.getGlobalBounds().width / 2, round(scale * 35.f));
	button_2_text.setPosition(w / 2 - button_2_text.getGlobalBounds().width / 2, h / 2 - round(scale * 40.f));
	button_3_text.setPosition(w / 2 - button_3_text.getGlobalBounds().width / 2, h - round(scale * 90.f));
	resbutton1_text.setPosition(w / 2 - round(scale * 120.f + resbutton1_shape.getGlobalBounds().width), round(scale * 25.f));
	resbutton1_shape.setPosition(round(resbutton1_text.getGlobalBounds().left - 4.f * scale), round(resbutton1_text.getGlobalBounds().top - 2.f * scale));
	resbutton2_text.setPosition(w / 2 + round(scale * 120.f), round(scale * 25.f));
	resbutton2_shape.setPosition(round(resbutton2_text.getGlobalBounds().left - 4.f * scale), round(resbutton2_text.getGlobalBounds().top - 2.f * h / 600.f));
	resbutton1_text.setString(fullone);
	resbutton2_text.setString(fulltwo);
	profilesmenu.setSize(std::move(sf::Vector2f(round(0.75f * w), round(h * 0.95f - 2 * arrowup.getGlobalBounds().height))));
=======
	button_1_text.setPosition(w / 2 - button_1_text.getGlobalBounds().width / 2, round(h / 600.f * 35.f));
	button_2_text.setPosition(w / 2 - button_2_text.getGlobalBounds().width / 2, h / 2 - round(h / 600.f * 40.f));
	button_3_text.setPosition(w / 2 - button_3_text.getGlobalBounds().width / 2, h - round(h / 600.f * 90.f));
	resbutton1_text.setPosition(w / 2 - round(w / 800.f * 120.f + resbutton1_shape.getGlobalBounds().width), round(h / 600.f * 25.f));
	resbutton1_shape.setPosition(round(resbutton1_text.getGlobalBounds().left - 4.f * (w + h) / 1400.f), round(resbutton1_text.getGlobalBounds().top - 2.f * h / 600.f));
	resbutton2_text.setPosition(w / 2 + round(w / 800.f * 120.f), round(h / 600.f * 25.f));
	resbutton2_shape.setPosition(round(resbutton2_text.getGlobalBounds().left - 4.f * (w + h) / 1400.f), round(resbutton2_text.getGlobalBounds().top - 2.f * h / 600.f));
	resbutton1_text.setString(fullone);
	resbutton2_text.setString(fulltwo);
	profilesmenu.setSize(sf::Vector2f(round(0.75f * w), round(h * 0.95f - 2 * arrowup.getGlobalBounds().height)));
>>>>>>> 962c618769e951108e54dadcdc7dac935fcb7185
	profilesmenu.setPosition(round(w * 0.125f), round((h - profilesmenu.getSize().y)/2));
	arrowup.setPosition(profilesmenu.getPosition().x + round((profilesmenu.getGlobalBounds().width - arrowup.getGlobalBounds().width)/2.f), profilesmenu.getGlobalBounds().top - round(arrowup.getGlobalBounds().height + 4.f * h / 600.f));
	arrowdn.setPosition(arrowup.getPosition().x, profilesmenu.getGlobalBounds().top + profilesmenu.getGlobalBounds().height + round(4.f * h / 600.f));
	bars.setPosition(round(w - bars.getGlobalBounds().width), 0);
<<<<<<< HEAD
	scenario.rmargin = static_cast<int>(floor(bars.getPosition().x - 15.f* scale));
=======
	scenario.rmargin = static_cast<int>(floor(bars.getPosition().x - 15.f* (w+h)/1400.f));
>>>>>>> 962c618769e951108e54dadcdc7dac935fcb7185
	smaxdown = h - static_cast<int>(round(h / 600.f * 8.f));
	sliders.setPosition(round(bars.getPosition().x + round(w / 800.f * 6.f)), round(h / 600.f * 11.f));
	smaxup = static_cast<int>(round(h / 600.f * 11.f));
	lsetPos = ssetPos = static_cast<float>(smaxup);
	showstats.setPosition(round(w - showstats.getGlobalBounds().width - bars.getGlobalBounds().width - round(w / 800.f * 40.f)), 0);
	showstats.setColor(sf::Color(255, 255, 255, 0));
	resets.setPosition(round(w + (showstats.getGlobalBounds().width - resets.getGlobalBounds().width) / 2 - showstats.getGlobalBounds().width - bars.getGlobalBounds().width - round(w / 800.f * 40.f)), 0);
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
	
	sf::Text t;
	t.setFont(*scenario.text.getFont());
	t.setCharacterSize(static_cast<unsigned int>(scenario.text.getCharacterSize() * 0.9f));
	t.setString("\n");
	scenario.Tsize = ceil(t.getGlobalBounds().height);
	
	getSaveData();
	if (!stories.empty()) scenario.path = "../../bin/Scripts/" + stories[selections].getString() + ".txt";
	
	scenario.text.setPosition(round(w / 18.f), floor(h / 12.f));
	LoadSave();
}

void Cmain::SaveOptions()
{
	int cw, ch;
	ch = h;
	cw = w;
	//duplicates current variables, so 
	if (fullscreen) w = desktop.x;
	else w = scenario.stoiCheck(fullone, 0);
	if (w < 800) w = 800;
	else if (static_cast<unsigned int>(w) > desktop.x) w = desktop.x;
	if (fullscreen) h = desktop.y;
	else h = scenario.stoiCheck(fulltwo, 0);
	if (h < 600) h = 600;
	else if (static_cast<unsigned int>(h) > desktop.y) h = desktop.y;
	//scenario.w = w;
	//scenario.h = h;
	scenario.w2 = static_cast<float>(w / 12);

	if (cfullscreen != fullscreen || w != cw || h != ch) 
	{
		window.close();
		SaveToFile();
		sSaveOptions();
	}
	else if (cmusic != music || csound != sound)
		SaveToFile();
}

inline void Cmain::createWindow()
{
	if (window.isOpen()) return;
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
	button_1_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_1_text.getGlobalBounds().width) / 2, static_cast<int>(round(h / 600.f * 35.f)))));
<<<<<<< HEAD
	button_1_text.setFillColor(std::move(sf::Color(37U, 37U, 249U, 0U)));
	int &&mw = static_cast<int>(round(w * 0.005f));
=======
	button_1_text.setFillColor(sf::Color(menuclickcolor.r, menuclickcolor.g, menuclickcolor.b, static_cast<sf::Uint8>(0)));
>>>>>>> 962c618769e951108e54dadcdc7dac935fcb7185
	//changes button 1 so it's bigger and somewhere else
	sf::Text general;
	general.setFont(font);
	general.setCharacterSize(static_cast<unsigned int>(round((w + h) / 175.f)));
<<<<<<< HEAD
	general.setFillColor(std::move(sf::Color(37U, 37U, 249U, 0U)));
=======
	general.setFillColor(sf::Color(menuclickcolor.r, menuclickcolor.g, menuclickcolor.b, static_cast<sf::Uint8>(0)));
>>>>>>> 962c618769e951108e54dadcdc7dac935fcb7185
	std::wstring str = L"Copyright (c) 2016 LightTab2 azorro12@gmail.com";
	general.setString(str);
	int gh = static_cast<int>(round(general.getGlobalBounds().height * 1.15f)), ghe = static_cast<int>(round(button_1_text.getGlobalBounds().top + button_1_text.getGlobalBounds().height * 1.25f));
	std::vector<sf::Text> cprght;
	cprght.push_back(general);
	ghe += gh;
	str = L"The software is licensed under MIT LICENSE, for more details see LICENSE.TXT";
	general.setString(str);
<<<<<<< HEAD
	general.setPosition(static_cast<float>(mw), static_cast<float>(ghe));
=======
	general.setPosition(round(w * 0.005f), static_cast<float>(ghe));
>>>>>>> 962c618769e951108e54dadcdc7dac935fcb7185
	cprght.push_back(general);
	ghe += gh;
	str = L"It couldn't be made without SFML";
	general.setString(str);
<<<<<<< HEAD
	general.setPosition(static_cast<float>(mw), static_cast<float>(ghe));
=======
	general.setPosition(round(w * 0.005f), static_cast<float>(ghe));
>>>>>>> 962c618769e951108e54dadcdc7dac935fcb7185
	cprght.push_back(general);
	ghe += 4 * gh;
	sf::Texture sfml; sfml.loadFromFile("../../bin/Images/sfml-logo-big.png");
	sf::Sprite sfml_s; sfml_s.setTexture(sfml); sfml_s.setScale((h+w)/5600.f, (h + w)/5600.f);
<<<<<<< HEAD
	sfml_s.setPosition(static_cast<float>(mw), static_cast<float>(ghe));
	sfml_s.setColor(std::move(sf::Color(255U, 255U, 255U, 0U)));
	ghe += 5 * gh + static_cast<int>(sfml_s.getGlobalBounds().height);
	str = L"Adittionaly I want to thank for resources I used:"; 
	general.setString(str);
	general.setPosition(static_cast<float>(mw), static_cast<float>(ghe));
=======
	sfml_s.setPosition(round(w * 0.005f), static_cast<float>(ghe));
	sfml_s.setColor(sf::Color(sf::Uint8(0), sf::Uint8(0), sf::Uint8(0), sf::Uint8(0)));
	ghe += 5 * gh + static_cast<int>(sfml_s.getGlobalBounds().height);
	str = L"Adittionaly I want to thank for resources I used:"; 
	general.setString(str);
	general.setPosition(round(w * 0.005f), static_cast<float>(ghe));
>>>>>>> 962c618769e951108e54dadcdc7dac935fcb7185
	cprght.push_back(general);
	ghe += gh;
	int check2 = static_cast<int>(round(w * 0.975f));
	std::wifstream credits(L"../../bin/Credits.txt");
	while (std::getline(credits, str))
	{
		general.setPosition(static_cast<float>(mw), static_cast<float>(ghe));
		general.setString(str);
		std::wstring strr;
		if (general.getGlobalBounds().left + general.getGlobalBounds().width < check2 || str.find(L' ') == std::wstring::npos) { cprght.push_back(general); ghe += gh; }
		else
		{
			std::size_t pos = 0;
			for (;;) {
<<<<<<< HEAD
				if ((pos = str.find(L' ', pos + 1)) == std::wstring::npos) { general.setString(str); if (general.getGlobalBounds().left + general.getGlobalBounds().width > check2) goto skip; general.setPosition(static_cast<float>(mw), static_cast<float>(ghe)); cprght.push_back(general); ghe += gh; break; }
=======
				if ((pos = str.find(L' ', pos + 1)) == std::wstring::npos) { general.setString(str); if (general.getGlobalBounds().left + general.getGlobalBounds().width > check2) goto skip; general.setPosition(round(w * 0.005f), static_cast<float>(ghe)); cprght.push_back(general); ghe += gh; break; }
>>>>>>> 962c618769e951108e54dadcdc7dac935fcb7185
				general.setString(str.substr(0U, pos));
				if (general.getGlobalBounds().left + general.getGlobalBounds().width > check2)
				{
				skip:general.setString(str.substr(0U, (pos = str.rfind(L' ', pos - 1U) + 1U)));
					str.erase(0U, pos);
<<<<<<< HEAD
					general.setPosition(static_cast<float>(mw), static_cast<float>(ghe));
=======
					general.setPosition(round(w * 0.005f), static_cast<float>(ghe));
>>>>>>> 962c618769e951108e54dadcdc7dac935fcb7185
					cprght.push_back(general);
					ghe += gh;
  				}
			}
		}
	} 
	for (;;)
	{
		sf::Clock timer; timer.restart();
		static sf::Uint8 a = 0;
		for (sf::Text &t : cprght) t.setFillColor(std::move(sf::Color(37U, 37U, 249U, a)));
		sfml_s.setColor(std::move(sf::Color(255U, 255U, 255U, a)));
		window.clear();
		button_1_text.setFillColor(sf::Color(37U, 37U, 249U, a));
		if (a == 255U)
		{
			button_1_text.setString("Resume");
			button_1_text.setCharacterSize(h / 10 + h / 120);
			button_1_text.setPosition(window.mapPixelToCoords(sf::Vector2i(w / 2 - static_cast<int>(button_1_text.getGlobalBounds().width) / 2, static_cast<int>(round(h / 600.f * 35.f)))));
			button_1 = button_1_text.getGlobalBounds();
			std::this_thread::sleep_for(std::chrono::milliseconds(1500)); //window isn't drawn or cleared	
			return; //go back to previous form
		}
		window.draw(Background);
		window.draw(button_1_text);
		window.draw(sfml_s);
		for (sf::Text &t : cprght) window.draw(t);
		window.display();
		++a;
		if (timer.getElapsedTime().asMicroseconds() < 924) std::this_thread::sleep_for(std::chrono::microseconds(924 - timer.getElapsedTime().asMicroseconds()));
	}
}

void Cmain::getSaveData()
{
	std::ifstream file;
	file.open("../../bin/Stories.txt");
	file.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	if (!file) throw w_err(L"Could not open \"../../bin/Stories.txt\"");
	std::string insert; //Buffer for reading profiles
	sf::Text insert_text = newname;	
	insert_text.setFillColor(menustoriescolor);
	arrowedp = arroweds = 0;
	//reset zmiennych
	positions.clear();

	profiles.clear();
	
	stories.clear();
	bool first = true;
	for (;;)
	{
		if (!std::getline(file, insert)) break;
		if (first)
		{
			if (insert[0] == 0xFEFF) insert.erase(0U, 1U); //not sure if necessary, I think the second one recognizes BOM correctly
			else if (insert[0] == 0xef && insert[1U] == 0xbb && insert[2U] == 0xbf) insert.erase(0U, 3U);
			first = false;
		}
		insert_text.setString(insert);
		stories.push_back(insert_text);
	}
	if (!stories.empty() && selections >= static_cast<int>(stories.size())) selections = static_cast<int>(stories.size()) - 1;
	insert_text.setFillColor(menuprofilescolor);
	file.close();
	file.open("../../bin/Profiles.txt");
	if (!file) throw w_err(L"Could not open \"../../bin/Profiles.txt\"");
	first = false;
	for (;;)
	{
		if (!std::getline(file, insert)) break;
		if (first)
		{
			if (insert[0] == 0xFEFF) insert.erase(0U, 1U); //not sure if necessary, I think the second one recognizes BOM correctly
			else if (insert[0] == 0xef && insert[1U] == 0xbb && insert[2U] == 0xbf) insert.erase(0U, 3U);
			first = false;
		}
		insert_text.setString(insert);
		profiles.push_back(insert_text);
	}
	if (!profiles.empty() && selectionp >= static_cast<int>(profiles.size())) selectionp = static_cast<int>(profiles.size()) - 1;
	{
		std::wstring temp;
		temp.reserve(95);
		for (char x = 32; x < 127; ++x) temp += x;
		insert_text.setString(temp);
	}
	int th = static_cast<int>(round(insert_text.getGlobalBounds().height * 1.15f));
	for (menucapacity = 0U; (profilesmenu.getPosition().y + profilesmenu.getGlobalBounds().height) > (insert_text.getPosition().y + round(10.f * h / 600.f) + 2 * th); menucapacity += 1U)
	{
		positions.emplace_back(static_cast<int>(profilesmenu.getPosition().x + round(8.f * w/800.f)), static_cast<int>(profilesmenu.getPosition().y + round(5.f * h / 600.f)) + th * static_cast<int>(menucapacity));
		insert_text.setPosition(static_cast<sf::Vector2f>(positions.back()));
	}
	arroweds_margin = static_cast<int>(stories.size()) - menucapacity;
	arrowedp_margin = static_cast<int>(profiles.size()) - menucapacity;
	if (arroweds_margin < 0) arroweds_margin = 0;
	if (arrowedp_margin < 0) arrowedp_margin = 0;
	arrowedp = selectionp - static_cast<int>(menucapacity/2U);
	if (arrowedp < 0) arrowedp = 0;	
	else if (arrowedp > arrowedp_margin) arrowedp = arrowedp_margin;
	arroweds = selections - static_cast<int>(menucapacity/2U);
	if (arroweds < 0) arroweds = 0;
	else if (arroweds > arroweds_margin) arroweds = arroweds_margin;
}

void Cmain::setupMenu()
{
	if ((gwhich = (gamestate == 7)))
	{
		if (!scheck) return;
		for (size_t repeated = 0U; repeated != menucapacity && repeated != stories.size(); ++repeated)
		{
			stories[arroweds + repeated].setPosition(window.mapPixelToCoords(sf::Vector2i(positions[repeated])));
			if (selections == arroweds + repeated) stories[arroweds + repeated].setFillColor(menustoriesselectcolor);
			else stories[arroweds + repeated].setFillColor(menustoriescolor);
		}
		if (selections == 0) arrowed_up = true;
		else arrowed_up = false; 
		if (stories.empty() || selections == (stories.size() - 1U)) arrowed_dn = true;
		else arrowed_dn = false;
		scheck = false;
	}
	else
	{
		if (!pcheck) return;
		for (size_t repeated = 0U; repeated != menucapacity && repeated != profiles.size(); ++repeated)
		{
			profiles[arrowedp + repeated].setPosition(window.mapPixelToCoords(sf::Vector2i(positions[repeated])));
			if (selectionp == arrowedp + repeated) profiles[arrowedp + repeated].setFillColor(menuprofilesselectcolor);
			else profiles[arrowedp + repeated].setFillColor(menuprofilescolor);
		}
		if (selectionp == 0U) arrowed_up = true;
		else arrowed_up = false;
		if (profiles.empty() || selectionp == (profiles.size() - 1U)) arrowed_dn = true;
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
	std::wstring name; //name of new profile/story (all characters are lower)
	for (const wchar_t &c : newname.getString().toWideString()) name.push_back(tolower(c)); //getting all chars to lower(can't create 2 files with the same name in Windows)
	enternewerror = false;
	if (!name.empty())
	{
		if (gwhich)
		{
			std::wofstream sfile(L"../../bin/Stories.txt", std::ios::trunc);
			sfile.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
			std::wstring oldname;
			for (auto &s : stories)
			{
				sfile << s.getString().toWideString() << std::endl;
				for (const wchar_t &c : s.getString().toWideString()) oldname.push_back(tolower(c)); //getting all chars to lower
				if (oldname == name) enternewerror = true;
				oldname.clear();
			}
			if (enternewerror)
			{
				enternewerror_t.setFillColor(sf::Color(menuerrorcolor.r, menuerrorcolor.g, menuerrorcolor.b, 255));
				errclock.restart();
				return;
			}
			stories.push_back(newname);
			sfile << stories.back().getString().toWideString() << std::endl;
			newname.setString("");
			for (auto &s : profiles)
			{
				std::wifstream temp(L"../../bin/Saves/" + s.getString().toWideString() + L"_" + stories.back().getString().toWideString() + L".txt"); //check if there's already a save
				if (!temp) std::wofstream file(L"../../bin/Saves/" + s.getString().toWideString() + L"_" + stories.back().getString().toWideString() + L".txt");
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
			std::wofstream pfile(L"../../bin/Profiles.txt", std::ios::trunc);
			pfile.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
			std::wstring oldname;
			for (auto &p : profiles) //checking if there's already a profile with the same name
			{
				oldname.clear();
				pfile << p.getString().toWideString() << std::endl;
				for (const wchar_t &c : p.getString().toWideString()) oldname.push_back(tolower(c)); //getting all chars to lower
				if (oldname == name) enternewerror = true;
			}
			if (enternewerror)
			{
				enternewerror_t.setFillColor(sf::Color(menuerrorcolor.r, menuerrorcolor.g, menuerrorcolor.b, 255));
				errclock.restart();
				return;
			}
			profiles.push_back(newname);
			pfile << profiles.back().getString().toWideString() << std::endl;
			newname.setString("");
			for (auto &s : stories)
			{
				std::wifstream temp(L"../../bin/Saves/" + s.getString().toWideString() + L"_" + stories.back().getString().toWideString() + L".txt"); //check if there's already a save
				if (!temp) std::wofstream file(L"../../bin/Saves/" + profiles.back().getString().toWideString() + L"_" + s.getString().toWideString() + L".txt");
			}
			if (profiles.size() > menucapacity) {
				arrowedp += 1;
				arrowedp_margin += 1;
			}
			pcheck = true;
			enternew = false;
		}
		//if (scenario.pempty || scenario.sempty) LoadSave();
	}
}	
<<<<<<< HEAD
void Cmain::LoadOptions()
{
	std::ifstream reader("../../bin/Options.ini");
	std::string buffer;
=======
void scut(std::string& to_cut, size_t pos, std::string& to_insert)
{
	if (pos <= to_cut.size()) to_insert = to_cut.substr(pos);
	else to_insert = "invalid";
}
void Cmain::LoadOptions()
{
	std::ifstream reader("../../bin/Options.ini");
>>>>>>> 962c618769e951108e54dadcdc7dac935fcb7185
	if (!reader)
	{
		std::ofstream myfile("../../bin/Options.ini", std::ios::trunc);
		warn(L"Could not load \"Options.ini\", retrying");
		LoadOptions();
		return;
	}
<<<<<<< HEAD

	auto elblanks = [] (std::string &&str) -> std::string
	{
		if(str.empty()) return "[empty]";
		std::string::size_type b = 0U;
		for (int x = 0; str[x] == ' '; ++x) ++b;
		std::string::size_type e = str.size() - b;
		for (int x = str.size()-1; str[x] == ' '; --x) --e;
		return str.substr(b, e);
	};
	auto CheckName = [&reader, &buffer, &elblanks](std::string &s_buffer) -> bool
	{
		std::getline(reader, buffer);
		if (buffer.empty()) return false;
		if (elblanks(std::move(buffer.substr(0U, buffer.find('=')))) != s_buffer)
		{
			std::string message = "Error reading variable in Options.ini. If it cannot be handled - delete the file.\nExpected: \"" + s_buffer + "\"\ninstead found: \"" + elblanks(std::move(buffer.substr(0U, buffer.find('=')))) + '\"';
			warn(std::wstring(message.begin(), message.end()));
			return false;
		}
		return true;
	};
	auto findvar = [&reader, &elblanks, &CheckName, &buffer](std::string &&s_name, int def = 0) ->int
	{
		if (!CheckName(s_name)) return def;
		if (buffer[0] == 'b')
		{
			if (buffer.find("true", buffer.find('=')) != std::string::npos) return 1;
			else if (buffer.find("false", buffer.find('=')) != std::string::npos) return 0;
			else return def;
		}
		else if (buffer[0] == 'i')
			return std::stoi(elblanks(std::move(buffer.substr(buffer.find('=') + 1))));
		//else throw w_err(L);
	};
	auto findvar_c = [&reader, &elblanks, &CheckName, &buffer](std::string &&s_name, sf::Color &def, unsigned int alpha = 0U)->sf::Color
	{
		if (!CheckName(s_name)) return def;
		if (buffer[0] == 'c')
		{
			int i[3];
			auto pos1 = buffer.find('=');
			auto pos2 = buffer.find(',');
			for (int x = 0; x != 3; ++x)
			{
				i[x] = std::stoi(elblanks(std::move(buffer.substr(pos1+1, pos2-pos1))));
				pos1 = pos2;
				pos2 = buffer.find(',', pos2+1);
			};
			return sf::Color(
				i[0],
				i[1],
				i[2],
				alpha);
		}
		else if (buffer[0] == 'C')
		{
			int i[4];
			auto pos1 = buffer.find('=');
			auto pos2 = buffer.find(',');
			for (int x = 0; x != 4; ++x)
			{
				i[x] = std::stoi(elblanks(std::move(buffer.substr(pos1+1, pos2-pos1))));
				pos1 = pos2;
				pos2 = buffer.find(',', pos2+1);
			};
			return sf::Color(
				i[0],
				i[1],
				i[2],
				i[3]
			);
		}
		//else throw w_err(L);
	};
	fullscreen = findvar("bFullscreen");

	w = findvar("iWidth", 800);
	if (fullscreen) w = desktop.x;
=======
	std::string name, buffer;

	std::getline(reader, name);
	scut(name, 13U, buffer);
	fullscreen = static_cast<bool>(scenario.stoiCheck(buffer));

	std::getline(reader, name);
	scut(name, 8U, buffer);
	if (!fullscreen) w = scenario.stoiCheck(buffer, 800);
	else w = desktop.x;
>>>>>>> 962c618769e951108e54dadcdc7dac935fcb7185
	if (w < 800) w = 800;
	else if (static_cast<unsigned int>(w) > desktop.x) w = desktop.x;
	fullone = std::to_string(w);

<<<<<<< HEAD
	h = findvar("iHeight", 600);
	if (fullscreen) h = desktop.y;
	if (h < 600) h = 600;
	else if (static_cast<unsigned int>(h) > desktop.y) h = desktop.y;

	scenario.w2 = round(w / 12.f);

	fullone = std::to_string(w);
	fulltwo = std::to_string(h);

	music = findvar("bMusic", 1);

	sound = findvar("bSound", 1);

	fontsize1 = findvar("iFontsize1", 44);

	fontsize2 = findvar("iFontsize2", 58);

	fontsize3 = findvar("iFontsize3", 76);

	selectionp = findvar("iCurrentProfile");

	selections = findvar("iCurrentStory");

	antialias = findvar("iAntialiasing", 4);

	framelimit = findvar("iFramerateLimit", 300);

	using cl = sf::Color;
	textcolor = findvar_c("cTextcolor", cl(0U,0U,0U,0U));

	menucolor = findvar_c("CMenucolor", cl(188U, 188U, 228U, 255U));

	menuinsertcolor = findvar_c("CMenuinsertcolor", cl(202U, 122U, 128U, 255U));

	menuselectcolor = findvar_c("CMenuselectcolor", cl(129U, 129U, 239U, 255U));

	menuclickcolor
	= findvar_c("CMenuclickcolor", cl(67U, 67U, 249U, 255U));

	menuoncolor
	= findvar_c("CMenuoncolor", cl(121U, 195U, 120U, 255U));

	menuonselectcolor
	= findvar_c("CMenuonselectcolor", cl(81U, 225U, 70U, 255U));

	menuonclickcolor
	= findvar_c("CMenuonclickcolor", cl(34U, 255U, 38U, 255U));

	menudangercolor
	= findvar_c("CMenudangercolor", cl(255U, 141U, 150U, 255U));

	menudangerselectcolor
	= findvar_c("CMenudangerselectcolor", cl(236U, 91U, 100U, 255U));

	menudangerclickcolor
	= findvar_c("CMenudangerclickcolor", cl(255U, 41U, 51U, 255U));

	menunodangercolor
	= findvar_c("CMenunodangercolor", cl(121U, 195U, 120U, 255U));

	menunodangerselectcolor
	= findvar_c("CMenunodangerselectcolor", cl(81U, 225U, 70U, 255U));

	menunodangerclickcolor
	= findvar_c("CMenunodangerclickcolor", cl(34U, 255U, 38U, 255U));

	menuwidthcolor
	= findvar_c("CMenuwidthcolor", cl(121U, 121U, 235U, 255U));

	menuwidthoutlinecolor
	= findvar_c("CMenuwidthoutlinecolor", cl(0U, 0U, 0U, 255U));

	menuwidthfillcolor
	= findvar_c("CMenuwidthfillcolor", cl(0U, 0U, 0U, 0U));

	menuwidthselfillcolor
	= findvar_c("CMenuwidthselfillcolor", cl(50U, 50U, 50U, 100U));

	menuwidthffillcolor
	= findvar_c("CMenuwidthffillcolor", cl(205U, 30U, 70U, 125U));

	menuheightcolor
	= findvar_c("CMenuheightcolor", cl(121U, 121U, 235U, 255U));

	menuheightoutlinecolor
	= findvar_c("CMenuheightoutlinecolor", cl(0U, 0U, 0U, 255U));

	menuheightfillcolor
	= findvar_c("CMenuheightfillcolor", cl(0U, 0U, 0U, 0U));

	menuheightselfillcolor
	= findvar_c("CMenuheightselfillcolor", cl(50U, 50U, 100U, 100U));

	menuheightffillcolor
	= findvar_c("CMenuheightffillcolor", cl(205U, 30U, 70U,125U));

	menuprofilesmenuoutlinecolor
	= findvar_c("cMenuprofilesmenuoutlinecolor", cl(0U, 0U, 0U, 0U));

	menuprofilesmenufillcolor
	= findvar_c("CMenuprofilesmenufillcolor", cl(0U, 0U, 0U, 0U));
	profilesmenufillfactor = menuprofilesmenufillcolor.a / 255.f;
	menuprofilesmenufillcolor.a = 0;

	menuprofilescolor
	= findvar_c("cMenuprofilescolor", cl(121U, 121U, 235U, 0U));

	menuprofilesselectcolor
	= findvar_c("cMenuprofilesselectcolor", cl(121U, 235U, 121U, 0U));

	menustoriescolor
	= findvar_c("cMenustoriescolor", cl(121U, 121U, 235U, 0U));

	menustoriesselectcolor
	= findvar_c("cMenustoriesselectcolor", cl(121U, 235U, 121U, 0U));

	menuerrorcolor
	= findvar_c("cMenuerrorcolor", cl(221U, 21U, 125U, 0U));

	menuhelpcolor
	= findvar_c("cMenuhelpcolor", cl(120U, 101U, 238U, 0U));

	textchoicecolor
	= findvar_c("cTextchoicecolor", cl(0U, 0U, 0U, 0U));

	textchoiceunavailablecolor
	= findvar_c("cTextchoiceunavailablecolor", cl(100U, 100U, 100U, 0U));

	textchoicefillcolor
	= findvar_c("CTextchoicefillcolor", cl(0U, 0U, 255U, 125U));
	choicefactor = textchoicefillcolor.a / 255.f;
	textchoicefillcolor.a = 0;

	scenario.typeboxcolor
	= findvar_c("cTexttypeboxcolor", cl(0U, 0U, 0U, 0U));

	scenario.typeboxtextcolor
	= findvar_c("cTexttypeboxtextcolor", cl(0U, 0U, 0U, 0U));

	scenario.typeboxfillcolor
	= findvar_c("CTexttypeboxfillcolor", cl(0U, 0U, 0U, 0U));
	typeboxfactor = scenario.typeboxfillcolor.a / 255.f;
	scenario.typeboxfillcolor.a = 0;

	scenario.typeboxfillselcolor
	= findvar_c("CTexttypeboxfillselcolor", cl(0U, 0U, 235U, 125U));
	typeboxfactor2 = scenario.typeboxfillselcolor.a / 255.f;
	scenario.typeboxfillselcolor.a = 0;

	scenario.typeboxunavailablefillcolor
	= findvar_c("CTexttypeboxunavailablefillcolor", cl(255U, 41U, 51U, 125U));
	typeboxunavailablefactor = scenario.typeboxunavailablefillcolor.a / 255.f;
	scenario.typeboxunavailablefillcolor.a = 0;

	scenario.typeboxunavailablefillselcolor 
	= findvar_c("CTexttypeboxunavailablefillselcolor", cl(190U, 25U, 105U, 125U));
	typeboxunavailablefactor2 = scenario.typeboxunavailablefillselcolor.a / 255.f;
	scenario.typeboxunavailablefillselcolor.a = 0;

	scenario.gaintextcolor
	= findvar_c("cTextgaintextcolor", cl(70U, 70U, 70U, 0U));

	scenario.statcolor
		= findvar_c("cStatcolor", cl(235U, 239U, 240U, 0U));

	scenario.statgaincolor
		= findvar_c("cStatgaincolor", cl(255U, 82U, 88U), 255);

	scenario.statlosscolor
		= findvar_c("cStatlosscolor", cl (147U, 146U, 146U), 255);

	scenario.statoppositecolor
		= findvar_c("cStatoppositecolor", cl(47U, 96U, 236U), 255);
=======
	std::getline(reader, name);
	scut(name, 9U, buffer);
	if (!fullscreen) h = scenario.stoiCheck(buffer, 600);
	else h = desktop.y;
	if (h < 600) h = 600;
	else if (static_cast<unsigned int>(h) > desktop.y) h = desktop.y;
	fulltwo = std::to_string(h);

	//scenario.w = w;
	//scenario.h = h;
	scenario.w2 = round(w / 12.f);

	std::getline(reader, name);
	scut(name, 8U, buffer);
	music = scenario.stoiCheck(buffer, 1);

	std::getline(reader, name);
	scut(name, 8U, buffer);
	sound = scenario.stoiCheck(buffer, 1);

	std::getline(reader, name);
	scut(name, 12U, buffer);
	fontsize1 = scenario.stoiCheck(buffer, 44);

	std::getline(reader, name);
	scut(name, 12U, buffer);
	fontsize2 = scenario.stoiCheck(buffer, 58);

	std::getline(reader, name);
	scut(name, 12U, buffer);
	fontsize3 = scenario.stoiCheck(buffer, 76);

	std::getline(reader, name);
	scut(name, 18U, buffer);
	selectionp = scenario.stoiCheck(buffer);

	std::getline(reader, name);
	scut(name, 16U, buffer);
	selections = scenario.stoiCheck(buffer);

	std::getline(reader, name);
	scut(name, 15U, buffer);
	antialias = scenario.stoiCheck(buffer, 4);

	std::getline(reader, name);
	scut(name, 17U, buffer);
	framelimit = scenario.stoiCheck(buffer, 300);

	std::getline(reader, name); scut(name, 14U, buffer);
	textcolor.r = scenario.stoiCheck(buffer, 0);
	std::getline(reader, name); scut(name, 14U, buffer);
	textcolor.g = scenario.stoiCheck(buffer, 0);
	std::getline(reader, name); scut(name, 14U, buffer);
	textcolor.b = scenario.stoiCheck(buffer, 0);
	textcolor.a = 0;

	std::getline(reader, name); scut(name, 14U, buffer);
	menucolor.r = scenario.stoiCheck(buffer, 188);
	std::getline(reader, name); scut(name, 14U, buffer);
	menucolor.g = scenario.stoiCheck(buffer, 188);
	std::getline(reader, name); scut(name, 14U, buffer);
	menucolor.b = scenario.stoiCheck(buffer, 228);

	std::getline(reader, name); scut(name, 20U, buffer);
	menuinsertcolor.r = scenario.stoiCheck(buffer, 202);
	std::getline(reader, name); scut(name, 20U, buffer);
	menuinsertcolor.g = scenario.stoiCheck(buffer, 122);
	std::getline(reader, name); scut(name, 20U, buffer);
	menuinsertcolor.b = scenario.stoiCheck(buffer, 128);

	std::getline(reader, name); scut(name, 20U, buffer);
	menuselectcolor.r = scenario.stoiCheck(buffer, 129);
	std::getline(reader, name); scut(name, 20U, buffer);
	menuselectcolor.g = scenario.stoiCheck(buffer, 129);
	std::getline(reader, name); scut(name, 20U, buffer);
	menuselectcolor.b = scenario.stoiCheck(buffer, 239);

	std::getline(reader, name); scut(name, 19U, buffer);
	menuclickcolor.r = scenario.stoiCheck(buffer, 67);
	std::getline(reader, name); scut(name, 19U, buffer);
	menuclickcolor.g = scenario.stoiCheck(buffer, 67);
	std::getline(reader, name); scut(name, 19U, buffer);
	menuclickcolor.b = scenario.stoiCheck(buffer, 249);

	std::getline(reader, name); scut(name, 16U, buffer);
	menuoncolor.r = scenario.stoiCheck(buffer, 121);
	std::getline(reader, name); scut(name, 16U, buffer);
	menuoncolor.g = scenario.stoiCheck(buffer, 195);
	std::getline(reader, name); scut(name, 16U, buffer);
	menuoncolor.b = scenario.stoiCheck(buffer, 120);

	std::getline(reader, name); scut(name, 22U, buffer);
	menuonselectcolor.r = scenario.stoiCheck(buffer, 81);
	std::getline(reader, name); scut(name, 22U, buffer);
	menuonselectcolor.g = scenario.stoiCheck(buffer, 225);
	std::getline(reader, name); scut(name, 22U, buffer);
	menuonselectcolor.b = scenario.stoiCheck(buffer, 70);

	std::getline(reader, name); scut(name, 21U, buffer);
	menuonclickcolor.r = scenario.stoiCheck(buffer, 34);
	std::getline(reader, name); scut(name, 21U, buffer);
	menuonclickcolor.g = scenario.stoiCheck(buffer, 255);
	std::getline(reader, name); scut(name, 21U, buffer);
	menuonclickcolor.b = scenario.stoiCheck(buffer, 38);

	std::getline(reader, name); scut(name, 20U, buffer);
	menudangercolor.r = scenario.stoiCheck(buffer, 225);
	std::getline(reader, name); scut(name, 20U, buffer);
	menudangercolor.g = scenario.stoiCheck(buffer, 141);
	std::getline(reader, name); scut(name, 20U, buffer);
	menudangercolor.b = scenario.stoiCheck(buffer, 150);

	std::getline(reader, name); scut(name, 26U, buffer);
	menudangerselectcolor.r = scenario.stoiCheck(buffer, 236);
	std::getline(reader, name); scut(name, 26U, buffer);
	menudangerselectcolor.g = scenario.stoiCheck(buffer, 91);
	std::getline(reader, name); scut(name, 26U, buffer);
	menudangerselectcolor.b = scenario.stoiCheck(buffer, 100);

	std::getline(reader, name); scut(name, 25U, buffer);
	menudangerclickcolor.r = scenario.stoiCheck(buffer, 255);
	std::getline(reader, name); scut(name, 25U, buffer);
	menudangerclickcolor.g = scenario.stoiCheck(buffer, 41);
	std::getline(reader, name); scut(name, 25U, buffer);
	menudangerclickcolor.b = scenario.stoiCheck(buffer, 51);

	std::getline(reader, name); scut(name, 22U, buffer);
	menunodangercolor.r = scenario.stoiCheck(buffer, 121);
	std::getline(reader, name); scut(name, 22U, buffer);
	menunodangercolor.g = scenario.stoiCheck(buffer, 195);
	std::getline(reader, name); scut(name, 22U, buffer);
	menunodangercolor.b = scenario.stoiCheck(buffer, 120);

	std::getline(reader, name); scut(name, 28U, buffer);
	menunodangerselectcolor.r = scenario.stoiCheck(buffer, 81);
	std::getline(reader, name); scut(name, 28U, buffer);
	menunodangerselectcolor.g = scenario.stoiCheck(buffer, 225);
	std::getline(reader, name); scut(name, 28U, buffer);
	menunodangerselectcolor.b = scenario.stoiCheck(buffer, 70);

	std::getline(reader, name); scut(name, 27U, buffer);
	menunodangerclickcolor.r = scenario.stoiCheck(buffer, 34);
	std::getline(reader, name); scut(name, 27U, buffer);
	menunodangerclickcolor.g = scenario.stoiCheck(buffer, 255);
	std::getline(reader, name); scut(name, 27U, buffer);
	menunodangerclickcolor.b = scenario.stoiCheck(buffer, 38);

	std::getline(reader, name); scut(name, 19U, buffer);
	menuwidthcolor.r = scenario.stoiCheck(buffer, 121);
	std::getline(reader, name); scut(name, 19U, buffer);
	menuwidthcolor.g = scenario.stoiCheck(buffer, 121);
	std::getline(reader, name); scut(name, 19U, buffer);
	menuwidthcolor.b = scenario.stoiCheck(buffer, 235);

	std::getline(reader, name); scut(name, 26U, buffer);
	menuwidthoutlinecolor.r = scenario.stoiCheck(buffer, 0);
	std::getline(reader, name); scut(name, 26U, buffer);
	menuwidthoutlinecolor.g = scenario.stoiCheck(buffer, 0);
	std::getline(reader, name); scut(name, 26U, buffer);
	menuwidthoutlinecolor.b = scenario.stoiCheck(buffer, 0);

	std::getline(reader, name); scut(name, 23U, buffer);
	menuwidthfillcolor.r = scenario.stoiCheck(buffer, 0);
	std::getline(reader, name); scut(name, 23U, buffer);
	menuwidthfillcolor.g = scenario.stoiCheck(buffer, 0);
	std::getline(reader, name); scut(name, 23U, buffer);
	menuwidthfillcolor.b = scenario.stoiCheck(buffer, 0);
	std::getline(reader, name); scut(name, 23U, buffer);
	menuwidthfillcolor.a = scenario.stoiCheck(buffer, 0);

	std::getline(reader, name); scut(name, 24U, buffer);
	menuwidthsfillcolor.r = scenario.stoiCheck(buffer, 50);
	std::getline(reader, name); scut(name, 24U, buffer);
	menuwidthsfillcolor.g = scenario.stoiCheck(buffer, 50);
	std::getline(reader, name); scut(name, 24U, buffer);
	menuwidthsfillcolor.b = scenario.stoiCheck(buffer, 100);
	std::getline(reader, name); scut(name, 24U, buffer);
	menuwidthsfillcolor.a = scenario.stoiCheck(buffer, 100);

	std::getline(reader, name); scut(name, 24U, buffer);
	menuwidthffillcolor.r = scenario.stoiCheck(buffer, 205);
	std::getline(reader, name); scut(name, 24U, buffer);
	menuwidthffillcolor.g = scenario.stoiCheck(buffer, 30);
	std::getline(reader, name); scut(name, 24U, buffer);
	menuwidthffillcolor.b = scenario.stoiCheck(buffer, 70);
	std::getline(reader, name); scut(name, 24U, buffer);
	menuwidthffillcolor.a = scenario.stoiCheck(buffer, 125);

	std::getline(reader, name); scut(name, 20U, buffer);
	menuheightcolor.r = scenario.stoiCheck(buffer, 121);
	std::getline(reader, name); scut(name, 20U, buffer);
	menuheightcolor.g = scenario.stoiCheck(buffer, 121);
	std::getline(reader, name); scut(name, 20U, buffer);
	menuheightcolor.b = scenario.stoiCheck(buffer, 235);

	std::getline(reader, name); scut(name, 27U, buffer);
	menuheightoutlinecolor.r = scenario.stoiCheck(buffer, 0);
	std::getline(reader, name); scut(name, 27U, buffer);
	menuheightoutlinecolor.g = scenario.stoiCheck(buffer, 0);
	std::getline(reader, name); scut(name, 27U, buffer);
	menuheightoutlinecolor.b = scenario.stoiCheck(buffer, 0);

	std::getline(reader, name); scut(name, 24U, buffer);
	menuheightfillcolor.r = scenario.stoiCheck(buffer, 0);
	std::getline(reader, name); scut(name, 24U, buffer);
	menuheightfillcolor.g = scenario.stoiCheck(buffer, 0);
	std::getline(reader, name); scut(name, 24U, buffer);
	menuheightfillcolor.b = scenario.stoiCheck(buffer, 0);
	std::getline(reader, name); scut(name, 24U, buffer);
	menuheightfillcolor.a = scenario.stoiCheck(buffer, 0);

	std::getline(reader, name); scut(name, 25U, buffer);
	menuheightsfillcolor.r = scenario.stoiCheck(buffer, 50);
	std::getline(reader, name); scut(name, 25U, buffer);
	menuheightsfillcolor.g = scenario.stoiCheck(buffer, 50);
	std::getline(reader, name); scut(name, 25U, buffer);
	menuheightsfillcolor.b = scenario.stoiCheck(buffer, 100);
	std::getline(reader, name); scut(name, 25U, buffer);
	menuheightsfillcolor.a = scenario.stoiCheck(buffer, 100);

	std::getline(reader, name); scut(name, 25U, buffer);
	menuheightffillcolor.r = scenario.stoiCheck(buffer, 205);
	std::getline(reader, name); scut(name, 25U, buffer);
	menuheightffillcolor.g = scenario.stoiCheck(buffer, 30);
	std::getline(reader, name); scut(name, 25U, buffer);
	menuheightffillcolor.b = scenario.stoiCheck(buffer, 70);
	std::getline(reader, name); scut(name, 25U, buffer);
	menuheightffillcolor.a = scenario.stoiCheck(buffer, 125);

	std::getline(reader, name); scut(name, 33U, buffer);
	menuprofilesmenuoutlinecolor.r = scenario.stoiCheck(buffer, 0);
	std::getline(reader, name); scut(name, 33U, buffer);
	menuprofilesmenuoutlinecolor.g = scenario.stoiCheck(buffer, 0);
	std::getline(reader, name); scut(name, 33U, buffer);
	menuprofilesmenuoutlinecolor.b = scenario.stoiCheck(buffer, 0);
	menuprofilesmenuoutlinecolor.a = 0;

	std::getline(reader, name); scut(name, 30U, buffer);
	menuprofilesmenufillcolor.r = scenario.stoiCheck(buffer, 0);
	std::getline(reader, name); scut(name, 30U, buffer);
	menuprofilesmenufillcolor.g = scenario.stoiCheck(buffer, 0);
	std::getline(reader, name); scut(name, 30U, buffer);
	menuprofilesmenufillcolor.b = scenario.stoiCheck(buffer, 0);
	std::getline(reader, name); scut(name, 30U, buffer);
	menuprofilesmenufillcolor.a = 0;
	profilesmenufillfactor = scenario.stoiCheck(buffer, 0) / 255.f;

	std::getline(reader, name); scut(name, 22U, buffer);
	menuprofilescolor.r = scenario.stoiCheck(buffer, 121);
	std::getline(reader, name); scut(name, 22U, buffer);
	menuprofilescolor.g = scenario.stoiCheck(buffer, 121);
	std::getline(reader, name); scut(name, 22U, buffer);
	menuprofilescolor.b = scenario.stoiCheck(buffer, 235);
	menuprofilescolor.a = 0;

	std::getline(reader, name); scut(name, 28U, buffer);
	menuprofilesselectcolor.r = scenario.stoiCheck(buffer, 121);
	std::getline(reader, name); scut(name, 28U, buffer);
	menuprofilesselectcolor.g = scenario.stoiCheck(buffer, 235);
	std::getline(reader, name); scut(name, 28U, buffer);
	menuprofilesselectcolor.b = scenario.stoiCheck(buffer, 121);
	menuprofilesselectcolor.a = 0;

	std::getline(reader, name); scut(name, 21U, buffer);
	menustoriescolor.r = scenario.stoiCheck(buffer, 121);
	std::getline(reader, name); scut(name, 21U, buffer);
	menustoriescolor.g = scenario.stoiCheck(buffer, 121);
	std::getline(reader, name); scut(name, 21U, buffer);
	menustoriescolor.b = scenario.stoiCheck(buffer, 235);
	menustoriescolor.a = 0;

	std::getline(reader, name); scut(name, 27U, buffer);
	menustoriesselectcolor.r = scenario.stoiCheck(buffer, 121);
	std::getline(reader, name); scut(name, 27U, buffer);
	menustoriesselectcolor.g = scenario.stoiCheck(buffer, 235);
	std::getline(reader, name); scut(name, 27U, buffer);
	menustoriesselectcolor.b = scenario.stoiCheck(buffer, 121);
	menustoriesselectcolor.a = 0;

	std::getline(reader, name); scut(name, 19U, buffer);
	menuerrorcolor.r = scenario.stoiCheck(buffer, 221);
	std::getline(reader, name); scut(name, 19U, buffer);
	menuerrorcolor.g = scenario.stoiCheck(buffer, 21);
	std::getline(reader, name); scut(name, 19U, buffer);
	menuerrorcolor.b = scenario.stoiCheck(buffer, 125);

	std::getline(reader, name); scut(name, 14U, buffer);
	scenario.statcolor.r = scenario.stoiCheck(buffer, 235);
	std::getline(reader, name); scut(name, 14U, buffer);
	scenario.statcolor.g = scenario.stoiCheck(buffer, 239);
	std::getline(reader, name); scut(name, 14U, buffer);
	scenario.statcolor.b = scenario.stoiCheck(buffer, 240);
	scenario.statcolor.a = 0;

	std::getline(reader, name); scut(name, 18U, buffer);
	scenario.statgaincolor.r = scenario.stoiCheck(buffer, 255);
	std::getline(reader, name); scut(name, 18U, buffer);
	scenario.statgaincolor.g = scenario.stoiCheck(buffer, 82);
	std::getline(reader, name); scut(name, 18U, buffer);
	scenario.statgaincolor.b = scenario.stoiCheck(buffer, 88);

	std::getline(reader, name); scut(name, 18U, buffer);
	scenario.statlosscolor.r = scenario.stoiCheck(buffer, 147);
	std::getline(reader, name); scut(name, 18U, buffer);
	scenario.statlosscolor.g = scenario.stoiCheck(buffer, 146);
	std::getline(reader, name); scut(name, 18U, buffer);
	scenario.statlosscolor.b = scenario.stoiCheck(buffer, 146);

	std::getline(reader, name); scut(name, 22U, buffer);
	scenario.statoppositecolor.r = scenario.stoiCheck(buffer, 47);
	std::getline(reader, name); scut(name, 22U, buffer);
	scenario.statoppositecolor.g = scenario.stoiCheck(buffer, 96);
	std::getline(reader, name); scut(name, 22U, buffer);
	scenario.statoppositecolor.b = scenario.stoiCheck(buffer, 236);

	std::getline(reader, name); scut(name, 20U, buffer);
	textchoicecolor.r = scenario.stoiCheck(buffer, 0);
	std::getline(reader, name); scut(name, 20U, buffer);
	textchoicecolor.g = scenario.stoiCheck(buffer, 0);
	std::getline(reader, name); scut(name, 20U, buffer);
	textchoicecolor.b = scenario.stoiCheck(buffer, 0);
	textchoicecolor.a = 0;

	std::getline(reader, name); scut(name, 29U, buffer);
	textchoiceunavaiblecolor.r = scenario.stoiCheck(buffer, 100);
	std::getline(reader, name); scut(name, 29U, buffer);
	textchoiceunavaiblecolor.g = scenario.stoiCheck(buffer, 100);
	std::getline(reader, name); scut(name, 29U, buffer);
	textchoiceunavaiblecolor.b = scenario.stoiCheck(buffer, 100);
	textchoiceunavaiblecolor.a = 0;

	std::getline(reader, name); scut(name, 24U, buffer);
	textchoicefillcolor.r = scenario.stoiCheck(buffer, 0);
	std::getline(reader, name); scut(name, 24U, buffer);
	textchoicefillcolor.g = scenario.stoiCheck(buffer, 0);
	std::getline(reader, name); scut(name, 24U, buffer);
	textchoicefillcolor.b = scenario.stoiCheck(buffer, 255);
	std::getline(reader, name); scut(name, 24U, buffer);
	textchoicefillcolor.a = 0;
	choicefactor = scenario.stoiCheck(buffer, 125) / 255.f;

	std::getline(reader, name); scut(name, 18U, buffer);
	menuhelpcolor.r = scenario.stoiCheck(buffer, 120);
	std::getline(reader, name); scut(name, 18U, buffer);
	menuhelpcolor.g = scenario.stoiCheck(buffer, 101);
	std::getline(reader, name); scut(name, 18U, buffer);
	menuhelpcolor.b = scenario.stoiCheck(buffer, 238);

	std::getline(reader, name); scut(name, 21U, buffer);
	scenario.typeboxcolor.r = scenario.stoiCheck(buffer, 0);
	std::getline(reader, name); scut(name, 21U, buffer);
	scenario.typeboxcolor.g = scenario.stoiCheck(buffer, 0);
	std::getline(reader, name); scut(name, 21U, buffer);
	scenario.typeboxcolor.b = scenario.stoiCheck(buffer, 0);
	scenario.typeboxcolor.a = 0;

	std::getline(reader, name); scut(name, 25U, buffer);
	scenario.typeboxtextcolor.r = scenario.stoiCheck(buffer, 0);
	std::getline(reader, name); scut(name, 25U, buffer);
	scenario.typeboxtextcolor.g = scenario.stoiCheck(buffer, 0);
	std::getline(reader, name); scut(name, 25U, buffer);
	scenario.typeboxtextcolor.b = scenario.stoiCheck(buffer, 0);
	scenario.typeboxtextcolor.a = 0;

	std::getline(reader, name); scut(name, 25U, buffer);
	scenario.typeboxfillcolor.r = scenario.stoiCheck(buffer, 0);
	std::getline(reader, name); scut(name, 25U, buffer);
	scenario.typeboxfillcolor.g = scenario.stoiCheck(buffer, 0);
	std::getline(reader, name); scut(name, 25U, buffer);
	scenario.typeboxfillcolor.b = scenario.stoiCheck(buffer, 255);
	std::getline(reader, name); scut(name, 25U, buffer);
	scenario.typeboxfillcolor.a = 0;
	typeboxfactor = scenario.stoiCheck(buffer, 125) / 255.f;

	std::getline(reader, name); scut(name, 22U, buffer);
	scenario.gaintextcolor.r = scenario.stoiCheck(buffer, 70);
	std::getline(reader, name); scut(name, 22U, buffer);
	scenario.gaintextcolor.g = scenario.stoiCheck(buffer, 70);
	std::getline(reader, name); scut(name, 22U, buffer);
	scenario.gaintextcolor.b = scenario.stoiCheck(buffer, 70);
	scenario.gaintextcolor.a = 0;
>>>>>>> 962c618769e951108e54dadcdc7dac935fcb7185
}

void Cmain::SaveToFile()
{
	std::ofstream myfile("../../bin/Options.ini", std::ios::trunc);
<<<<<<< HEAD
	myfile << "bFullscreen = " << (fullscreen ? "true": "false" )
		<< "\niWidth = " << fullone
		<< "\niHeight = " << fulltwo
		<< "\nbMusic = " << (music ? "true" : "false" )
		<< "\nbSound = " << (sound ? "true" : "false" )
		<< "\niFontsize1 = " << fontsize1
		<< "\niFontsize2 = " << fontsize2
		<< "\niFontsize3 = " << fontsize3
		<< "\niCurrentProfile = " << selectionp
		<< "\niCurrentStory = " << selections
		<< "\niAntialiasing = " << antialias
		<< "\niFramerateLimit = " << framelimit
		<< "\ncTextcolor = " << static_cast<int>(textcolor.r) << ", " << static_cast<int>(textcolor.g) << ", " << static_cast<int>(textcolor.b)
		<< "\nCMenucolor = " << static_cast<int>(menucolor.r) << ", " << static_cast<int>(menucolor.g) << ", " << static_cast<int>(menucolor.b) << ", " << static_cast<int>(menucolor.a)
		<< "\nCMenuinsertcolor = " << static_cast<int>(menuinsertcolor.r) << ", " << static_cast<int>(menuinsertcolor.g) << ", " << static_cast<int>(menuinsertcolor.b) << ", " << static_cast<int>(menuinsertcolor.a)
		<< "\nCMenuselectcolor = " << static_cast<int>(menuselectcolor.r) << ", " << static_cast<int>(menuselectcolor.g) << ", " << static_cast<int>(menuselectcolor.b) << ", " << static_cast<int>(menuselectcolor.a)
		<< "\nCMenuclickcolor = " << static_cast<int>(menuclickcolor.r) << ", " << static_cast<int>(menuclickcolor.g) << ", " << static_cast<int>(menuclickcolor.b) << ", " << static_cast<int>(menuclickcolor.a)
		<< "\nCMenuoncolor = " << static_cast<int>(menuoncolor.r) << ", " << static_cast<int>(menuoncolor.g) << ", " << static_cast<int>(menuoncolor.b) << ", " << static_cast<int>(menuoncolor.a)
		<< "\nCMenuonselectcolor = " << static_cast<int>(menuonselectcolor.r) << ", " << static_cast<int>(menuonselectcolor.g) << ", " << static_cast<int>(menuonselectcolor.b) << ", " << static_cast<int>(menuonselectcolor.a)
		<< "\nCMenuonclickcolor = " << static_cast<int>(menuonclickcolor.r) << ", " << static_cast<int>(menuonclickcolor.g) << ", " << static_cast<int>(menuonclickcolor.b) << ", " << static_cast<int>(menuonclickcolor.a)
		<< "\nCMenudangercolor = " << static_cast<int>(menudangercolor.r) << ", " << static_cast<int>(menudangercolor.g) << ", " << static_cast<int>(menudangercolor.b) << ", " << static_cast<int>(menudangercolor.a)
		<< "\nCMenudangerselectcolor = " << static_cast<int>(menudangerselectcolor.r) << ", " << static_cast<int>(menudangerselectcolor.g) << ", " << static_cast<int>(menudangerselectcolor.b) << ", " << static_cast<int>(menudangerselectcolor.a)
		<< "\nCMenudangerclickcolor = " << static_cast<int>(menudangerclickcolor.r) << ", " << static_cast<int>(menudangerclickcolor.g) << ", " << static_cast<int>(menudangerclickcolor.b) << ", " << static_cast<int>(menudangerclickcolor.a)
		<< "\nCMenunodangercolor = " << static_cast<int>(menunodangercolor.r) << ", " << static_cast<int>(menunodangercolor.g) << ", " << static_cast<int>(menunodangercolor.b) << ", " << static_cast<int>(menunodangercolor.a)
		<< "\nCMenunodangerselectcolor = " << static_cast<int>(menunodangerselectcolor.r) << ", " << static_cast<int>(menunodangerselectcolor.g) << ", " << static_cast<int>(menunodangerselectcolor.b) << ", " << static_cast<int>(menunodangerselectcolor.a)
		<< "\nCMenunodangerclickcolor = " << static_cast<int>(menunodangerclickcolor.r) << ", " << static_cast<int>(menunodangerclickcolor.g) << ", " << static_cast<int>(menunodangerclickcolor.b) << ", " << static_cast<int>(menunodangerclickcolor.a)
		<< "\nCMenuwidthcolor = " << static_cast<int>(menuwidthcolor.r) << ", " << static_cast<int>(menuwidthcolor.g) << ", " << static_cast<int>(menuwidthcolor.b) << ", " << static_cast<int>(menuwidthcolor.a)
		<< "\nCMenuwidthoutlinecolor = " << static_cast<int>(menuwidthoutlinecolor.r) << ", " << static_cast<int>(menuwidthoutlinecolor.g) << ", " << static_cast<int>(menuwidthoutlinecolor.b) << ", " << static_cast<int>(menuwidthoutlinecolor.a)
		<< "\nCMenuwidthfillcolor = " << static_cast<int>(menuwidthfillcolor.r) << ", " << static_cast<int>(menuwidthfillcolor.g) << ", " << static_cast<int>(menuwidthfillcolor.b) << ", " << static_cast<int>(menuwidthfillcolor.a)
		<< "\nCMenuwidthselfillcolor = " << static_cast<int>(menuwidthselfillcolor.r) << ", " << static_cast<int>(menuwidthselfillcolor.g) << ", " << static_cast<int>(menuwidthselfillcolor.b) << ", " << static_cast<int>(menuwidthselfillcolor.a)
		<< "\nCMenuwidthffillcolor = " << static_cast<int>(menuwidthffillcolor.r) << ", " << static_cast<int>(menuwidthffillcolor.g) << ", " << static_cast<int>(menuwidthffillcolor.b) << ", " << static_cast<int>(menuwidthffillcolor.a)
		<< "\nCMenuheightcolor = " << static_cast<int>(menuheightcolor.r) << ", " << static_cast<int>(menuheightcolor.g) << ", " << static_cast<int>(menuheightcolor.b) << ", " << static_cast<int>(menuheightcolor.a)
		<< "\nCMenuheightoutlinecolor = " << static_cast<int>(menuheightoutlinecolor.r) << ", " << static_cast<int>(menuheightoutlinecolor.g) << ", " << static_cast<int>(menuheightoutlinecolor.b) << ", " << static_cast<int>(menuheightoutlinecolor.a)
		<< "\nCMenuheightfillcolor = " << static_cast<int>(menuheightfillcolor.r) << ", " << static_cast<int>(menuheightfillcolor.g) << ", " << static_cast<int>(menuheightfillcolor.b) << ", " << static_cast<int>(menuheightfillcolor.a)
		<< "\nCMenuheightselfillcolor = " << static_cast<int>(menuheightselfillcolor.r) << ", " << static_cast<int>(menuheightselfillcolor.g) << ", " << static_cast<int>(menuheightselfillcolor.b) << ", " << static_cast<int>(menuheightselfillcolor.a)
		<< "\nCMenuheightffillcolor = " << static_cast<int>(menuheightffillcolor.r) << ", " << static_cast<int>(menuheightffillcolor.g) << ", " << static_cast<int>(menuheightffillcolor.b) << ", " << static_cast<int>(menuheightffillcolor.a)
		<< "\ncMenuprofilesmenuoutlinecolor = " << static_cast<int>(menuprofilesmenuoutlinecolor.r) << ", " << static_cast<int>(menuprofilesmenuoutlinecolor.g) << ", " << static_cast<int>(menuprofilesmenuoutlinecolor.b)
		<< "\nCMenuprofilesmenufillcolor = " << static_cast<int>(menuprofilesmenufillcolor.r) << ", " << static_cast<int>(menuprofilesmenufillcolor.g) << ", " << static_cast<int>(menuprofilesmenufillcolor.b) << ", " << static_cast<int>(round(profilesmenufillfactor * 255.f))
		<< "\ncMenuprofilescolor = " << static_cast<int>(menuprofilescolor.r) << ", " << static_cast<int>(menuprofilescolor.g) << ", " << static_cast<int>(menuprofilescolor.b)
		<< "\ncMenuprofilesselectcolor = " << static_cast<int>(menuprofilesselectcolor.r) << ", " << static_cast<int>(menuprofilesselectcolor.g) << ", " << static_cast<int>(menuprofilesselectcolor.b)
		<< "\ncMenustoriescolor = " << static_cast<int>(menustoriescolor.r) << ", " << static_cast<int>(menustoriescolor.g) << ", " << static_cast<int>(menustoriescolor.b)
		<< "\ncMenustoriesselectcolor = " << static_cast<int>(menustoriesselectcolor.r) << ", " << static_cast<int>(menustoriesselectcolor.g) << ", " << static_cast<int>(menustoriesselectcolor.b)
		<< "\ncMenuerrorcolor = " << static_cast<int>(menuerrorcolor.r) << ", " << static_cast<int>(menuerrorcolor.g) << ", " << static_cast<int>(menuerrorcolor.b)
		<< "\ncMenuhelpcolor = " << static_cast<int>(menuhelpcolor.r) << ", " << static_cast<int>(menuhelpcolor.g) << ", " << static_cast<int>(menuhelpcolor.b)
		<< "\ncTextchoicecolor = " << static_cast<int>(textchoicecolor.r) << ", " << static_cast<int>(textchoicecolor.g) << ", " << static_cast<int>(textchoicecolor.b)
		<< "\ncTextchoiceunavailablecolor = " << static_cast<int>(textchoiceunavailablecolor.r) << ", " << static_cast<int>(textchoiceunavailablecolor.g) << ", " << static_cast<int>(textchoiceunavailablecolor.b)
		<< "\nCTextchoicefillcolor = " << static_cast<int>(textchoicefillcolor.r) << ", " << static_cast<int>(textchoicefillcolor.g) << ", " << static_cast<int>(textchoicefillcolor.b) << ", " << static_cast<int>(round(choicefactor * 255.f))
		<< "\ncTexttypeboxcolor = " << static_cast<int>(scenario.typeboxcolor.r) << ", " << static_cast<int>(scenario.typeboxcolor.g) << ", " << static_cast<int>(scenario.typeboxcolor.b)
		<< "\ncTexttypeboxtextcolor = " << static_cast<int>(scenario.typeboxtextcolor.r) << ", " << static_cast<int>(scenario.typeboxtextcolor.g) << ", " << static_cast<int>(scenario.typeboxtextcolor.b)
		<< "\nCTexttypeboxfillcolor = " << static_cast<int>(scenario.typeboxfillcolor.r) << ", " << static_cast<int>(scenario.typeboxfillcolor.g) << ", " << static_cast<int>(scenario.typeboxfillcolor.b) << ", " << static_cast<int>(round(typeboxfactor * 255.f))
		<< "\nCTexttypeboxfillselcolor = " << static_cast<int>(scenario.typeboxfillselcolor.r) << ", " << static_cast<int>(scenario.typeboxfillselcolor.g) << ", " << static_cast<int>(scenario.typeboxfillselcolor.b) << ", " << static_cast<int>(round(typeboxunavailablefactor * 255.f))
		<< "\nCTexttypeboxunavailablefillcolor = " << static_cast<int>(scenario.typeboxunavailablefillcolor.r) << ", " << static_cast<int>(scenario.typeboxunavailablefillcolor.g) << ", " << static_cast<int>(scenario.typeboxunavailablefillcolor.b) << ", " << static_cast<int>(round(typeboxfactor2 * 255.f))
		<< "\nCTexttypeboxunavailablefillselcolor = " << static_cast<int>(scenario.typeboxunavailablefillselcolor.r) << ", " << static_cast<int>(scenario.typeboxunavailablefillselcolor.g) << ", " << static_cast<int>(scenario.typeboxunavailablefillselcolor.b) << ", " << static_cast<int>(round(typeboxunavailablefactor2 * 255.f))
		<< "\ncTextgaintextcolor = " << static_cast<int>(scenario.gaintextcolor.r) << ", " << static_cast<int>(scenario.gaintextcolor.g) << ", " << static_cast<int>(scenario.gaintextcolor.b)
		<< "\ncStatcolor = " << static_cast<int>(scenario.statcolor.r) << ", " << static_cast<int>(scenario.statcolor.g) << ", " << static_cast<int>(scenario.statcolor.b)
		<< "\ncStatgaincolor = " << static_cast<int>(scenario.statgaincolor.r) << ", " << static_cast<int>(scenario.statgaincolor.g) << ", " << static_cast<int>(scenario.statgaincolor.b)
		<< "\ncStatlosscolor = " << static_cast<int>(scenario.statlosscolor.r) << ", " << static_cast<int>(scenario.statlosscolor.g) << ", " << static_cast<int>(scenario.statlosscolor.b)
		<< "\ncStatoppositecolor = " << static_cast<int>(scenario.statoppositecolor.r) << ", " << static_cast<int>(scenario.statoppositecolor.g) << ", " << static_cast<int>(scenario.statoppositecolor.b)
=======
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
		<< "\ntextcolor.r = " << static_cast<int>(textcolor.r)
		<< "\ntextcolor.g = " << static_cast<int>(textcolor.g)
		<< "\ntextcolor.b = " << static_cast<int>(textcolor.b)
		<< "\nmenucolor.r = " << static_cast<int>(menucolor.r)
		<< "\nmenucolor.g = " << static_cast<int>(menucolor.g)
		<< "\nmenucolor.b = " << static_cast<int>(menucolor.b)
		<< "\nmenuinsertcolor.r = " << static_cast<int>(menuinsertcolor.r)
		<< "\nmenuinsertcolor.g = " << static_cast<int>(menuinsertcolor.g)
		<< "\nmenuinsertcolor.b = " << static_cast<int>(menuinsertcolor.b)
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
		<< "\nmenuerrorcolor.r = " << static_cast<int>(menuerrorcolor.r)
		<< "\nmenuerrorcolor.g = " << static_cast<int>(menuerrorcolor.g)
		<< "\nmenuerrorcolor.b = " << static_cast<int>(menuerrorcolor.b)
		<< "\nstatcolor.r = " << static_cast<int>(scenario.statcolor.r)
		<< "\nstatcolor.g = " << static_cast<int>(scenario.statcolor.g)
		<< "\nstatcolor.b = " << static_cast<int>(scenario.statcolor.b)
		<< "\nstatgaincolor.r = " << static_cast<int>(scenario.statgaincolor.r)
		<< "\nstatgaincolor.g = " << static_cast<int>(scenario.statgaincolor.g)
		<< "\nstatgaincolor.b = " << static_cast<int>(scenario.statgaincolor.b)
		<< "\nstatlosscolor.r = " << static_cast<int>(scenario.statlosscolor.r)
		<< "\nstatlosscolor.g = " << static_cast<int>(scenario.statlosscolor.g)
		<< "\nstatlosscolor.b = " << static_cast<int>(scenario.statlosscolor.b)
		<< "\nstatoppositecolor.r = " << static_cast<int>(scenario.statoppositecolor.r)
		<< "\nstatoppositecolor.g = " << static_cast<int>(scenario.statoppositecolor.g)
		<< "\nstatoppositecolor.b = " << static_cast<int>(scenario.statoppositecolor.b)
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
		<< "\ntexttypeboxcolor.r = " << static_cast<int>(scenario.typeboxcolor.r)
		<< "\ntexttypeboxcolor.g = " << static_cast<int>(scenario.typeboxcolor.g)
		<< "\ntexttypeboxcolor.b = " << static_cast<int>(scenario.typeboxcolor.b)
		<< "\ntexttypeboxtextcolor.r = " << static_cast<int>(scenario.typeboxtextcolor.r)
		<< "\ntexttypeboxtextcolor.g = " << static_cast<int>(scenario.typeboxtextcolor.g)
		<< "\ntexttypeboxtextcolor.b = " << static_cast<int>(scenario.typeboxtextcolor.b)
		<< "\ntexttypeboxfillcolor.r = " << static_cast<int>(scenario.typeboxfillcolor.r)
		<< "\ntexttypeboxfillcolor.g = " << static_cast<int>(scenario.typeboxfillcolor.g)
		<< "\ntexttypeboxfillcolor.b = " << static_cast<int>(scenario.typeboxfillcolor.b)
		<< "\ntexttypeboxfillcolor.a = " << static_cast<int>(round(typeboxfactor * 255.f))
		<< "\ntextgaintextcolor.r = " << static_cast<int>(scenario.gaintextcolor.r)
		<< "\ntextgaintextcolor.g = " << static_cast<int>(scenario.gaintextcolor.g)
		<< "\ntextgaintextcolor.b = " << static_cast<int>(scenario.gaintextcolor.b)
>>>>>>> 962c618769e951108e54dadcdc7dac935fcb7185
		<< std::endl;
		//todo colors in one line with prefix, cuz its so unreadable
	myfile.close();
}
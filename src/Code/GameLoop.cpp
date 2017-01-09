/*
@Author: LightTab2
The MIT License(MIT)

Copyright(c) 2016 LightTab2 azorro12@gmail.com
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and / or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "Cmain.h"

inline bool Cmain::Contains(sf::FloatRect &box)
{
	return box.contains(mousepos);
}

void Cmain::GameLoop()
{
	while (!quit) {
		MainEvent();
		window.clear();
		onTick();
		GameMenu();
		window.display();
	}
}
	
void Cmain::GameMenu()
{
	PrepareMenu();
	if (!clicked) {
		if (Contains(button_1)) {
			if (disbutton) return;
			if (gamestate == 4) {
				button_1_text.setFillColor(music ? menuonselectcolor : menuselectcolor);
				button_2_text.setFillColor(sound ? menuoncolor : menucolor);
				button_3_text.setFillColor(menucolor);
			}
			else if (gamestate != -1){
				button_1_text.setFillColor(menuselectcolor);
				if (gamestate == 3) button_2_text.setFillColor(fullscreen ? menuoncolor : menucolor);
				else button_2_text.setFillColor(menucolor);
			}
			disrandomnameLOL = disbutton = true;
		}
		else if (Contains(button_2)) {
			if (disbutton) return;
			if (gamestate == 4) {
				button_1_text.setFillColor(music ? menuoncolor : menucolor);
				button_2_text.setFillColor(sound ? menuonselectcolor : menuselectcolor);
				button_3_text.setFillColor(menucolor);
			}
			else if (gamestate == 6 || gamestate == 7) {
				button_2_text.setFillColor(k_delete ? menunodangerselectcolor : menuselectcolor);
				button_3_text.setFillColor(k_delete ? menudangercolor : menucolor);
			}
			else if (gamestate == -1)
			{
				button_2_text.setFillColor(menunodangerselectcolor);
				button_3_text.setFillColor(menudangercolor);
			}
			else {
				button_1_text.setFillColor(menucolor);
				if (gamestate == 3) button_2_text.setFillColor(fullscreen ? menuonselectcolor : menuselectcolor);
				else button_2_text.setFillColor(menuselectcolor);
				button_3_text.setFillColor(menucolor);
			}
			disrandomnameLOL = disbutton = true; 
		}
		else if (Contains(button_3)) {
			if (disbutton) return;
			if (gamestate == 4) {
				button_1_text.setFillColor(music ? menuoncolor : menucolor);
				button_2_text.setFillColor(sound ? menuoncolor : menucolor);
				button_3_text.setFillColor(menuselectcolor);
			}
			else if (gamestate == 6 || gamestate == 7) {
				button_2_text.setFillColor(k_delete ? menunodangercolor : menucolor);
				button_3_text.setFillColor(k_delete ? menudangerselectcolor : menuselectcolor);
			}
			else if (gamestate == -1)
			{
				button_2_text.setFillColor(menunodangercolor);
				button_3_text.setFillColor(menudangerselectcolor);
			}
			else {
				button_1_text.setFillColor(menucolor);
				if (gamestate == 3) button_2_text.setFillColor(fullscreen ? menuoncolor : menucolor);
				else button_2_text.setFillColor(menucolor);
				button_3_text.setFillColor(menuselectcolor);
			}
			disrandomnameLOL = disbutton = true;
		}
		else if (disrandomnameLOL) {
			if (gamestate == 4)
			{
				button_1_text.setFillColor(music ? menuoncolor : menucolor);
				button_2_text.setFillColor(sound ? menuoncolor : menucolor);
				button_3_text.setFillColor(menucolor);
			}
			else if (gamestate == 6 || gamestate == 7) {
				button_2_text.setFillColor(k_delete ? menunodangercolor : menucolor);
				button_3_text.setFillColor(k_delete ? menudangercolor : menucolor);
			}
			else if (gamestate == -1)
			{
				button_2_text.setFillColor(menunodangercolor);
				button_3_text.setFillColor(menudangercolor);
			}
			else {
				button_1_text.setFillColor(menucolor);
				if (gamestate == 3) button_2_text.setFillColor(fullscreen ? menuoncolor : menucolor);
				else button_2_text.setFillColor(menucolor);
				button_3_text.setFillColor(menucolor);
			}
			disrandomnameLOL = disbutton = false;
		}
	}
	else
	{
		if (Contains(button_1)) {
			if (!disbutton) return;
			if (gamestate == 4) {
				button_1_text.setFillColor(music ? menuonclickcolor : menuclickcolor);
				button_2_text.setFillColor(sound ? menuoncolor : menucolor);
				button_3_text.setFillColor(menucolor);
			}
			else if (gamestate != -1){
				button_1_text.setFillColor(menuclickcolor);
				if (gamestate == 3) button_2_text.setFillColor(fullscreen ? menuoncolor : menucolor);
				else button_2_text.setFillColor(menucolor);
				button_3_text.setFillColor(menucolor);
			}
			disrandomnameLOL = disbutton = false;
		}
		else if (Contains(button_2)) {
			if (!disbutton) return;
			if (gamestate == 4) {
				button_1_text.setFillColor(music ? menuoncolor : menucolor);
				button_2_text.setFillColor(sound ? menuonclickcolor : menuclickcolor);
				button_3_text.setFillColor(menucolor);
			}
			else if (gamestate == 6 || gamestate == 7) {
				button_2_text.setFillColor(k_delete ? menunodangerclickcolor : menuclickcolor);
				button_3_text.setFillColor(k_delete ? menudangercolor : menucolor);
			}
			else if (gamestate == -1)
			{
				button_2_text.setFillColor(menunodangerclickcolor);
				button_3_text.setFillColor(menudangercolor);
			}
			else {
				button_1_text.setFillColor(menucolor);
				if (gamestate == 3) button_2_text.setFillColor(fullscreen ? menuonclickcolor : menuclickcolor);
				else button_2_text.setFillColor(menuclickcolor);
				button_3_text.setFillColor(menucolor);
			}
			disrandomnameLOL = disbutton = false;
		}
		else if (Contains(button_3)) {
			if (!disbutton) return;
			if (gamestate == 4) {
				button_1_text.setFillColor(music ? menuoncolor : menucolor);
				button_2_text.setFillColor(sound ? menuoncolor : menucolor);
				button_3_text.setFillColor(menuclickcolor);
			}
			else if (gamestate == 6 || gamestate == 7) {
				button_2_text.setFillColor(k_delete ? menunodangercolor : menucolor);
				button_3_text.setFillColor(k_delete ? menudangerclickcolor : menuclickcolor);
			}
			else if (gamestate == -1)
			{
				button_2_text.setFillColor(menunodangercolor);
				button_3_text.setFillColor(menudangerclickcolor);
			}
			else {
				button_1_text.setFillColor(menucolor);
				if (gamestate == 3) button_2_text.setFillColor(fullscreen ? menuoncolor : menucolor);
				else button_2_text.setFillColor(menucolor);
				button_3_text.setFillColor(menuclickcolor);
			}
			disrandomnameLOL = disbutton = false;
		}
		else if (!disrandomnameLOL) {
			if (gamestate == 4)
			{
				button_1_text.setFillColor(music ? menuoncolor : menucolor);
				button_2_text.setFillColor(sound ? menuoncolor : menucolor);
				button_3_text.setFillColor(menucolor);
			}
			else if (gamestate == 6 || gamestate == 7) {
				button_2_text.setFillColor(k_delete ? menunodangercolor : menucolor);
				button_3_text.setFillColor(k_delete ? menudangercolor : menucolor);
			}
			else if (gamestate == -1)
			{
				button_2_text.setFillColor(menunodangercolor);
				button_3_text.setFillColor(menudangercolor);
			}
			else {
				button_1_text.setFillColor(menucolor);
				if (gamestate == 3) button_2_text.setFillColor(fullscreen ? menuoncolor : menucolor);
				else button_2_text.setFillColor(menucolor);
				button_3_text.setFillColor(menucolor);
			}
			disrandomnameLOL = disbutton = true;
		}
	}
}

void Cmain::DeleteStory()
{
	std::ofstream sfile("bin/Stories.txt", std::ios::out | std::ios::trunc);
	for (unsigned int s = 0U, size = profiles.size(); s < size; ++s)
	{
		remove(std::string("bin/Saves/" + profiles[s].getString().toAnsiString() + "_" + stories[selections].getString().toAnsiString() + ".txt").c_str());
	}
	stories.erase(stories.begin() + selections);
	arroweds -= 1;
	if (arroweds < 0) arroweds = 0;
	arroweds_margin -= 1;
	if (arroweds_margin < 0) arroweds_margin = 0;
	selections -= 1;
	if (selections < 0) selections = 0;
	for (unsigned int i = 0U, size = stories.size(); i < size; ++i)
	{
		sfile << stories[i].getString().toAnsiString() << std::endl;
	}
	scheck = true;
	k_delete = false;
	if (profiles.empty()) scenario.pempty = true;
	else if (stories.empty()) { scenario.pempty = false; scenario.sempty = true; }
	if (!scenario.sempty && !scenario.pempty) scenario.savefile = L"bin/Saves/" + profiles[selectionp].getString().toWideString() + L"_" + stories[selections].getString().toWideString() + L".txt";
	else scenario.pempty = scenario.sempty = false;
	scenario.path = "bin/Scripts/" + stories[selections].getString() + ".txt";
	LoadSave();
}

void Cmain::DeleteProfile()
{
	std::ofstream pfile("bin/Profiles.txt", std::ios::out | std::ios::trunc);
	for (unsigned int s = 0U, size = stories.size(); s < size; ++s)
	{
		remove(std::string("bin/Saves/" + profiles[selectionp].getString().toAnsiString() + "_" + stories[s].getString().toAnsiString() + ".txt").c_str());
	}
	profiles.erase(profiles.begin() + selectionp);
	arrowedp -= 1;
	if (arrowedp < 0) arrowedp = 0;
	arrowedp_margin -= 1;
	selectionp -= 1;
	if (selectionp < 0) selectionp = 0;
	if (arrowedp_margin < 0) arrowedp_margin = 0;
	for (unsigned int i = 0U, size = profiles.size(); i < size; ++i)
	{
		pfile << profiles[i].getString().toAnsiString() << std::endl;
	}
	pcheck = true;
	k_delete = false;
	if (profiles.empty()) scenario.pempty = true;
	else if (stories.empty()) { scenario.pempty = false; scenario.sempty = true; }
	else scenario.pempty = scenario.sempty = false;
	LoadSave();
}

void Cmain::Show_stats()
{
	s_pos.clear();
	i_pos.clear();
	v_pos.clear();
	s_posv.clear();
	v_posi.clear();
	sf::Text astat = scenario.tekst;
	astat.setFillColor(sf::Color(textcolor.r, textcolor.g, textcolor.b, static_cast<sf::Uint8>(0)));
	astat.setCharacterSize(static_cast<int>(astat.getCharacterSize() * 0.8f));
	astat.setString(L"WMP¥Ê¹êjpgqiL");

	she = static_cast<int>(astat.getGlobalBounds().height);
	for (int prior = priorlimit; prior >= 0; --prior)
	{
		for (auto &s : scenario.s_stats)
		{
			if (!s.read && s.prior == prior && (!s.hidden || !s.vhidden))
			{
				if (!s.hidden) astat.setString(s.name + L": ");
				else if (!s.vhidden) astat.setString(astat.getString() + s.value);
				astat.setPosition(round(w / 12.f), static_cast<float>(she));
				s_pos.push_back(astat);
				s_posv.push_back(static_cast<sf::Vector2i>(s_pos.back().getPosition()));
				she += scenario.th;
				s.address = s_pos.size() - 1U;
				s.read = true;
			}
		}
		for (auto &i : scenario.io_stats)
		{
			if (!i.read && i.prior == prior && !i.hidden)
			{
				astat.setString(i.name);
				astat.setPosition(round(w / 12.f), static_cast<float>(she));
				s_pos.push_back(astat);
				s_posv.push_back(static_cast<sf::Vector2i>(s_pos.back().getPosition()));
				astat.setString(std::to_wstring(i.value));
				astat.setPosition(round(w / 2.f), static_cast<float>(she));
				s_pos.push_back(astat);
				s_posv.push_back(static_cast<sf::Vector2i>(s_pos.back().getPosition()));
				astat.setString(i.opposite);
				astat.setPosition(round(w - w / 12 - astat.getGlobalBounds().width), static_cast<float>(she));
				she += scenario.th;
				s_pos.push_back(astat);
				s_posv.push_back(static_cast<sf::Vector2i>(s_pos.back().getPosition()));
				i.read = true;
			}
		}
		for (auto &i : scenario.i_stats)
		{
			if (!i.read && i.prior == prior && !i.hidden)
			{
				astat.setString(i.name + L": " + std::to_wstring(static_cast<int>(i.value * 100.f / i.max)) + L"%");
				astat.setPosition(round(w / 11.f), static_cast<float>(she));
				astat.setFillColor(statcolor);
				astat.setStyle(sf::Text::Bold);
				s_pos.push_back(astat);
				s_posv.push_back(static_cast<sf::Vector2i>(s_pos.back().getPosition()));
				astat.setFillColor(sf::Color(textcolor.r, textcolor.g, textcolor.b, static_cast<sf::Uint8>(0)));
				astat.setStyle(sf::Text::Regular);

				i_pos.push_back(sf::Texture());
				i_pos.back().loadFromImage(IntSpecial(static_cast<int>(w / 2.5f), static_cast<int>(s_pos.back().getGlobalBounds().height * 1.6f), i.value, i.min, i.max));
				v_pos.push_back(sf::Sprite(i_pos.back()));
				v_pos.back().setPosition(round(w / 12.f), round(s_pos.back().getGlobalBounds().top - s_pos.back().getGlobalBounds().height * 0.3f));
				v_pos.back().setColor(sf::Color(v_pos.back().getColor().r, v_pos.back().getColor().g, v_pos.back().getColor().b, static_cast<sf::Uint8>(0)));
				v_posi.push_back(sf::Vector2i(static_cast<int>(round(w / 12.f)), static_cast<int>(v_pos.back().getPosition().y)));
				she += static_cast<int>(v_pos.back().getGlobalBounds().height *1.1f);
				i.address = i_pos.size() - 1U;
				i.read = true;
			}
		}
		for (auto &i : scenario.Ints)
		{
			if (!i.read && i.prior == prior && !i.hidden)
			{
				astat.setString(i.name);
				astat.setPosition(round(w / 12.f), static_cast<float>(she));
				s_pos.push_back(astat);
				s_posv.push_back(static_cast<sf::Vector2i>(s_pos.back().getPosition()));
				astat.setString(std::to_wstring(i.value));
				astat.setPosition(round(w / 2.f), static_cast<float>(she));
				she += scenario.th;
				s_pos.push_back(astat);
				s_posv.push_back(static_cast<sf::Vector2i>(s_pos.back().getPosition()));
				i.read = true;
			}
		}
	}
	for (auto &s : scenario.s_stats) s.read = false;
	for (auto &i : scenario.io_stats) i.read = false;
	for (auto &i : scenario.i_stats) i.read = false;
	for (auto &i : scenario.Ints) i.read = false;
}

void Cmain::LoadSave()
{
	scenario.i_stats.clear();
	scenario.io_stats.clear();
	scenario.s_stats.clear();
	scenario.Ints.clear();
	s_pos.clear();
	i_pos.clear();
	v_pos.clear();
	s_posv.clear();
	v_posi.clear();
	if (selectionp >= profiles.size()) return;
	else if (selections >= stories.size()) return;
	begin: std::wfstream save(L"bin/Saves/" + profiles[selectionp].getString().toWideString() + L"_" + stories[selections].getString().toWideString() + L".txt");
	if (save)
	{
		std::wstring insert;
		const std::locale empty_locales = std::locale::empty();
		const std::codecvt_utf8<wchar_t>* converters = new std::codecvt_utf8<wchar_t>;
		const std::locale utf8_locales = std::locale(empty_locales, converters);
		save.imbue(utf8_locales);
		int state = 0;
		while (state < 5) //reading... 
		{
			std::getline(save, insert);
			//if (insert.empty()){ scenario.mfile << '[' << scenario.sgoto << ']' << L"Error: the save contains an empty line or is empty" << std::endl; break; }
			if (insert.empty()) break;
			if (insert[0] == L'}'){
				++state;
				continue;
			}
			std::wstring name;
			int arglistx;
			if (state == 0)
			{
				static sf::Uint8 t = 0;
				switch (t)
				{
				case 0:
					scenario.stoicheck(insert, scenario.sgoto);// throw std::runtime_error("FATAL stoicheck failure(save loading, \"goto\" variable)");
					scenario.cgoto = scenario.sgoto;
					break;
				case 1:
					scenario.stoicheck(insert, scenario.dgoto);
					break;
				case 2:
					int variable = 0;
					if (!scenario.stoicheck(insert, variable));// throw std::runtime_error("FATAL stoicheck failure(save loading, \"loadtextonly\" variable)");
					scenario.loadtextonly = variable;
					break;
				}
				++t;
				continue;
			}
			else if (state == 1){
				name = L"IntStatOpposite";
				arglistx = 7;
			}
			else if (state == 2){
				name = L"IntStat";
				arglistx = 5;
			}
			else if (state == 3){
				name = L"StringStat";
				arglistx = 4;
			}
			else if (state == 4)
			{
				name = L"Int";
				arglistx = 3;
			}
			std::wstring names[2];
			int arguments[6];
			int arglist;
			int namelist = 0;
			for (arglist = 0; arglist < arglistx; ++arglist)
			{
				unsigned int __w64 s_position;
				if (insert.empty() || (s_position = insert.find(L',')) == std::wstring::npos)
				{
					//scenario.mfile << '[' << scenario.sgoto << ']' << L"Error: an/a \"" + name + L"\" with name \"" << names[0].empty() ? L"unknown" : names[0];
					//if (insert.empty()) scenario.mfile << L"\" couldn't be loaded (an empty argument " << arglist << L')' << std::endl/*L*/;
					//else scenario.mfile << L"\" couldn't be loaded (missing argument " << arglist << L')' << std::endl/*L*/;
					break;
				}
				switch (arglist)
				{
				case 0:
					names[0] = insert.substr(0, s_position);
					if (scenario.chName(names[0])) continue;
					++namelist;
					break;
				case 1:
					if (state == 1) {
						names[1] = insert.substr(0, s_position);
						++namelist;
					}
					if (!scenario.stoicheck(insert.substr(0, s_position), arguments[0])) { /* scenario.mfile << L"[Stat]Error: An/a " + name + L" with name " + names[0] + L" failed its stoicheck on argument 1"; */ return; }
					break;
				default:
					if (!scenario.stoicheck(insert.substr(0, s_position), arguments[arglist - 1])) { /* scenario.mfile << "[Stat]Error: An/a " << name << " with name " << names[0] << " failed its stoicheck on argument " << arglist; */ return; }
					break;
				}
				insert = insert.substr(s_position + 1, insert.size());
			}
			if (arglist == arglistx)
			{
				//if (insert.empty()) scenario.mfile << '[' << scenario.sgoto << ']' << L"Error: an/a \"" + name + L"\" with name \"" + names[0] + L"\" couldn't be loaded (last argument empty)" << std::endl/*L*/;
				if (!insert.empty())
				{
					if (state == 1) names[namelist] = insert.substr(0, insert.size());
					else//{
						//if (!scenario.stoicheck(insert.substr(0, insert.size()), arguments[arglist - namelist])) scenario.mfile << L"[Stat]Error: An/a " + name + L" with name " + names[0] + L" failed its stoicheck on argument " << arglist - namelist;
						scenario.stoicheck(insert.substr(0, insert.size()), arguments[arglist - namelist]);
					//}
					insert.clear();
					//if ((state == 1 || state == 2) && arguments[1] == arguments[2]) scenario.mfile << '[' << scenario.sgoto << ']' << L"Error: an/a \"" + name + L"\" with name \"" + names[0] + L"\" has same minimum value as maximum value - it hasn't any purpose(to hold values use Int)" << std::endl/*L*/;
					//else if ((state == 1 || state == 2) && arguments[1] < arguments[2]) scenario.mfile << '[' << scenario.sgoto << ']' << L"Error: an/a \"" + name + L"\" with name \"" + names[0] + L"\" has higher minimum value than maximum value" << std::endl/*L*/;
					//if () {
						if (state == 1) scenario.io_stats.push_back(IntStatOpposite(names[0], arguments[0], arguments[1], arguments[2], arguments[3], arguments[4], arguments[5], names[1]));
						else if (state == 2) scenario.i_stats.push_back(IntStat(names[0], arguments[0], arguments[1], arguments[2], arguments[3], arguments[4]));
						else if (state == 3) scenario.s_stats.push_back(StringStat(names[0], names[1], arguments[0], arguments[1], arguments[2]));
						else if (state == 4) scenario.Ints.push_back(Int(names[0], arguments[0], arguments[1], arguments[2]));
						//scenario.mfile << '[' << scenario.sgoto << ']' << L"Could load an/a \"" + name + L"\" with name \"" + names[0] << '\"' << std::endl/*L*/;
					//}
				}
			}
			//else if (arglist == 1) scenario.mfile << '[' << scenario.sgoto << ']' << L"Error: could not load(missing arguments or stoicheck failure) an/a \"" + name + L"\" with name\"" + names[0] << '\"' << std::endl/*L*/;
			//else scenario.mfile << '[' << scenario.sgoto << ']' << L"Error: could not load(missing arguments or stoicheck failure) an/a \"" + name + L"\" with missing name" << std::endl/*L*/;
		}
		scenario.Parse();
		Show_stats();
		scenario.choicesel = -1;
	}
	else //throw std::runtime_error('[' + scenario.sgoto + ']'+ "FATAL Error: Couldn't open save [while loading](unaccessible file or invalid path)");
	{
		std::wofstream save(L"bin/Saves/" + profiles[selectionp].getString().toWideString() + L"_" + stories[selections].getString().toWideString() + L".txt");
		goto begin;
	}
}

sf::Image Cmain::IOStatspecial(int w, int h, int value, int min, int max, int threshold) //outdated
{
	sf::Image img;
	img.create(w, h, sf::Color(static_cast<sf::Uint8>(255), static_cast<sf::Uint8>(255), static_cast<sf::Uint8>(255), static_cast<sf::Uint8>(0)));
	float rxs = w / 254.f;
	float bxs = w / 254.f;
	//the number of certain pixels
	int valuepos = w * round(abs(value) / (abs(min) + abs(max)));
	//current value
	float xms = rxs;
	//manages the number of needed pixels to create image
	int x = 0;
	if (rxs < 1)
	{
		for (int r = 127; r != 0 && x < w; ++x) 
		{
			while (xms < 1)
			{
				xms += rxs;
				if (r != 0) r--;
			}
			img.setPixel(x, 0, sf::Color(static_cast<sf::Uint8>(254 - (127 - r)), static_cast<sf::Uint8>(127 - r), static_cast<sf::Uint8>(127 - r)));
			xms--;
			if (r != 0) r--;
			xms += rxs;
		}
	}
	else
	{
		for (int r = 127; r != 0 && x < w; ++x)
		{
			while (xms > 2)
			{
				img.setPixel(x, 0, sf::Color(static_cast<sf::Uint8>(254 - (127 - r)), static_cast<sf::Uint8>(127 - r), static_cast<sf::Uint8>(127 - r)));
				xms--;
			}
			img.setPixel(x, 0, sf::Color(static_cast<sf::Uint8>(254 - (127 - r)), static_cast<sf::Uint8>(127 - r), static_cast<sf::Uint8>(127 - r)));
			r--;
			xms--;
			xms += rxs;
		}
	}
	xms = bxs;
	if (bxs < 1)
	{
		for (int b = 127; b != 254 && x < w; ++x)
		{
			while (xms < 1)
			{
				xms += bxs;
				if (b != 254) b++;
			}
			img.setPixel(x, 0, sf::Color(static_cast<sf::Uint8>(254 - b), static_cast<sf::Uint8>(254 - b), static_cast<sf::Uint8>(127 + (b - 127))));
			xms--;
			if (b != 254) b++;
			xms += bxs;
		}
	}
	else
	{
		for (int b = 127; b != 254 && x < w; ++x)
		{
			while (xms > 2)
			{
				img.setPixel(x, 0, sf::Color(static_cast<sf::Uint8>(254 - b), static_cast<sf::Uint8>(254 - b), static_cast<sf::Uint8>(127 + (b - 127))));
				xms--;
			}
			img.setPixel(x, 0, sf::Color(static_cast<sf::Uint8>(254 - b), static_cast<sf::Uint8>(254 - b), static_cast<sf::Uint8>(127 + (b - 127))));
			b++;
			xms--;
			xms += bxs;
		}
	}

	for (int x = 0; x < w; ++x)
	{
		for (int y = 1; y < h; ++y)
		{
			img.setPixel(x, y, img.getPixel(x, 0));
		}
	}
	//copying the pattern

	//rame
	return img; //w razie lagów zastosowaæ skalowanie[mo¿e siê zakoñczyæ wiêkszym zu¿yciem pamiêci(?)] = in case of lags use setScale() [might use more memory(?)]
}

sf::Image Cmain::IntSpecial(int w, int h, int value, int min, int max)
{
	sf::Image img;
	img.create(w, h);
	//the number of certain pixels
	int valuepos = w * static_cast<float>(abs(value)) / (abs(min) + abs(max));
	//manages the number of needed pixels to create image
	unsigned int x = 0;
	while (x < valuepos)
	{
		for (unsigned int y = 0; y < h; ++y)
		{
			img.setPixel(x, y, statgaincolor);
		}
		++x;
	}
	while (x < w)
	{
		for (unsigned int y = 0; y < h; ++y)
		{
			img.setPixel(x, y, statlosscolor);
		}
		++x;
	}
	//copying the pattern

	//rame
	return img; //w razie lagów zastosowaæ skalowanie[mo¿e siê zakoñczyæ wiêkszym zu¿yciem pamiêci(?)] = in case of lags use setScale() [might use more memory(?)]
}


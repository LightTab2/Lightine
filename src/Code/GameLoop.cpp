/*
@Author: LightTab2
The MIT License(MIT)

Copyright(c) 2016 LightTab2 azorro12@gmail.com
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and / or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "Cmain.h"

inline const bool Cmain::Contains(const sf::FloatRect &box)
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
				button_2_text.setFillColor(menudangerselectcolor);
				button_3_text.setFillColor(menunodangercolor);
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
				button_2_text.setFillColor(menudangercolor);
				button_3_text.setFillColor(menunodangerselectcolor);
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
				button_2_text.setFillColor(menudangercolor);
				button_3_text.setFillColor(menunodangercolor);
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
				button_2_text.setFillColor(menudangerclickcolor);
				button_3_text.setFillColor(menunodangercolor);
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
				button_2_text.setFillColor(menudangercolor);
				button_3_text.setFillColor(menunodangerclickcolor);
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
				button_2_text.setFillColor(menudangercolor);
				button_3_text.setFillColor(menunodangercolor);
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
	std::ofstream sfile("../../bin/Stories.txt");
	for (size_t s = 0U; s != profiles.size(); ++s)
	{
		remove(std::string("../../bin/Saves/" + profiles[s].getString().toAnsiString() + "_" + stories[selections].getString().toAnsiString() + ".txt").c_str());
	}
	stories.erase(stories.begin() + selections);
	arroweds -= 1;
	if (arroweds < 0) arroweds = 0;
	arroweds_margin -= 1;
	if (arroweds_margin < 0) arroweds_margin = 0;
	selections -= 1;
	if (selections < 0) selections = 0;
	for (size_t i = 0U; i != stories.size(); ++i)
	{
		sfile << stories[i].getString().toAnsiString() << std::endl;
	}
	scheck = true;
	k_delete = false;
	if (profiles.empty()) scenario.pempty = true;
	else if (stories.empty()) { scenario.pempty = false; scenario.sempty = true; }
	if (!scenario.sempty && !scenario.pempty) scenario.savefile = L"../../bin/Saves/" + profiles[selectionp].getString().toWideString() + L"_" + stories[selections].getString().toWideString() + L".txt";
	else scenario.pempty = scenario.sempty = false;
	scenario.path = "../../bin/Scripts/" + stories[selections].getString() + ".txt";
	LoadSave();
}

void Cmain::DeleteProfile()
{
	std::ofstream pfile("../../bin/Profiles.txt");
	for (size_t s = 0U; s != stories.size(); ++s)
	{
		remove(std::string("../../bin/Saves/" + profiles[selectionp].getString().toAnsiString() + "_" + stories[s].getString().toAnsiString() + ".txt").c_str());
	}
	profiles.erase(profiles.begin() + selectionp);
	arrowedp -= 1;
	if (arrowedp < 0) arrowedp = 0;
	arrowedp_margin -= 1;
	selectionp -= 1;
	if (selectionp < 0) selectionp = 0;
	if (arrowedp_margin < 0) arrowedp_margin = 0;
	for (size_t i = 0U; i != profiles.size(); ++i)
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

void Cmain::LoadSave()
{
	scenario.i_stats.clear();
	scenario.io_stats.clear();
	scenario.s_stats.clear();
	scenario.Ints.clear();
	if (selectionp >= static_cast<int>(profiles.size())) return;
	else if (selections >= static_cast<int>(stories.size())) return;
	{
		std::wfstream file(scenario.path);
		std::wstring db;
		std::getline(file, db);
		if (db[0] == 0xFEFF) db.erase(0U, 1U);
		else if (db[0] == 0xef && db[1] == 0xbb && db[2] == 0xbf) db.erase(0U, 3U);
		if (db == L"#debug") {
 			scenario.Parse();
			scenario.choicesel = -1;
			return;
		}
	}
	LoadStatics();
	std::wfstream save(L"../../bin/Saves/" + profiles[selectionp].getString().toWideString() + L"_" + stories[selections].getString().toWideString() + L".txt");
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
			if (insert.empty()) break; //throw "[LoadingSave] Error: the save contains an empty line or is empty [" + scenario.sgoto + ']';
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
					if(!scenario.stoicheck(insert, scenario.sgoto)) warn(L"[LoadingSave]FATAL stoicheck failure(\"goto\" variable)");
					scenario.scgoto = scenario.cgoto = scenario.sgoto;
					break;
				case 1:
					scenario.stoicheck(insert, scenario.dgoto);
					break;
				case 2:
					int variable = 0;
					if (!scenario.stoicheck(insert, variable)) warn(L"[LoadingSave]FATAL stoicheck failure(\"loadtextonly\" variable)");
					scenario.loadtextonly = static_cast<bool>(variable);
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
				size_t s_position;
				if (insert.empty() || (s_position = insert.find(L',')) == std::wstring::npos)
					warn(L"[LoadingSave]Error: an/a " + name + L" with name \"" + (names[0].empty() ? L"unknown" : names[0]) +
						L"\" couldn't be loaded (missing argument or an empty argument)");
				switch (arglist)
				{
				case 0:
					names[0] = insert.substr(0U, s_position);
					scenario.chName(names[0]);
					++namelist;
					break;
				case 1:
					if (state == 3) {
						names[1] = insert.substr(0U, s_position);
						++namelist;
					}
					else if (!scenario.stoicheck(insert.substr(0U, s_position), arguments[0])) warn(L"[LoadingSave, Stat]Error: An/a " + name + L" failed its stoicheck on argument 1");
					break;
				default:
					if (!scenario.stoicheck(insert.substr(0U, s_position), arguments[arglist - 1])) warn(L"[LoadingSave, Stat]Error: An/a " + name + L" with name \"" + names[0] + L"\" failed its stoicheck on argument " + std::to_wstring(arglist));
					break;
				}
				insert.erase(0U, s_position + 1U);
			}
			if (arglist == arglistx)
			{
				if (!insert.empty())
				{
					if (state == 1) names[namelist] = insert.substr(0U, insert.size());
					else if (!scenario.stoicheck(insert.substr(0U, insert.size()), arguments[arglist - namelist])) warn(L"[Stat]Error: An/a " + name + L" with name \"" + names[0] + L"\" failed its stoicheck on argument " + std::to_wstring(arglist - namelist));
					insert.clear();
					if (state == 1) scenario.io_stats.push_back(IntStatOpposite(names[0], arguments[0], arguments[1], arguments[2], arguments[3], arguments[4], arguments[5], names[1]));
					else if (state == 2) scenario.i_stats.push_back(IntStat(names[0], arguments[0], arguments[1], arguments[2], arguments[3], arguments[4]));
					else if (state == 3) scenario.s_stats.push_back(StringStat(names[0], names[1], arguments[0], arguments[1], arguments[2]));
					else if (state == 4) scenario.Ints.push_back(Int(names[0], arguments[0], arguments[1], arguments[2]));
				}
				else warn(L"[LoadingSave] Error: an/a " + name + L" with name \"" + names[0] + L"\" couldn't be loaded (last argument empty)");
			}
			else if (arglist == 1) warn(L"Error: could not load(missing arguments or stoicheck failure) an/a " + name + L" with name\"" + names[0] + L'\"');
			else warn(L"Error: could not load(missing arguments or stoicheck failure) an/a " + name + L" with missing name");
		}
		scenario.Parse();
		scenario.choicesel = -1;
	}
	else
	{
		static bool attempt = false;
		if (attempt) throw w_err(L"Could not create save file \"../../bin/Saves/" + profiles[selectionp].getString().toWideString() 
			+ L'_' + stories[selections].getString().toWideString() + L".txt\"");
		std::wofstream save(L"../../bin/Saves/" + profiles[selectionp].getString().toWideString() + L"_" + stories[selections].getString().toWideString() + L".txt");
		attempt = true;
		LoadSave();
	}
}

void Cmain::LoadStatics()
{
	std::wfstream save(ScenarioParser::apath + L"\\Stc.txt");
	if (save)
	{
		std::wstring insert;
		std::getline(save, insert);
		const std::locale empty_locales = std::locale::empty();
		const std::codecvt_utf8<wchar_t>* converters = new std::codecvt_utf8<wchar_t>;
		const std::locale utf8_locales = std::locale(empty_locales, converters);
		save.imbue(utf8_locales);
		if (insert[0U] == 0xFEFF) //not sure if necessary
			insert.erase(0U, 1U);
		else if (insert[0U] == 0xef && insert[1U] == 0xbb && insert[2U] == 0xbf)
			insert.erase(0U, 3U);
		while (insert[0U] != L'}')
		{
			if (insert.empty()) break;
			std::wstring name = insert.substr(0U, insert.find(L','));
			int value;
			if (scenario.stoicheck(insert.substr(insert.find(L',') + 1U), value))
			{
				scenario.stc_i.push_back(StcIntStat(name, value));
			}
			else throw w_err(L"Error loading Stc.txt, this should not happend unless you were editing files. Delete Stc.txt");
			std::getline(save, insert);
		}
		while (std::getline(save, insert))	
		{
			std::wstring name = insert.substr(0U, insert.find(L',')), value = insert.substr(insert.find(L',') + 1U);
			warn(value);
			scenario.stc_s.push_back(StcStringStat(name, value));
			if (insert.empty()) break;
		}
	}
}
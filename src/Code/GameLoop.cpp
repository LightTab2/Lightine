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
	std::wofstream sfile(L"../../bin/Stories.txt");
 	sfile.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	for (size_t s = 0U; s != profiles.size(); ++s)
	{
		std::wstring str = L"../../bin/Saves/" + profiles[s].getString().toWideString() + L'_' + stories[selections].getString().toWideString() + L".txt";
		_wremove(str.c_str());
		//str = scenario.apath + L"\\" + stories[selections].getString().toWideString() + L'_' + profiles[s].getString().toWideString() + L"_Stc.txt";
		//_wremove(str.c_str());
	}
	//const std::wstring str = std::wstring(scenario.apath + L"\\" + stories[selections].getString().toWideString() + L"_Stc.txt");
	//_wremove(str.c_str());
	stories.erase(stories.begin() + selections);
	arroweds -= 1;
	if (arroweds < 0) arroweds = 0;
	arroweds_margin -= 1;
	if (arroweds_margin < 0) arroweds_margin = 0;
	selections -= 1;
	if (selections < 0) selections = 0;
	for (size_t i = 0U; i != stories.size(); ++i)
	{
		sfile << stories[i].getString().toWideString() << std::endl;
	}
	scheck = true;
	k_delete = false;
	LoadSave();
}

void Cmain::DeleteProfile()
{
	std::wofstream pfile("../../bin/Profiles.txt");
	pfile.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	for (size_t s = 0U; s != stories.size(); ++s)
	{
		std::wstring str = L"../../bin/Saves/" + profiles[selectionp].getString().toWideString() + L"_" + stories[s].getString().toWideString() + L".txt";
		_wremove(str.c_str());
		//str = scenario.apath + L"\\" + stories[s].getString().toWideString() + L'_' + profiles[selectionp].getString().toWideString() + L"_Stc.txt";
		//_wremove(str.c_str());
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
		pfile << profiles[i].getString().toWideString() << std::endl;
	}
	pcheck = true;
	k_delete = false;
	LoadSave();
}

void Cmain::LoadSave() //There's bunch of "scenario.savefile =", maybe it can be optimized even further, deleting pempty and sempty in process
{
	SaveToFile();
	//if (profiles.empty()) scenario.pempty = true;
	//else scenario.pempty = false;
	//if (stories.empty()) scenario.sempty = true;
	//else scenario.sempty = false;
	if (!stories.empty()) scenario.path = "../../bin/Scripts/" + stories[selections].getString() + ".txt";
	if (!stories.empty() && !profiles.empty()) {
		scenario.savefile = L"../../bin/Saves/" + profiles[selectionp].getString().toWideString() + L"_" + stories[selections].getString().toWideString() + L".txt";
		if (!scenario.Parse(true)) DeleteStory();
		sviewchange(lsetPos = static_cast<float>(smaxup));
	}
	else
		Reset();
}

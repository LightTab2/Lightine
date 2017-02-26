/*
@Author: LightTab2
The MIT License(MIT)

Copyright(c) 2016 LightTab2 azorro12@gmail.com
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and / or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#pragma once
#include "Stat.h"
#include "CustImg.h"
#include "Choice.h"
#include <fstream>
#include "shlobj.h"
class ScenarioParser													//Parses scenario file, inserting data into program
{
public:																	//Read from goto to end(next or end command)
	void Parse();
																		//Prevents crash and does std::stoi; if failure: return def		
	const bool stoicheck(std::wstring &checked, int &number, const int def = 0);
	const bool stoicheck(std::wstring &checked, unsigned int &number, const int def = 0);
	const int stoicheck(std::string &checked, const int def = 0);

	bool chName(const std::wstring &name, bool fatal = false);			//Checks if there's already an object with the same name

	bool drawnext = false;												//True - next is rendered
	bool debug = false;													//Makes it easier to write stories
	bool typing = false;
	int owd = 0;														//The right margin
	//int th = 0;														//Height of one text from additional
	int the = 0;														//Current down margin
	int she = 0;														//Like 'the' but for gamestate '-1'
	float w2;															//Made to improve performance - calculates commonly used statement
	int h;																//Copy of h in Cmain, thought about pointer but it is read only, changes in Cmain::sSaveOptions
	int st = 0;															//How many times you need to scroll to get from top to down
	int w;																//Copy of w in Cmain, thought about pointer but it is read only, changes in Cmain::sSaveOptions
	int sgoto = 0;														//Parse() starts of reading at this line
	int cgoto = 0;														//Copy of sgoto, used when saving the game
	int dgoto = 0;														//Stops parsing when sgoto hits dgoto's value
	int scgoto = 0;
	int	choicesel = -1;													//Currently selected Choice
	bool slideratv = false;												//Is slider active(rendered and able to be pushed)
	bool pempty = false;												//If profiles are empty
	bool sempty = false;												//If stories are empty
	bool loadtextonly = false;											//Reload text, but do not execute commands
	bool choiceneed = false;											//Logging file
	bool ssreload = true;
	sf::Text text;														//Vector of text that are displayed as current story
	std::vector<Choice> choice;											//List of choice that are avaiable
	std::vector<IntStat> i_stats;										//IntStats' vector
	std::vector<IntStatOpposite> io_stats;								//IntStatOpposities' vector
	std::vector<StringStat> s_stats;									//StringStats' vector
	std::vector<Int> Ints;												//Ints' vector
	std::vector<StcStringStat> stc_s;									//Stc StringStats' vector
	std::vector<StcIntStat> stc_i;										//Stc IntStatz' vector
	sf::Texture next_t;													//Texture of next
	sf::Sprite next;													//"Next" button
	std::wstring savefile;												
	sf::Color *textchoiceunavaiblecolor;				
	std::wstring path;													//Path to current file
	sf::Color statcolor, statgaincolor, statlosscolor, statoppositecolor;
	static std::wstring apath;											//For static stats, path to %APPDATA%
	std::wstring *type;													//So you can enter some text and make StringStat out of it
private:
	void ParseMainBody();
	bool formattype = false;											//If true SplitText() occurs every line
																		//Sets the position where reading beggins
	void GotoLine(const int num);
																		//Finds a statistic and returns its value
	const bool statfind(const std::wstring &name,int &val);
	const bool statfind(const std::wstring &name, std::wstring &val);
																		//Executes various commands return;
	sf::ConvexShape rrect;
	void ExecuteCommand(std::wstring &insrtttt);
																		//Splits text if it's 2 long
	void SplitText(const bool w, std::wstring &insrt);
																		//tinsr and text becames one
	void MergeText();
																		//Checks if in the line is a comment
	const bool CommentCheck(std::wstring &insr);
																		//Very thingy thing that actually does some things - used to create Stats
	void Thingy(const int argz, std::wstring &insrtttt);
																		//Rounded rectangle around choice's text
	void RoundRect();
																		//A long command for creating choices
	void CreateChoice();
																		//Saves the game
	void Save();
																		//Part of Save()
	void SaveStcs();	
																		//Gets current locale to read widestrings
	const std::locale utf8_locale = std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>); 
																		//Shows your all glorious fails and almighty weaknesses of the hero(victories and strenghts are shown too, but who cares?)
	void Show_stats();

																		//Creates the image of IntStatOpposite (I'll allow to customize colors soon here)
	const sf::Image IOStatspecial(const int w, const int h, int value, int min, int max, int threshold);
																		//Creates the image of IntStat(here too)
	const sf::Image IntSpecial(const int w, const int h, int value, int min, int max);
															
	inline void IfCheck(std::wstring &insr);
	inline void getline(std::wstring &preinsr);
	//inline void TabFind(std::wstring &preinsr);
	sf::Font sfont;														//Font of the text
	std::wstring insr;													//Contains text that will be splitted into tinsr
	std::wstring tinsr;													//Splitted insr that will be displayed
	std::wfstream in;													//File from which parser gets data
};
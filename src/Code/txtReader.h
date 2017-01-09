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
#include <codecvt>
#include <fstream>
#include "Windows.h"

class ScenarioParser													//Parses scenario file, inserting data into program
{
public:
																		//The constructor
	ScenarioParser();
																		//Read from goto to end(next or end command)
	void Parse();
																		//Prevents crash and does std::stoi; if failure: return def maybe just catch exception?
	int stoicheck(std::string &checked, int def = 0);
																		//Tells if std::stoi on &number was successfull
	bool stoicheck(std::wstring &checked, int &number, int def = 0);

	bool chName(std::wstring name);										//Checks if there's already an object with the same name

	bool drawnext = false;												//True - next is rendered

	int owd = 0;														//The right margin
	int th = 0;															//Height of one text from additional
	int the = 0;														//Current down margin
	float w1;															//Made to improve performance - calculates commonly used statement
	float w2;															//Made to improve performance - calculates commonly used statement
	int sh;																//Copy of h in Cmain, thought about pointer but it is read only, changes in Cmain::sSaveOptions
	int st = 0;															//How many times you need to scroll to get from top to down
	int sw;																//Copy of w in Cmain, thought about pointer but it is read only, changes in Cmain::sSaveOptions
	int sgoto = 0;														//Parse() starts of reading at this line
	int cgoto = 0;														//Copy of sgoto, used when saving the game
	int dgoto = 0;
	int	choicesel = -1;													//Currently selected Choice
	bool slideratv = false;												//Is slider active(rendered and able to be pushed)
	bool pempty = false;												//If profiles are empty
	bool sempty = false;												//If stories are empty
	bool loadtextonly = false;											//Reload text, but do not execute commands
	bool choiceneed = false;
	//std::wofstream //mfile;											//Logging file
	std::vector <sf::Text> additional;									//Vector of text that are displayed as current story
	std::vector<Choice> choice;											//List of choice that are avaiable
	std::vector<IntStat> i_stats;										//IntStats' vector
	std::vector<IntStatOpposite> io_stats;								//IntStatOpposities' vector
	std::vector<StringStat> s_stats;									//StringStats' vector
	std::vector<Int> Ints;												//Ints' vector
	sf::Texture next_t;													//Texture of next
	sf::Sprite next;													//"Next" button
	sf::Text tekst;														//Builds sf::Texts in additional
	std::unique_ptr<sf::Color> textcolor;								//Color used to create new additionals
	std::wstring savefile;
	std::unique_ptr<sf::Color> textchoiceunavaiblecolor;
	std::wstring path;													//Path to current file
private:
	bool bold = false;													//Tells if next sf::Texts should be in bold font
	bool italic = false;												//Tells if next sf::Texts should be in italic font
	bool formattype = false;
																		//Sets the position where reading beggins
	void GotoLine(int num);
																		//Finds a statistic and returns its value
	bool statfind(std::wstring &name, int &val);
																		//Makes text bold, soon italic too
	void formaT(std::vector<sf::Text>& vec, int wu, std::vector<sf::Vector2i>& b);
																		//Executes various commands
	void ExecuteCommand(std::wstring &insrtttt, int &sh, int &sw);
																		//Splits text if it's 2 long
	void SplitText(bool w, std::wstring &insrt);
																		//Splits text if it's 2 long(choice)
	//void ChSplitText();
																		//Checks if in the line is a comment
	bool CommentCheck(std::wstring &insr);
																		//Very thingy thing that actually does some things - used to create Stats
	void Thingy(int argz, std::wstring insrtttt);
																		//Rounded rectangle around choice's text
	void RoundRect();
																		//A long command for creating choices
	void CreateChoice(std::wstring &insrtttt);
																		//Saves the game
	void Save();

	const std::locale utf8_locale = std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>);	//Gets current locale to read widestrings

	sf::Font sfont;														//Font of the text
	std::wstring insr;													//Buffer that holds line currently read
	std::wfstream in;													//File from which parser gets data
};
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
#include "TypeBox.h"
class ScenarioParser													//Parses scenario file, inserting data into program
{
public:
	bool pempty = false;												//If profiles are empty
	bool sempty = false;												//If stories are empty
private:
	friend class Cmain;
																		//Read from goto to end(next or end command)
	const bool Parse(const bool loadgame);	
																		//Prevents crash and does std::stoi; if failure: ReturnInt is set to Default and returns false
	const bool stoiCheck(const std::wstring& NumberInText,
	                     int &ReturnInt,
	                     int Default = 0);										
																		//Prevents crash and does std::stoi; if failure: ReturnUInt is set to Default and returns false
	const bool stoiCheck(
		const std::wstring& checked,
		unsigned& number, const int def = 0);
																		//Prevents crash and returns std::stoi; if failure: returns Default
	const int stoiCheck(
		const std::string& checked, const int def = 0); 
																		//Checks if there's already an object with the same name
	bool checkName(const std::wstring &NameToFind, 
		bool ThrowError = false);

	bool DrawNext = false;												//True - next is rendered
	bool Debug = false;													//Makes it easier to write stories			
	bool PlayerTurn = false;											//True when player need to make a choice or move (type, click next etc.)
	bool allowdebugging = true;											//Controls if file already has been debugged
	int rmargin = 0;													//The right margin
	//int th = 0;														//Height of one text from additional
	int dmargin = 0;													//Current down margin
	int sdmargin = 0;													//Like 'dmargin' but for gamestate '-1', s stands for Stats'
	float w2;															//Made to improve performance - calculates commonly used statement //choice
	int *h;																//Copy of h in Cmain, it needs to change change in Cmain::sSaveOptions
	int scrolltimes = 0;												//How many times you need to scroll to get from top to down
	int *w;																//Copy of w in Cmain, it needs to change in Cmain::sSaveOptions
	int sgoto = 0;														//Parse starts of reading at this line
	int cgoto = 0;														//Copy of sgoto, used when saving the game
	int dgoto = 0;														//Stops parsing when sgoto hits dgoto's value	
	int	choicesel = -1;													//Currently selected Choice
	int	typesel = -1;													//Which TypeBox is selected, it also indicates if player is focused on typing anything to any typebox
	int ttignore = 0;													//Number of Tabs to being ignored
	bool slideratv = false;												//Is slider active(rendered and able to be pushed)
	bool loadtextonly = false;											//Read only text, do not execute any commands if true
	bool choiceneed = false;											//So you can't click Next when no choice is selected if it is true
	bool ssreload = true;												//Tells if Show_Stats needs to be called(Stats images reloaded)
	bool formattype = false;											//If true SplitText() occurs every line
	float Tsize;														//Maximum height of a single line in TypeBox
	sf::Text text;														//Vector of text that are displayed as current story
	std::vector<Choice> choice;											//List of choice that are avaiable
	std::vector<TypeBox> typeboxes;										//Boxes where input can occur
	std::multimap<unsigned int, IntStat> i_stats;						//IntStats' multimap
	std::multimap<unsigned int, IntStatOpposite> io_stats;				//IntStatOpposities' multimap
	std::multimap<unsigned int, StringStat> s_stats;					//StringStats' multimap
	std::multimap<unsigned int, Int> Ints;								//Ints' multimap
	std::vector<StcString> stc_s, dstc_s;								//Stc StringStats' multimap, d version stands for debugging
	std::vector<StcInt> stc_i, dstc_i;									//Stc IntStatz' vector, d version stands for debugging
	std::vector<sf::Text> customtxt;									//Custom formated text user can create
	std::vector<sf::Text> gaintext;										//Tells player if he had gained anything; can be turned on/off
	sf::Texture next_t;													//Texture of next
	sf::Sprite next;													//"Next" button
	sf::FloatRect Bnext;												//Boundaries of scenario.next
	std::wstring savefile;												//Path to current save file
	sf::Color *textchoiceunavailablecolor;								//Pointer to cmain's choiceunavailablecolor
	std::wstring path;													//Path to current story file
	sf::Color statcolor, statgaincolor, statlosscolor, statoppositecolor,
		typeboxcolor, typeboxfillcolor, typeboxfillselcolor, typeboxtextcolor, typeboxunavailablefillcolor, typeboxunavailablefillselcolor,
		gaintextcolor;													//Colors needed by ScenarioParser
	static std::wstring apath;											//For static stats, path to %APPDATA%
	//std::wstring *type;												//So you can enter some text and make StringStat out of it
	sf::ConvexShape rrect;
	const std::locale utf8_locale = std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>);	//Gets current locale to read widestrings
																		//Basically core of Parse, where loop is called
	void ParseMainBody();
																		//Heart of parsing the text
	void TextProcess(std::wstring &TextToProcess, std::wstring &AddReturnTo);
																		//Sets the position where reading beggins
	void GotoLine(const int Line);
																		//Executes various commands return;
	void ExecuteCommand(std::wstring &Command);
	sf::Text& Split(sf::Text& tekst, bool newline, float margin);										//Function extracted from SplitText, because it is usefull in f.e. gaintext formatting or Stat's text cutting. As name says it splits text, so it can fit on screen (position + size is lesser than rmagin)
	//Splits text if it's too long; State = true: prasing for choice, otherwise for main text
	void SplitText(const bool State, std::wstring &AddReturnTo);
																		//tinsr and text becames one
	void MergeText();
																		//Checks if in the line is a comment
	const bool CommentCheck(std::wstring &TextToBeChecked);
	void FindRange(int start = 1);
	//Very thingy thing that actually does some things - used to create Stats; arg - informs which Stat is about to be created
	void Thingy(const int arg, std::wstring &Command);
																		//Rounded rectangle around choice's text
	void RoundRect();
																		//A long command for creating choices
	void CreateChoice();
																		//Saves the game
	void Save();
																		//Part of Save()
	void SaveStcs();	
																		//Shows your all glorious fails and almighty weaknesses of the hero(victories and strenghts are shown too, but who cares?)
	void Show_stats();
																		//Checks if the text isn't just a piled up '\n'									
	static bool NewlineCheck(const std::wstring& TextToCheck);
																		//Creates the image of IntStatOpposite (I'll allow to customize colors soon here)
	const sf::Image IOStatspecial(const int w, const int h, int value, int min, int max, int threshold);
																		//Creates the image of IntStat(here too)
	const sf::Image IntSpecial(const int w, const int h, int value, int min, int max);
																		//Protected find - throws error if it doesn't find any occurencers of given character
	size_t Pfind(const std::wstring& FindHere, wchar_t character);
																		//Ingame conditional, very useful :)
	bool IfCheck(std::wstring &Chache);
																		//Gets single line from story file
	void getline(std::wstring &preinsr);
																		//Creates a single typebox
	void CreateTypeBox();
																		//Creates new gaintext and adds to a container
	void CreateGainText();
																		//Following finds certain Stats
IntStat* FindIStat(const std::wstring &name);
	bool FindIStat(const std::wstring &name, const IntStat *&rt);
IntStatOpposite* FindIStatO(const std::wstring &name);
	bool FindIStatO(const std::wstring &name, const IntStatOpposite *&rt);
Int *FindInt(const std::wstring &name);
	bool FindInt(const std::wstring &name, const Int *&rt);
StcInt* FindStcI(const std::wstring &name);
	bool FindStcI(const std::wstring &name, const StcInt *&rt);
StringStat* FindSStat(const std::wstring &name);
	bool FindSStat(const std::wstring &name, const StringStat *&rt);
StcString* FindStcS(const std::wstring &name);
	bool FindStcS(const std::wstring &name, const StcString *&rt);
	bool FindString(const std::wstring &name, std::wstring &rt);
	bool FindInt(const std::wstring &name, int &rt);
																		//Finds '#' and eliminates all tabs that are obstacles to it
	bool ElTabs(std::wstring &insr);
																		//Ignores ttignore(number of tabs to ignore) tabs
	void IgnoreTabs(std::wstring &insr);
																		//Initializes all waypionts for given file;
	void ScanForWaypoints(); 
																		//Checks every command if it is correct
	void ScanForErrors();
																		//Loads save? dunno
	void LoadSave();
																		//Probably part of LoadSave()
	void LoadStatics();
	void ValueCheck(std::wstring& insr);
	//Part of IfCheck();
	void elsecheck(bool IFb);
	//inline void TabFind(std::wstring &preinsr);
	std::wstring insr;													//Contains text that will be splitted into tinsr
	std::wstring tinsr;													//Splitted insr that will be displayed
	std::wifstream in;													//File from which parser gets data
	std::map<std::wstring, int> waypoints;								//Waypoints for #goto
	std::wstring fpath;													//Simplest imo way to make #file work is making copies of certain variables to save things proper
	int fcgoto;															//Simplest imo way to make #file work is making copies of certain variables to save things proper
};
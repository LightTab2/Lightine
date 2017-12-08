/*
@Author: LightTab2
The MIT License(MIT)

Copyright(c) 2016 LightTab2 azorro12@gmail.com
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and / or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#pragma once
#include "txtReader.h"
#include <thread>
#include <chrono>
//Hello everyone, I want to say that my English isn't so good and any correction would be very kind from you =)
class Cmain
{
	public:
		bool quit = false;															//True - program closes	

																					//The constructor
		Cmain();
																					//"Tick" is every call of this function, essential for program to work
		void GameLoop();
																					//"Lightine appears before"
		void Intro();

		ScenarioParser scenario;													//Parses stories
		std::vector<sf::Text> profiles;												//Profiles that can be selected
		std::vector<sf::Text> stories; 												//Stories that can be selected
	private:	
		bool fullscreen = true;														//Enables fullscreen?
		bool cfullscreen = false;													//Like cmusic, used in SaveOptions(). Maybe use pointers here? As far as I know they're 4 bytes, so there's no reason to that.
		bool sound = false;															//Turns on sounds... or off
		bool music = false;															//Music on/off
		bool cmusic = false;														//Music's value copied when constructor of cmain was called
		bool csound = false;														//Like cmusic, used in SaveOptions()
		bool stigger = false;														//If true - slider moves along with mouse
		bool resbutton1_focus = false;												//True-you can enter width number (fullone)
		bool resbutton2_focus = false;												//True-you can enter height number (fulltwo)
		bool clicked = false;														//Used in function that changes buttons' color when you hover cursor over them or click at 'em
		bool scheck = true;															//Manages the look of stories menu(gamestate 7)
		bool pcheck = true;															//Manages the look of profiles menu(gamestate 6)
		bool k_delete = false;														//If clicked and in gamestate 6 or 7, a text(ctext) appears with button 2 and 3 ("No", "Yes")
		bool alt = false;															//Used in combination alt + f4
		bool prov = false;															//So you click Escape, but it's not "onRelease". Clicks would repeat if not this
		bool gwhich = false;														//When you're in gamestate 5 and wondering if you went from gmst 6 or 7
		bool enternew = false;														//Sub-gamestate in gamestates 6 and 7
		bool enternewerror = false;													//Name conflict, makes error render
		bool visible = false;														//If functions in Fades ended its work
		bool arrowed_dn = false;													//Means selection is max down
		bool arrowed_up = false;													//Means selection is max up
		bool resetsb = false;														//Sub-gamestate in gamestate -1
		bool disrandomnameLOL = true;												//Optimization for instructions based on clicked, name is an easter egg
		bool disbutton = false;														//Optimization for instructions based on clicked, name is an easter egg
		int	fontsize1 = 0;															//Font's size for small resolution
		int	fontsize2 = 0;															//Font's size for medium resolution
		int	fontsize3 = 0;	 														//Font's size for big resolution
		int	arroweds = 0;															//View transform in stories(gmst 7)
		int	arrowedp = 0;															//View transform in profiles(gmst 6)
		int selections = 0;															//Selected (in-use) story
		int selectionp = 0;															//Selected (in-use) profile
		int	arroweds_margin = 0;													//Maximal arroweds
		int	arrowedp_margin = 0;													//Maximal arrowedp
		int	gamestate = 1;															//State of the game. -1-statistics menu 0-main menu 1-game 2-options 3-graphics options 4-audio options 5-save settings 6-profile settings 7-story settings
		unsigned int menucapacity = 0;												//Maximum number of sf::Text(s), that are able to render in profilesmenu
		int	antialias = 0;															//Antialiasing setting
		int	framelimit = 0;															//Maximum fps
		int	smax = 0;																//The number of movement that can be done by slider
		int smaxup = 0;																//Minimum slider's position (up)
		int	smaxdown = 0;															//Maximum slider's position (down)
		int w = 800;																//Width of the window, in pixels
		int	h = 600;																//Height of the window, in pixels
		int	smouseposy = 0;															//Mousepos - smaxup
		float lsetPos = 0;															//Used in (saves current possition)
		float ssetPos = 0;															//lsetPos for gamestate -1
		int numbss = 0;																//The real view change done

		float choicefactor = 0;														//Used in Fades to determine precise alpha of choicefillcolor
		float typeboxfactor = 0, typeboxunavailablefactor = 0, typeboxfactor2 = 0, typeboxunavailablefactor2 = 0;													//Used in Fades to determine precise alpha of scenario.typeboxfillcolor
		float profilesmenufillfactor = 0;											//Used in Fades to determine precise alpha of menuprofilesmenufillcolor

		std::string	fulltwo;														//String that holds height value
		std::string	fullone;														//String that holds width value
		std::string	profilname;														//New object name(profile or story)
		std::string	cfullone;														//Like cmusic, used in SaveOptions()
		std::string	cfulltwo;														//Like cmusic, used in SaveOptions()
		//--Main--//
		sf::Vector2f mousepos;														//Position in the cursor (in window)
		sf::Vector2i pos[18];														//Positions that are used when view is changed(slider moving)
		const sf::Vector2u desktop = sf::Vector2u(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height); //Used when fullscreen
		sf::Event mainevent;														//Checks for input and stuff
		sf::RenderWindow window;													//The magic eye of mighty SFML we can look into and seek wisdom... What would it be? The Window of course! (gotta make 1st letter capital c:)

		sf::Font font;																//Font for the menu text
		sf::Font font2;								 								//Font for the game's text(scenario.additional)

		sf::Sprite Background;														//"Super secret image that has inside very hidden data about safety of our country. Trust me." I think it's background image, but not sure lfmao
		sf::Sprite michaupase³ke³;													//Horizontal bar where show_stats is located, later inventory too
		sf::Sprite sliders;															//Slider used to move the view
		sf::Sprite bars;															//Slider moves within it
		sf::Sprite arrowdn;															//The "down" arrow sprite
		sf::Sprite arrowup;															//The "up" arrow sprite
		sf::Sprite showstats;														//The "Show Stats" image seen in gamestate 1
		sf::Sprite resets;															//When you'll click showstats you'll see it in the same position

		sf::Texture Background_texture,												//JUST SOME TEXTURES
			michaupase³ke³_t,
			slider,
			bar,
			arrowup_t,
			arrowdn_t,
			shwstats_t,
			reset_t;

		sf::Text button_t[3],														//Button used to navigate the game's menu
			&button_1_text = button_t[0],
			&button_2_text = button_t[1],
			&button_3_text = button_t[2];
		sf::Text resbutton1_text;													//Shows current width
		sf::Text resbutton2_text;													//Shows current height
		sf::Text f14_text;															//Informs user that alt + f4 quits the game
		sf::Text help_text;															//"Press delete to remove"
		sf::Text ctext;																//"Are you sure?"
		sf::Text ntext;																//"Enter name:"
		sf::Text newname;															//Name you entered
		sf::Text enternewerror_t;													//"Error: There's already an object with the same name"
		sf::Text endmessage;														//Customizable text placed before choices
		sf::FloatRect button[3],													//Boundaries of a button
			&button_1 = button[0],
			&button_2 = button[1],
			&button_3 = button[2];
		sf::FloatRect resbutton1;													//Boundaries of resbutton1_shape
		sf::FloatRect resbutton2;													//Boundaries of resbutton2_shape
		sf::FloatRect slidersb;														//Boundaries of sliders
		sf::FloatRect shwstats;														//Boundaries of showstats
		sf::FloatRect arrowdn_b;													//Boundaries of arrowdn
		sf::FloatRect arrowup_b;													//Boundaries of arrowup
		sf::FloatRect resets_b;														//Boundaries of resets

		sf::RectangleShape resbutton1_shape;										//The rectangle where you type height number
		sf::RectangleShape resbutton2_shape;										//The rectangle where you type width number
		sf::RectangleShape profilesmenu;											//The rectangle where profiles or stories are stored
		
		sf::Color
			color[35],																//Many, very many colors, so you can adjust your game
			&textcolor = color[0],
			&menucolor = color[1],
			&menuselectcolor = color[2],
			&menuclickcolor = color[3],
			&menuoncolor = color[4],
			&menuonselectcolor = color[5],
			&menuonclickcolor = color[6],
			&menudangercolor = color[7],
			&menudangerselectcolor = color[8],
			&menudangerclickcolor = color[9],
			&menunodangercolor = color[10],
			&menunodangerselectcolor = color[11],
			&menunodangerclickcolor = color[12],
			&menuwidthcolor = color[13],
			&menuwidthoutlinecolor = color[14],
			&menuwidthfillcolor = color[15],
			&menuwidthselfillcolor = color[16],
			&menuwidthffillcolor = color[17],
			&menuheightcolor = color[18],
			&menuheightoutlinecolor = color[19],
			&menuheightfillcolor = color[20],
			&menuheightselfillcolor = color[21],
			&menuheightffillcolor = color[22],
			&menuprofilesmenuoutlinecolor = color[23],
			&menuprofilesmenufillcolor = color[24],
			&menuprofilescolor = color[25],
			&menuprofilesselectcolor = color[26],
			&menustoriescolor = color[27],
			&menustoriesselectcolor = color[28],
			&menuerrorcolor = color[29],
			&textchoicecolor = color[30],
			&textchoiceunavailablecolor = color[31],
			&textchoicefillcolor = color[32],
			&menuhelpcolor = color[33],
			&menuinsertcolor = color[34];
		
		sf::Clock errclock;															//Manages enternewerror_t lifetime

		std::vector<sf::Vector2i> positions;										//Possible positions in profilesmenu

																					//Loads save? dunno
		void LoadSave();
																					//Gets data from bin\Options.ini		
		void LoadOptions();
																					//Main loop	
		void MainEvent();															
																					//Transforms done along with slider's movement
		void sviewchange(float setPos);
																					//Adjusts sprites, texts, images to new resolution
		void sSaveOptions();
																					//Saves game's options
		void SaveOptions();
																					//Creates window; used in sSaveOptions() and constructor
		void createWindow();													
																					//A method, created to improve readablity in SaveOptions()
		void SaveToFile();
																					//Steers the menu look
		void GameMenu();
																					//Things that happen in every GameLoop() (why seperated? To improve transparency of the code, but tho honestly. It's bad as hell anyways)
		void onTick();
																					//Separated from MainEvent()
		void onClick();
																					//Separated from MainEvent()
		void onRelease();
																					//Sets menucapacity, profiles, stories and connected
		void getSaveData();
																					//Prepares gamestate 6 or 7
		void setupMenu();
																					//Creates new profile or story
		void CreateNew();
																					//Deletes a story
		void DeleteStory();
																					//Deletes a profile
		void DeleteProfile();
																					//Sets transparency of certain objects, polishing navigation between gamestates
		void PrepareMenu();
																					//Resets the progress
		void Reset();
																					//Checks if you clicked on shwstats
		void ssb();
																					//Check if mousepos is contained in box	
		const bool Contains(const sf::FloatRect &box);					
																					//The code that doesn't look good, because was made for performance, splitted from PrepareMenu()
		void Manage67();	
																					//The code that doesn't look good, because was made for performance, splitted from PrepareMenu()
		void Manage1();
																					//The code that doesn't look good, because was made for performance, splitted from PrepareMenu()
		void Manageminus1();
																					//The code that doesn't look good, because was made for performance, splitted from PrepareMenu()
		void Draw67();
																					//The code that doesn't look good, because was made for performance, splitted from PrepareMenu()
		void Draw1();
																					//The code that doesn't look good, because was made for performance, splitted from PrepareMenu()
		void Drawminus1();
};
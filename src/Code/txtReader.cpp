/*
@Author: LightTab2
The MIT License(MIT)

Copyright(c) 2016 LightTab2 azorro12@gmail.com
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and / or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "txtReader.h"
#include <type_traits>
constexpr wchar_t* const split = L"`/`"; //Add an option to change it, for user preference
const size_t split_l = std::wcslen(split);
constexpr wchar_t* const comment = L"//"; //Add an option to change it, for user preference
constexpr wchar_t* const empty = L"`"; //Add an option to change it, for user preference

ScenarioParser::ScenarioParser()
{
	//mfile.open("../../bin/Logs/log.txt", std::ios::trunc);
	//mfile.imbue(utf8_locale);
	insr.reserve(2000);
}

void ScenarioParser::GotoLine(int num)
{
	in.seekg(std::ios::beg);
	for (unsigned int i = 0U; num != 0U && i < num - 1U; ++i){
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	cgoto = sgoto = num;
}

void ScenarioParser::Parse()
{
	drawnext = false;	
	bool bold = false;
	bool italic = false;
	additional.clear();
	choice.clear();
	the = sh / 12;
	slideratv = false;
	st = 0;
	if (pempty)
	{
		tekst.setFillColor(sf::Color(textcolor->r, textcolor->g, textcolor->b, static_cast<sf::Uint8>(0)));
		tekst.setString("Unable to save the game.");
		th = static_cast<int>(tekst.getGlobalBounds().height);
		tekst.setPosition(floor(sw / 24.f), static_cast<float>(the));
		the += 2 * th;
		additional.push_back(tekst);
		tekst.setString("Add at least one profile.");
		tekst.setPosition(floor(sw / 24.f), static_cast<float>(the));
		the += th;
		additional.push_back(tekst);
		tekst.setString("");
		return;
	}
	else if (sempty)
	{
		tekst.setFillColor(sf::Color(textcolor->r, textcolor->g, textcolor->b, static_cast<sf::Uint8>(0)));
		tekst.setString("Unable to save the game.");
		th = static_cast<int>(tekst.getGlobalBounds().height);
		tekst.setPosition(floor(sw / 24.f), static_cast<float>(the));
		the += 2 * th;
		additional.push_back(tekst);
		tekst.setString("Add at least one story.");
		tekst.setPosition(floor(sw / 24.f), static_cast<float>(the));
		the += th;
		additional.push_back(tekst);
		tekst.setString("");
		return;
	}
	in.open(path);
	if (!in) throw std::runtime_error("File that contains story couldn't be open");
	//else //mfile << '[' << sgoto << ']' << "Story file could be opened" << std::endl;
	in.imbue(utf8_locale);
	GotoLine(cgoto);

	tekst.setFillColor(*textcolor);
	std::wstring preinsr;
	preinsr.reserve(400);
	for (;;)
	{
		if (dgoto != 0 && sgoto >= dgoto) { SplitText(false, insr); break; }
		std::getline(in, preinsr);
		++sgoto;
		if (preinsr[0] == '#')
		{
			//mfile << '[' << sgoto << ']' << "Executed a command" << std::endl;
			SplitText(false, insr);
			if (preinsr == L"#end")
			{
				//mfile << '[' << sgoto << ']' << "Command executed: #end" << std::endl;
				SplitText(false, insr);
				break;
			}
			else if (preinsr == L"#next")
			{
				//mfile << '[' << sgoto << ']' << "Command executed: #next" << std::endl;
				SplitText(false, insr);
				next.setPosition(floor(sw / 2 - next.getGlobalBounds().width / 2.f), floor(the + next.getGlobalBounds().height / 2.f));
				the += static_cast<int>(next.getGlobalBounds().height * 1.6f); //ignore warn
				drawnext = true;
				break;
			}
			else if (preinsr == L"#choice") CreateChoice(preinsr);
			else if (!loadtextonly) ExecuteCommand(preinsr, sw, sh);
			continue;
		}
		if (CommentCheck(preinsr))
		{
			if (preinsr.empty())
				continue;
		};
		if (preinsr.empty() || preinsr == empty || preinsr == L"\n")
		{
			SplitText(false, insr);
			the += th;
		}
		else if (preinsr[0] == L'\t'){
			insr += '\n';
			insr += preinsr;
		}
		else if (preinsr == split) formattype = !formattype;
		else {
			insr += preinsr;
			if (formattype) SplitText(false, insr);
			else insr += L" ";
		}
	}
	loadtextonly = true;
	st = static_cast<int>(round((the - sh) / (sh/450.f *tekst.getCharacterSize())));
	in.close();
	Save();
	if (the > sh) slideratv = true;
	choicesel = -1;
}
void ScenarioParser::Save()
{
	if (sempty || pempty) return;
	std::wofstream save(savefile);
	save.imbue(utf8_locale);
	if (save)
	{
		save << cgoto << std::endl;
		save << dgoto << std::endl;
		save << static_cast<int>(loadtextonly) << std::endl;
		save << '}' << std::endl;

		for (IntStatOpposite &x : io_stats) save << x.name << ',' << x.value << ',' << x.max << ',' << x.min << ',' << x.threshold << ',' << x.hidden << ',' << x.prior << ',' << x.opposite << std::endl;
		save << '}' << std::endl;

		for (auto &x : i_stats) save << x.name << ',' << x.value << ',' << x.max << ',' << x.min << ',' << x.hidden << ',' << x.prior << std::endl;
		save << '}' << std::endl;

		for (auto &x : s_stats) save << x.name << ',' << x.value << ',' << x.hidden << x.vhidden << ',' << x.prior << std::endl;
		save << '}' << std::endl;

		for (auto &x : Ints) save << x.name << ',' << x.value << ',' << x.hidden << ',' << x.prior << std::endl;
		save << '}' << std::endl;
	}
	//else throw std::runtime_error('[' + sgoto + "]Error: Couldn't load save [while saving]: missing file or invalid path");
		//mfile << '[' << sgoto << ']' << "Error: Couldn't load save (while saving) file with name \"" << savefile << '\"' << std::endl;
}

void ScenarioParser::ExecuteCommand(std::wstring &insrtttt, int &sw, int &sh)
{
	if (insrtttt.size() >= 17 && std::equal(insrtttt.begin(),
		insrtttt.begin() + 17, L"#IntStatOpposite("))
	{
		insrtttt.erase(0U, 17U);
		//mfile << '[' << sgoto << ']' << "Command executed: #IntStatOpposite" << std::endl;
		Thingy(0, insrtttt);
	}
	else if (insrtttt.size() >= 9 && std::equal(insrtttt.begin(),
		insrtttt.begin() + 9, L"#IntStat("))
	{
		insrtttt.erase(0U, 9U);
		//mfile << '[' << sgoto << ']' << "Command executed: #IntStat" << std::endl;
		Thingy(1, insrtttt);
	}
	else if (insrtttt.size() >= 12 && std::equal(insrtttt.begin(),
		insrtttt.begin() + 12, L"#StringStat("))
	{
		insrtttt.erase(0U, 12U);
		//mfile << '[' << sgoto << ']' << "Command executed: #StringStat" << std::endl;
		Thingy(2, insrtttt);
	}
	else if (insrtttt.size() >= 5 && std::equal(insrtttt.begin(),
		insrtttt.begin() + 5, L"#Int("))
	{
		insrtttt.erase(0U, 5U);
		//mfile << '[' << sgoto << ']' << "Command executed: #Int" << std::endl;
		Thingy(3, insrtttt);
	}
	else if (insrtttt.substr(0, 6) == L"#goto(")
	{
		//mfile << "Command executed: #goto" << std::endl;
		int line;
		if (stoicheck(insrtttt.substr(6, insrtttt.size() - 1), line)) GotoLine(line);
		else throw std::runtime_error("Goto command failure! Check if you didn't use a letter or if you put too many non-digit characters");
	}
	else if (insrtttt.substr(0, 5) == L"#set(")
	{
		size_t n;
		if ((n = std::count(insrtttt.begin(), insrtttt.end(), L',')) == std::wstring::npos) return;
		int arg[3];
	}
	else if (insrtttt == L"#showstats") //it will be changed so stats will appear
	{

	}
}

void ScenarioParser::SplitText(bool w, std::wstring &insrt)
{
	if (insrt.empty()) return;
	size_t d;
	while ((d = insrt.find('\n')) != std::wstring::npos)
	{
		SplitText(w, insrt.substr(0, d));
		insrt.erase(0, d+1);
	}
	std::vector<sf::Vector2i> b;
	for (;;)
	{
		b.push_back(sf::Vector2i());
		if ((b.back().x = insrt.find(L"[B]")) != std::wstring::npos)
			insrt.erase(b.back().x, 3U);
		else {
			b.pop_back(); break;
		}
		if ((b.back().y = insrt.find(L"[/B]")) != std::wstring::npos)
			insrt.erase(b.back().y, 4U);
		else throw std::runtime_error("Error: couldn't find \"[/B]\" - did you close every \"[B]\" before exectuing a command?");
	}
	float &wu = w ? w2 : w1;
		tekst.setString(insrt);
		tekst.setPosition(wu, static_cast<float>(the));
		//----------------------------------//
		std::vector<sf::Text> &v = w ? choice.back().text : additional;
		if (tekst.getGlobalBounds().left + tekst.getGlobalBounds().width < owd || insrt.find(L' ') == std::wstring::npos) { formaT(v, wu, b); }
		else
		{
			std::wstring str;
			for (size_t pos = 0;;) {
				if ((pos = insrt.find(L' ', pos + 1)) == std::wstring::npos)
				{
					tekst.setString(insrt);
					if (tekst.getGlobalBounds().left + tekst.getGlobalBounds().width > owd && insrt.find(L' ') != std::wstring::npos) goto skip;
					tekst.setPosition(wu, static_cast<float>(the));
					formaT(v, wu, b);
					break;
				}

				tekst.setString(insrt.substr(0, pos));
				str = tekst.getString().toWideString();
				if (tekst.getGlobalBounds().left + tekst.getGlobalBounds().width > owd)
				{
					if (insrt.rfind(L' ', pos - 1) != std::wstring::npos)
					{
						pos = insrt.rfind(L' ', pos - 1);
					}
				skip:tekst.setString(insrt.substr(0, pos));
					insrt.erase(0, pos + 1);
					tekst.setPosition(wu, static_cast<float>(the));
					formaT(v, wu, b);
				}
			}
		}
	insrt.clear();
}	

int ScenarioParser::stoicheck(std::string &checked, int def)
{
	if (checked.empty()) return def;
	for (char c : checked){
		if (!isdigit(c))
		{
			//mfile << '[' << sgoto << ']' << "Error: stoicheck failure at char \"" << c << '\"' << "in string \"" << checked.c_str() << '\"' << std::endl;
			return def;
		}
	}
	return std::stoi(checked);
}

bool ScenarioParser::stoicheck(std::wstring &checked, int &number, int def)
{
	if (checked.empty())
	{
		number = def;
		return false;
	}
	for (wchar_t c : checked) {
		if (!isdigit(c))
		{
			//mfile << '[' << sgoto << ']' << "Error: stoicheck failure at char \"" << c << '\"' << "in string \"" << checked << '\"' << std::endl;
			number = def;
			return false;
		}
	}
	number = stoi(checked);
	return true;
}
void ScenarioParser::Thingy(int state, std::wstring insert)
{
	if (insert.empty()) return;//{ //mfile << '[' << sgoto << ']' << L"Error: the save contains an empty line or is empty" << std::endl; return; }
	std::wstring name;
	int arglistx = 0;
	if (state == 0){
		name = L"IntStatOpposite";
		arglistx = 7;	
	}
	else if (state == 1){
		name = L"IntStat";
		arglistx = 5;
	}
	else if (state == 2){
		name = L"StringStat";
		arglistx = 4;
	}
	else if (state == 3)
	{
		name = L"Int";
		arglistx = 3;
	}
	std::wstring names[2];
	int arguments[6] = { 0, 0, 0, 0, 0, 0 },
		arglist = 0,
		namelist = 0;
	for (arglist = 0; arglist < arglistx; ++arglist)
	{
		unsigned int __w64 s_position = 0U;	
		if (insert.empty() || !(s_position = insert.find(L',')))
		{
			//mfile << '[' << sgoto << ']' << L"Error: an/a \"" + name + L"\" with name " << names[0].empty() ? L"unknown" : names[0];
			//if (insert.empty()) mfile << L" couldn't be loaded (an empty argument " << arglist << L')' << std::endl/*L*/;
			//else mfile << L" couldn't be loaded (missing argument " << arglist << L')' << std::endl/*L*/;
			break;
		}
		switch (arglist)
		{
		case 0:
			names[0] = insert.substr(0, s_position);
			if (chName(names[0])) return;
			++namelist;
			break;
		case 1:	
			if (state == 2){
				names[1] = insert.substr(0, s_position);
				++namelist;
			}
			if (!stoicheck(insert.substr(0, s_position), arguments[0])) return; //{ mfile << L"[Stat]Error: An/a " + name + L" with name " + names[0] + L" failed its stoicheck on argument 1"; return; }
			break;
		default:
			if (!stoicheck(insert.substr(0, s_position), arguments[arglist - 1])) return; //{ mfile << "[Stat]Error: An/a " << name << " with name " << names[0] << " failed its stoicheck on argument " << arglist; return; }
			break;
		}
		insert.erase(0U, s_position + 1U);
	}
	if (arglist == arglistx)
	{
		//if (insert.empty()) mfile << '[' << sgoto << ']' << L"Error: an/a \"" + name + L"\" with name \"" + names[0] + L"\" couldn't be loaded (last argument empty)" << std::endl/*L*/;
		if (!insert.empty())
		{
			if (state == 0) names[namelist] = insert.substr(0, insert.size() - 1);
			else{
				//if (!stoicheck(insert.substr(0, insert.size() - 1), arguments[arglist - namelist])) mfile << L"[Stat]Error: An/a " + name + L" with name " + names[0] + L" failed its stoicheck on argument " << arglist - namelist;
				stoicheck(insert.substr(0, insert.size() - 1), arguments[arglist - namelist]);
			}
			insert.clear();
			//if ((state == 1 || state == 0) && arguments[1] == arguments[2]) //mfile << '[' << sgoto << L"]Error: an/a \"" + name + L"\" with name \"" + names[0] + L"\" has same minimum value as maximum value - it hasn't any purpose(to hold values use Int)" << std::endl/*L*/;
			//else if ((state == 1 || state == 0) && arguments[1] < arguments[2]) //mfile << '[' << sgoto << L"]Error: an/a \"" + name + L"\" with name \"" + names[0] + L"\" has higher minimum value than maximum value" << std::endl/*L*/;
			//else
			//{
				if (state == 0) io_stats.push_back(IntStatOpposite(names[0], arguments[0], arguments[1], arguments[2], arguments[3], arguments[4], arguments[5], names[1]));
				else if (state == 1) i_stats.push_back(IntStat(names[0], arguments[0], arguments[1], arguments[2], arguments[3], arguments[4]));
				else if (state == 2) s_stats.push_back(StringStat(names[0], names[1], arguments[0], arguments[1], arguments[2]));
				else if (state == 3) Ints.push_back(Int(names[0], arguments[0], arguments[1], arguments[2]));
				//mfile << '[' << sgoto << ']' << L"Could load an/a \"" + name + L"\" with name \"" + names[0] << '\"' << std::endl/*L*/;
			//}
		}
	}
	//else if (arglist == 1) //mfile << '[' << sgoto << "]Error: could not load(missing arguments or stoicheck failure) an/a \"" << name << "\" with name\"" << names[0] << '\"' << std::endl/*L*/;
	//else //mfile << '[' << sgoto << "]Error: could not load(missing arguments or stoicheck failure) an/a \"" << name << "\" with missing name" << std::endl/*L*/;
}

void ScenarioParser::formaT(std::vector<sf::Text> &vec, int wu, std::vector<sf::Vector2i> &b)
{
	if (b.size() == 0){
		tekst.setPosition(wu, static_cast<float>(the));
		the += static_cast<int>(tekst.getGlobalBounds().height * 1.2f);
		vec.push_back(tekst);
		return;
	}
	int one = (sw + sh) / 1400;
	sf::String str = tekst.getString();
	unsigned int size = str.getSize();
	float hgh = tekst.getGlobalBounds().height;
	for (unsigned int x = 0U, bsize = b.size(); x < bsize; ++x)
	{
		std::wstring c = tekst.getString().toWideString();
		if (x != 0U)
		{
			tekst.setPosition(vec.back().getGlobalBounds().left + vec.back().getGlobalBounds().width + one, static_cast<float>(the));
			tekst.setString(str.substring(b[x-1].y, b[x].x - b[x - 1].y));
		}
		else
		{
			tekst.setPosition(wu, static_cast<float>(the));
			tekst.setString(str.substring(0, b[x].x));
		}
		if (!tekst.getString().isEmpty()) vec.push_back(tekst);
		std::wstring a = tekst.getString().toWideString();


		tekst.setStyle(sf::Text::Bold);
		tekst.setPosition(round(vec.back().getGlobalBounds().left + vec.back().getGlobalBounds().width + one), static_cast<float>(the));
		tekst.setString(str.substring(b[x].x, b[x].y - b[x].x));
		vec.push_back(tekst);

		std::wstring bc = tekst.getString().toWideString();
		tekst.setStyle(sf::Text::Regular);
	}
	b.clear();
	the += static_cast<int>(tekst.getGlobalBounds().height * 1.2f);
}

void ScenarioParser::RoundRect()
{
	if (choice.empty() || choice.back().text.empty()) return;
	sf::ConvexShape rrect;
	float X = 0, Y = 0, ratio = (sw + sh) / 1400.f;
	int radius = static_cast<int>(round(15.f * ratio));
	float add = radius / 15.f;
	int rectWidth = 0, rectHeight = 0;
	for (sf::Text &c : choice.back().text)
	{
		rectHeight += c.getGlobalBounds().height * 1.15f;
	}
	for (unsigned int x = rectWidth, size = choice.back().text.size(); x < size; ++x)
	{
		if (choice.back().text[x].getGlobalBounds().width > choice.back().text[rectWidth].getGlobalBounds().width) rectWidth = x;
	}
	sf::CircleShape cs(static_cast<float>(radius));
	cs.setFillColor(sf::Color(static_cast<sf::Uint8>(0), static_cast<sf::Uint8>(0), static_cast<sf::Uint8>(0), static_cast<sf::Uint8>(0)));
	cs.setOutlineThickness(floor(2.f * ratio));
	cs.setOutlineColor(sf::Color(static_cast<sf::Uint8>(0), static_cast<sf::Uint8>(0), static_cast<sf::Uint8>(0), static_cast<sf::Uint8>(0)));
	rectWidth = static_cast<int>(choice.back().text[rectWidth].getGlobalBounds().width) + 2*radius;
	rrect.setPointCount(60);
	rrect.setOutlineThickness(floor(2.f * (sh + sw) / 1400.f));
	rrect.setOutlineColor(sf::Color(static_cast<sf::Uint8>(0), static_cast<sf::Uint8>(0), static_cast<sf::Uint8>(0), static_cast<sf::Uint8>(0)));
	rrect.setFillColor(sf::Color(static_cast<sf::Uint8>(0), static_cast<sf::Uint8>(0), static_cast<sf::Uint8>(0), static_cast<sf::Uint8>(0)));
	unsigned int i;
	for (i = 0U; i<15U; i++)
	{
		X += add;
		Y = sqrt(radius * radius - X*X);
		rrect.setPoint(i, sf::Vector2f(rectWidth + X - radius, radius - Y)); //prawa . || góra v.
	}
	Y = 0;
	for (i = 0U; i<15U; i++)
	{
		Y += add;
		X = sqrt(radius * radius - Y*Y);
		rrect.setPoint(15 + i,	sf::Vector2f(rectWidth + X - radius, rectHeight - radius + Y)); //prawa <-. || dó³ v
	}
	X = 0;
	for (i = 0U; i<15U; i++)
	{
		X += add;
		Y = sqrt(radius * radius - X*X);
		rrect.setPoint(30 + i, sf::Vector2f(radius - X, rectHeight - radius + Y)); //lewa <- || dó³ ^.
	}
	Y = 0;
	for (i = 0U; i<15U; i++)
	{
		Y += add;
		X = sqrt(radius * radius - Y*Y);
		rrect.setPoint(45 + i, sf::Vector2f(radius - X, radius - Y));
	}
	rrect.setPosition(choice.back().text[0].getPosition().x - radius, choice.back().text[0].getGlobalBounds().top * 1 - choice.back().text[0].getGlobalBounds().height * 0.1f);
	cs.setPosition(rrect.getPosition().x - static_cast<int>(cs.getGlobalBounds().width*1.2f), round(rrect.getGlobalBounds().top + rrect.getGlobalBounds().height / 2.f - cs.getGlobalBounds().height / 2.f));
	choice.back().cs = cs;
	choice.back().c = rrect;
}

bool ScenarioParser::CommentCheck(std::wstring &insr)
{ 
	size_t bt;
	if ((bt = insr.find(comment)) != std::string::npos)
	{
		insr.erase(bt, std::string::npos);
		return true;
	}
	return false;
}

bool ScenarioParser::statfind(std::wstring &name, int &val)
{
	for (auto &x : i_stats){
		if (name == x.name){
			val = x.value;
			//mfile << '[' << sgoto << ']' << "[Choice]\"if\" successful" << std::endl;
			return true;
		}
	}
	for (auto &x : io_stats){
		if (name == x.name){
			val = x.value;
			//mfile << '[' << sgoto << ']' << "[Choice]\"if\" successful" << std::endl;
			return true;
		}
	}
	for (auto &x : Ints){
		if (name == x.name){
			val = x.value;
			//mfile << '[' << sgoto << ']' << "[Choice] \"if\" sucessfull" << std::endl;
			return true;
		}
	}
	//mfile << '[' << sgoto << ']' << "[Choice]Error: could not find variable with name \"" << name << "\" \"If\" failure" << std::endl/*L*/;
	return false;
}

void ScenarioParser::CreateChoice(std::wstring &insrtttt)
{
	//mfile << '[' << sgoto << ']' << "Command executed: #choice" << std::endl;
	insr.clear(); insrtttt.clear();
	the += static_cast<int>(th * 0.6f);
	choice.push_back(Choice());
	for (;;) 
	{
		std::getline(in, insrtttt);
		++sgoto;
		CommentCheck(insrtttt);
		if (insrtttt.empty()) insr += '\n';
		//mfile << '[' << sgoto << ']' << "[Choice]Found an empty line" << std::endl;
		else if (insrtttt[0] == L'\t') {
			insr += '\n';
			insr += insrtttt;
		}
		else if (insrtttt[0] == L'#') break;
		else { insr += insrtttt; insr += L' '; }; //http://stackoverflow.com/questions/41353227/does-stdstring-char-expression-create-another-stdstring
	}
	std::wstring value;
	for (;;)
	{
		if (insrtttt[0] == '#')
		{
			//mfile << '[' << sgoto << ']' << "[Choice]First character of the line is \"#\". Checking if choice is available..." << std::endl;
			sf::Uint8 to3;
			int bt, val;
			if ((bt = insrtttt.rfind(L"hidden ")) != std::wstring::npos)
				choice.back().hidden = (insrtttt[8] == 'y');
			else {
				if ((bt = insrtttt.rfind(L"==")) != std::wstring::npos) { to3 = 2; value = insrtttt.substr(bt + 2, insrtttt.size() - bt - 4); insrtttt.resize(bt); insrtttt.erase(0U, 4U); }
				else if ((bt = insrtttt.rfind(L"<=")) != std::wstring::npos) { to3 = 3; value = insrtttt.substr(bt + 2, insrtttt.size() - bt - 4); insrtttt.resize(bt); insrtttt.erase(0U, 4U); }
				else if ((bt = insrtttt.rfind(L">=")) != std::wstring::npos) { to3 = 4; value = insrtttt.substr(bt + 2, insrtttt.size() - bt - 4); insrtttt.resize(bt); insrtttt.erase(0U, 4U); }
				else if ((bt = insrtttt.rfind(L"!=")) != std::wstring::npos) { to3 = 5; value = insrtttt.substr(bt + 2, insrtttt.size() - bt - 4); insrtttt.resize(bt); insrtttt.erase(0U, 4U); }
				else if ((bt = insrtttt.rfind(L'>')) != std::wstring::npos) { to3 = 0; value = insrtttt.substr(bt + 1, insrtttt.size() - bt - 3); insrtttt.resize(bt); insrtttt.erase(0U, 4U); }
				else if ((bt = insrtttt.rfind(L'<')) != std::wstring::npos) { to3 = 1; value = insrtttt.substr(bt + 1, insrtttt.size() - bt - 3); insrtttt.resize(bt); insrtttt.erase(0U, 4U); }
				else throw std::runtime_error("Improper choice command"); //{ mfile << '[' << sgoto << ']' << L"[Choice] Error: Found \"#\", but couldn't find proper command for \"if\""; return; };
				if (choice.back().avaible && stoicheck(value, val) && statfind(insrtttt, bt))
				{
					switch (to3)
					{
					case 0:
						choice.back().avaible = (bt > val);
						break;
					case 1:
						choice.back().avaible = (bt < val);
						break;
					case 2:
						choice.back().avaible = (bt == val);
						break;
					case 3:
						choice.back().avaible = (bt <= val);
						break;
					case 4:
						choice.back().avaible = (bt >= val);
						break;
					case 5:
						choice.back().avaible = (bt != val);
						break;
					}
					if (!choice.back().avaible) {
						for (auto &e : choice.back().text) e.setFillColor(tekst.getFillColor()); choice.back().c.setOutlineColor(*textchoiceunavaiblecolor); choice.back().cs.setOutlineColor(*textchoiceunavaiblecolor);
					}
				}
			}
		}
		//else if (insrtttt.empty())
		//{
			//mfile << '[' << sgoto << ']' << "[Choice]Wrong input: Found an empty line" << std::endl;
		//	return;
		//}
		else if (insrtttt[0] == L'{')
		{
			choice.back().gto = sgoto + 1;
			//mfile << '[' << sgoto << ']' << "[Choice]Searching for \"}\". If infinite loop occurs (program is stuck and yields no repsonse) you probably forgot to write \"}\" at the end of choice" << std::endl;
			for (; insrtttt != L"}"; sgoto++) std::getline(in, insrtttt); //seekg \n
			choice.back().dgto = sgoto;
			if (!choice.back().avaible && choice.back().hidden) { insr.clear(); return; }
			choiceneed = true;
			SplitText(true, insr);
			RoundRect();
			return;
		}
		else throw std::runtime_error("Improper choice command"); //{ mfile << '[' << sgoto << ']' << "[Choice]Wrong input: First character of the line is not \"#\". It is not valid \"if\"" << std::endl; return; }
		std::getline(in, insrtttt);
		++sgoto;
	}
}

bool ScenarioParser::chName(std::wstring name)
{	
	for (auto &x : s_stats){
		if (name == x.name){
			//mfile << '[' << sgoto << ']' << "Error: there is a name conflict! There can be no 2 variables of type \"StringStat\" with name \"" << name << "\". Ignoring second variable. \"If\" from [Choice] yields false" << std::endl/*L*/;
			return true;
		}
	}
	for (auto &x : i_stats){
		if (name == x.name){
			//mfile << '[' << sgoto << ']' << "Error: there is a name conflict! There can be no 2 variables of type \"IntStat\" with name \"" << name << "\". Ignoring second variable. \"If\" from [Choice] yields false" << std::endl/*L*/;
			return true;
		}
	}
	for (auto &x : io_stats){
		if (name == x.name){
			//mfile << '[' << sgoto << ']' << "Error: there is a name conflict! There can be no 2 variables of type \"IntStatOpposite\" with name \"" << name << "\". Ignoring second variable. \"If\" from [Choice] yields false" << std::endl/*L*/;
			return true;
		}
	}
	for (auto &x : Ints){
		if (name == x.name){
			//mfile << '[' << sgoto << ']' << "Error: there is a name conflict! There can be no 2 variables of type \"Int\" with name \"" << name << "\". Ignoring second variable. \"If\" from [Choice] yields false" << std::endl/*L*/;
			return true;
		}
	}
	return false;
}
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
extern unsigned int priorlimit;
constexpr wchar_t* const split = L"`/`"; //Add an option to change it, for user preference
const size_t split_l = std::wcslen(split);
constexpr wchar_t* const comment = L"//"; //Add an option to change it, for user preference
constexpr wchar_t* const empty = L"`"; //Add an option to change it, for user preference
//todo: repair set(using show_stats), add type function, add stc command, add achievements, add center text, add gain text, //change the color, change pos to sf::Vector2f, ignore tabs, erase command
void ScenarioParser::GotoLine(const int num)
{
	in.seekg(std::ios::beg);
	for (int i = 0U; i < num; ++i){
		in.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
	}
	cgoto = sgoto = num;
}

void ScenarioParser::Parse()
{
	drawnext = false;
	choice.clear();
	tinsr.clear();
	text.setString(L"");
	slideratv = false;
	the = h / 12;
	choicesel = -1;
	if (pempty)
	{
		text.setPosition(round(w / 24.f), static_cast<float>(the));
		text.setString("Unable to save the game.\nAdd at least one profile.");
		return;
	}
	else if (sempty)
	{
		text.setPosition(round(w / 24.f), static_cast<float>(the));
		text.setString("Unable to save the game.\nAdd at least one story.");
		return;
	}
	in.open(path);
	if (!in) throw w_err(L"File that contains story couldn't be open [" + std::to_wstring(sgoto) + L']');
	in.imbue(utf8_locale);
	GotoLine(cgoto);

	ParseMainBody();
	in.close();
	st = static_cast<int>(round((the - h) / (100.f *(w + h) / 1400.f)));
	if (!debug) {
		loadtextonly = true;
		Save();
	}
	if (the > h) slideratv = true;
	if (ssreload) Show_stats();
}

void ScenarioParser::Save()
{
	if (sempty || pempty || debug) return;
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

		for (auto &x : s_stats) save << x.name << ',' << x.value << ',' << x.hidden << ',' << x.vhidden << ',' << x.prior << std::endl;
		save << '}' << std::endl;

		for (auto &x : Ints) save << x.name << ',' << x.value << ',' << x.hidden << ',' << x.prior << std::endl;
		save << '}' << std::endl;
	}
	else throw w_err(L"Error: Couldn't load save [while saving]: missing file or invalid path \"" + savefile + L"\" [" + std::to_wstring(sgoto) + L']');
}

void ScenarioParser::ExecuteCommand(std::wstring &insrtttt)
{
	if (insrtttt == L"#choice")
	{
		SplitText(false, insr);
		MergeText();
		CreateChoice();
	}
	else if (insrtttt == L"#debug")
	{
		debug = true;
		std::wofstream save(savefile, std::wios::trunc);
		dgoto = cgoto = 0;
		loadtextonly = false;
	}
	else if (insrtttt == L"#showstats") //it will be changed so stats will appear
	{

	}
	else if (!loadtextonly)
	{
		if (insrtttt.substr(0U, 11U) == L"#piorlimit(")
		{
			if (stoicheck(insrtttt.substr(11U, insrtttt.size() - 12U), priorlimit)) throw w_err(L"FATAL stoicheck failure while exectuing \"#priorlimit\" command [" + std::to_wstring(sgoto) + L']');
		}
		else if (insrtttt.substr(0U, 17U) == L"#IntStatOpposite(")
		{
			insrtttt.erase(0U, 17U);
			Thingy(0, insrtttt);
		}
		else if (insrtttt.substr(0U, 9U) == L"#IntStat(")
		{
			insrtttt.erase(0U, 9U);
			Thingy(1, insrtttt);
		}
		else if (insrtttt.substr(0U, 12U) == L"#StringStat(")
		{
			insrtttt.erase(0U, 12U);
			Thingy(2, insrtttt);
		}
		else if (insrtttt.substr(0U, 5U) == L"#Int(")
		{
			insrtttt.erase(0U, 5U);
			Thingy(3, insrtttt);
		}
		else if (insrtttt.substr(0U, 5U) == L"#Set(")
		{
			insrtttt.erase(0U, 5U);
			size_t n;
			if ((n = insrtttt.find(L',')) == std::wstring::npos) return;
			std::wstring name = insrtttt.substr(0U, n);
			insrtttt.erase(0U, n);
			std::wstring value = insrtttt.substr(1U, insrtttt.size() - 2U);
			insrtttt.erase(0U, n);
			for (auto &x : io_stats)
			{
				if (name == x.name)
				{
					if (!stoicheck(value, x.value)) throw w_err(L"FATAL stoicheck failure while exectuing \"#set\" command(1st argument) [" + std::to_wstring(sgoto) + L']');

					if ((n = insrtttt.find(L',')) == std::wstring::npos) goto iocalc;
					value = insrtttt.substr(0U, n);
					insrtttt.erase(0U, n);
					if (!stoicheck(value, x.min)) throw w_err(L"FATAL stoicheck failure while exectuing \"#set\" command(2nd argument) [" + std::to_wstring(sgoto) + L']');

					if ((n = insrtttt.find(L',')) == std::wstring::npos) goto iocalc;
					value = insrtttt.substr(0U, n);
					insrtttt.erase(0U, n);
					if (!stoicheck(value, x.max)) throw w_err(L"FATAL stoicheck failure while exectuing \"#set\" command(3nd argument) [" + std::to_wstring(sgoto) + L']');

					if ((n = insrtttt.find(L',')) == std::wstring::npos) goto iocalc;
					value = insrtttt.substr(0U, n);
					if (!stoicheck(value, x.threshold)) throw w_err(L"FATAL stoicheck failure while exectuing \"#set\" command(4nd argument) [" + std::to_wstring(sgoto) + L']');
				iocalc:
					x.t[2].setString(std::to_wstring(x.value));
					x.t[2].setOrigin(2, round(x.t[2].getLocalBounds().top + x.t[2].getLocalBounds().height / 2.f));
					x.setSprite(IOStatspecial(static_cast<int>(round(w / 1.45f)), x.s.getGlobalBounds().height, x.value, x.min, x.max, x.threshold));
					x.t[2].setPosition(static_cast<sf::Vector2f>(x.pos[2]));
					return;
				}
			}
			for (auto &x : i_stats)
			{
				if (name == x.name)
				{
					if (!stoicheck(value, x.value)) throw w_err(L"FATAL stoicheck failure while exectuing \"#set\" command(1st argument) [" + std::to_wstring(sgoto) + L']');

					if ((n = insrtttt.find(L',')) == std::wstring::npos) goto icalc;
					value = insrtttt.substr(0U, n);
					insrtttt.erase(0U, n);
					if (!stoicheck(value, x.min)) throw w_err(L"FATAL stoicheck failure while exectuing \"#set\" command(2nd argument) [" + std::to_wstring(sgoto) + L']');

					if ((n = insrtttt.find(L',')) == std::wstring::npos) goto icalc;
					value = insrtttt.substr(0U, n);
					if (!stoicheck(value, x.max)) throw w_err(L"FATAL stoicheck failure while exectuing \"#set\" command(3nd argument) [" + std::to_wstring(sgoto) + L']');
				icalc:
					int arg[3] = { x.value, x.min, x.max };
					if (arg[1] < 0)
					{
						arg[0] -= arg[1];
						arg[2] -= arg[1];
						arg[1] = 0;
					}
					x.t.setString(x.name + L": " + std::to_wstring(static_cast<int>(round(arg[0] * 100.f / arg[2]))) + L"%");
					x.t.setOrigin(0, round(x.t.getLocalBounds().top + x.t.getLocalBounds().height / 2.f));
					x.setSprite(IntSpecial(static_cast<int>(round(w / 1.45f)), x.s.getGlobalBounds().height, arg[0], arg[1], arg[2]));
					x.t.setPosition(static_cast<sf::Vector2f>(x.pos[0]));
					return;
				}
			}
			for (auto &x : s_stats)
			{
				if (name == x.name)
				{
					x.value = value;
					x.t.setString(x.name + L": ");
					if (!x.vhidden) x.t.setString(x.t.getString() + x.value);
					x.t.setOrigin(0, round(x.t.getLocalBounds().top));
					x.t.setPosition(static_cast<sf::Vector2f>(x.pos));
					return;
				}
			}
			for (auto &x : Ints)
			{
				if (name == x.name)
				{
					if (!stoicheck(value, x.value)) throw w_err(L"FATAL stoicheck failure while exectuing \"#set\" command(1st argument) [" + std::to_wstring(sgoto) + L']');
					x.t.setString(x.name + L": " + std::to_wstring(x.value));
					x.t.setOrigin(0, round(x.t.getLocalBounds().top));
					x.t.setPosition(static_cast<sf::Vector2f>(x.pos));
					return;
				}
			}
		}
		else if (insrtttt.substr(0U, 6U) == L"#hide(")
		{
			std::wstring name = insrtttt.substr(6U, insrtttt.size() - 7U);
			for (auto x : io_stats)
			{
				if (name == x.name) {
					x.hidden = !x.hidden;
					return;
				}
			}
			for (auto x : i_stats)
			{
				if (name == x.name) {
					x.hidden = !x.hidden;
					return;
				}
			}
			for (auto x : s_stats)
			{
				if (name == x.name) {
					x.hidden = !x.hidden;
					return;
				}
			}
			for (auto x : Ints)
			{
				if (name == x.name) {
					x.hidden = !x.hidden;
					return;
				}
			}
		}
		else if (insrtttt.substr(0U, 7U) == L"#vhide(")
		{
			std::wstring name = insrtttt.substr(7U, insrtttt.size() - 8U);
			for (auto x : s_stats)
			{
				if (name == x.name) {
					x.vhidden = !x.vhidden;
					x.t.setString(x.name + L": ");
					if (!x.vhidden) x.t.setString(x.t.getString() + x.value);
					x.t.setOrigin(0, round(x.t.getLocalBounds().top));
					x.t.setPosition(static_cast<sf::Vector2f>(x.pos));
					return;
				}
			}
		}
		else if (insrtttt.substr(0U, 5U) == L"#stc(")
		{
			insrtttt.erase(0U, 5U);
			size_t n;
			if ((n = insrtttt.find(L',')) == std::wstring::npos) return;
			std::wstring name = insrtttt.substr(0U, n),
				value = insrtttt.substr(n + 1U, insrtttt.size() - 1U - n);
			if (chName(name)) return;
		}
	}
}

void ScenarioParser::SplitText(const bool w, std::wstring &insrt)
{
	if (insrt.empty()) return;
	size_t d;
	std::wstring str;
	while ((d = insrt.find(L'\n', 1U)) != std::wstring::npos)
	{
		if (d == insr.size() - 2U) break;
		SplitText(w, insrt.substr(0U, d));
		insrt.erase(0U, d+1);
	}
	sf::Text tekst = w ? choice.back().text : text;
	tekst.setString(insrt);
	if ((tekst.getLocalBounds().left + tekst.getGlobalBounds().left + tekst.getGlobalBounds().width) < static_cast<float>(owd) || insrt.find(L' ') == std::wstring::npos) str = insrt + L'\n';
	else
	{
		for (size_t pos = 0U;;) {
			pos = insrt.find(L' ', pos + 1U);
			tekst.setString(insrt.substr(0U, pos));
			if ((tekst.getLocalBounds().left + tekst.getGlobalBounds().left + tekst.getGlobalBounds().width) > owd)
			{
				size_t cpos;
				if ((cpos = insrt.rfind(L' ', pos - 1U)) == std::wstring::npos) cpos = pos;
				else { //single characters
					while (cpos - insrt.rfind(L' ', cpos - 1U) < 3) {
						if ((cpos = insrt.rfind(L' ', cpos - 1U)) == std::wstring::npos) {
							cpos = insrt.rfind(L' ', pos - 1U);
							break;
						}
					}
				}
				str += insrt.substr(0U, cpos);
				str += L'\n';
				insrt.erase(0U, cpos + 1U);
				pos = 0;
			}
			else if (pos == std::wstring::npos)
			{
				str += insrt;
				str += L'\n';
				break;
			}
		}
	}
	if (w)
	{
		str.pop_back();
		sf::Text &t = choice.back().text;
		sf::String s = t.getString();
		if (!s.isEmpty()) str.insert(str.begin(), L'\n');
		t.setString(s + str);
	}
	else tinsr += str;
	insrt.clear();
}	

const int ScenarioParser::stoicheck(std::string &checked, const int def)
{
	if (checked.empty())
	{
		warn(L"[Stoicheck failure] stoicheck performed on an empty string [" + std::to_wstring(sgoto) + L']');
		return def;
	}
	for (char c : checked){
		if (!isdigit(c, utf8_locale))
		{
			if (checked[0] == 0xFEFF)
			{
				checked.erase(0U, 1U);
				continue;
			}
			else if (checked[0] == 0xef && checked[1] == 0xbb && checked[2] == 0xbf)
			{
				checked.erase(0U, 3U);
				continue;
			}
			std::wstring_convert<std::codecvt_utf8<wchar_t>> converter; //http://stackoverflow.com/questions/17103925/how-well-is-unicode-supported-in-c11/17106065#17106065
			warn(L"[Stoicheck failure] stoicheck performed on \"" + converter.from_bytes(checked) + L"\" failed on char \"" + static_cast<wchar_t>(c) + L"\" [" + std::to_wstring(sgoto) + L']');
			return def;
		}
	}
	return stoi(checked);
}

const bool ScenarioParser::stoicheck(std::wstring &checked, int &number, int def)
{
	int type = 6; //(=) += -= *= /= %=
	if (checked.empty())
	{
		number = def;
		warn(L"[Stoicheck failure] stoicheck performed on an empty string [" + std::to_wstring(sgoto) + L']');
		return false;
	}
	bool minus = false;
	unsigned int ec = 0U;
	for (auto it = checked.begin(); it != checked.end(); ++it) {
		if (!isdigit(*it, utf8_locale))
		{
			if (checked[ec] == L'+' && checked[ec + 1U] == L'=')
			{
				type = 1;
				ec += 2U;
			}
			else if (checked[ec] == L'-' && checked[ec + 1U] == L'=')
			{
				type = 2;
				ec += 2U;
			}
			else if (checked[ec] == L'*' && checked[ec + 1U] == L'=')
			{
				type = 3;
				ec += 2U;
			}
			else if (checked[ec] == L'/' && checked[ec + 1U] == L'=')
			{
				type = 4;
				ec += 2U;
			}
			else if (checked[ec] == L'%' && checked[ec + 1U] == L'=')
			{
				type = 5;
				ec += 2U;
			}
			else if (checked[ec] == L'-')
			{
				minus = true;
				ec += 1U;
			}
			else if (checked[0] == 0xFEFF) //not sure if necessary
			{
				ec += 1U;
			}
			else if (checked[0] == 0xef && checked[1U] == 0xbb && checked[2U] == 0xbf)
			{
				ec += 3U;
			}
			else
			{
				number = def;
				warn(L"[Stoicheck failure] stoicheck performed on \"" + checked + L"\" failed on char \"" + *it + L"\" [" + std::to_wstring(sgoto) + L']');
				return false;
			}
			checked.erase(0U, ec);
		}
	}
	def = stoi(checked);
	if (minus) def = -def;
	switch (type)
	{
	case 1:
		number += def;
		break;
	case 2:
		number -= def;
		break;
	case 3:
		number *= def;
		break;
	case 4:
		number /= def;
		break;
	case 5:
		number %= def;
		break;
	default:
		number = def;
		break;
	}
	return true;
}

const bool ScenarioParser::stoicheck(std::wstring &checked, unsigned int &number, const int def)
{
	if (checked.empty())
	{
		number = def;
		warn(L"[Stoicheck failure] stoicheck performed on an empty string [" + std::to_wstring(sgoto) + L']');
		return false;
	}
	for (wchar_t c : checked) {
		if (!isdigit(c, utf8_locale))
		{
			if (checked[0] == 0xFEFF)
			{
				checked.erase(0U, 1U);
				continue;
			}
			else if (checked[0] == 0xef && checked[1] == 0xbb && checked[2] == 0xbf) //in linux it isn't necessary
			{
				checked.erase(0U, 3U);
				continue;
			}
			number = def;
			warn(L"[Stoicheck failure] stoicheck performed on \"" + checked + L"\" failed on char \"" + c + L"\" [" + std::to_wstring(sgoto) + L']');
			return false;
		}
	}
	number = stoi(checked);
	return true;
}

void ScenarioParser::Thingy(const int state, std::wstring &insert)
{
	if (insert.empty()) return;
	ssreload = true;
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
		size_t s_position = 0U;	
		if (insert.empty() || !(s_position = insert.find(L',')))
			throw w_err(L"[LoadingSave] Error: an/a \"" + name + L"\" with name \"" + (names[0].empty() ? L"unknown" : names[0]) +
				L"\" couldn't be loaded (missing argument or an empty argument) [" + std::to_wstring(sgoto) + L']');
		switch (arglist)
		{
		case 0:
			names[0] = insert.substr(0U, s_position);
			chName(names[0]);
			++namelist;
			break;
		case 1:	
			if (state == 2){
				names[1] = insert.substr(0U, s_position);
				++namelist;
			}
			else if (!stoicheck(insert.substr(0U, s_position), arguments[0])) throw w_err(L"[LoadingSave, Stat]Error: An/a " + name + L"\" failed its stoicheck on argument 1 [" + std::to_wstring(sgoto) + L']');
			break;
		default:
			if (!stoicheck(insert.substr(0U, s_position), arguments[arglist - 1])) throw w_err(L"[LoadingSave, Stat]Error: An/a " + name + L" with name \"" + names[0] + L"\" failed its stoicheck on argument " + std::to_wstring(arglist) + L" [" + std::to_wstring(sgoto) + L']');
			break;
		}
		insert.erase(0U, s_position + 1U);
	}
	if (arglist == arglistx)
	{
		if (!insert.empty())
		{
			if (state == 0) names[namelist] = insert.substr(0U, insert.size() - 1U);
			else if (!stoicheck(insert.substr(0U, insert.size() - 1U), arguments[arglist - namelist])) throw w_err(L"[LoadingSave, Stat]Error: An/a " + name + L" with name \"" + names[0] + L"\" failed its stoicheck on argument " + std::to_wstring(arglist - namelist) + L" [" + std::to_wstring(sgoto) + L']');
			insert.clear();
			if (state == 0) io_stats.push_back(IntStatOpposite(names[0], arguments[0], arguments[1], arguments[2], arguments[3], arguments[4], arguments[5], names[1]));
			else if (state == 1) i_stats.push_back(IntStat(names[0], arguments[0], arguments[1], arguments[2], arguments[3], arguments[4]));
			else if (state == 2) s_stats.push_back(StringStat(names[0], names[1], arguments[0], arguments[1], arguments[2]));
			else if (state == 3) Ints.push_back(Int(names[0], arguments[0], arguments[1], arguments[2]));
		}
		else throw w_err(L"[LoadingSave] Error: an/a \"" + name + L"\" with name \"" + names[0] + L"\" couldn't be loaded (last argument empty) [" + std::to_wstring(sgoto) + L']');
	}
	else if (arglist == 1) throw w_err(L"Error: could not load(missing arguments or stoicheck failure) an/a " + name + L" with name \"" + names[0] + L"\" [" + std::to_wstring(sgoto) + L']');
	else throw w_err(L"Error: could not load(missing arguments or stoicheck failure) an/a " + name + L" with missing name [" + std::to_wstring(sgoto) + L']');
}

void ScenarioParser::RoundRect()
{
	if (choice.back().text.getString().isEmpty()) return;
	sf::ConvexShape rrect;
	float X = 0, Y = 0, ratio = (w + h) / 1400.f;
	int radius = static_cast<int>(round(15.f * ratio));
	int rectHeight = static_cast<int>(round(choice.back().text.getGlobalBounds().height + (w + h) / 350.f));
	if (rectHeight < radius*2) rectHeight = radius*2;
	float add = radius / 15.f;
	int rectWidth = static_cast<int>(choice.back().text.getGlobalBounds().width + 1.5f * radius);
	sf::CircleShape cs(static_cast<float>(radius));
	cs.setFillColor(sf::Color(static_cast<sf::Uint8>(0), static_cast<sf::Uint8>(0), static_cast<sf::Uint8>(0), static_cast<sf::Uint8>(0))); //change the color
	cs.setOutlineThickness(round(2.f * ratio));
	cs.setOutlineColor(text.getFillColor());
	rrect.setPointCount(60);
	rrect.setOutlineThickness(round(2.f * (h + w) / 1400.f));
	rrect.setOutlineColor(text.getFillColor());
	rrect.setFillColor(sf::Color(static_cast<sf::Uint8>(0), static_cast<sf::Uint8>(0), static_cast<sf::Uint8>(0), static_cast<sf::Uint8>(0))); //change the color
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
	rrect.setPosition(round(choice.back().text.getGlobalBounds().left - choice.back().text.getLocalBounds().left - (w+h)/700.f), the);
	choice.back().text.setOrigin(round(choice.back().text.getLocalBounds().left + choice.back().text.getLocalBounds().width/2), round(choice.back().text.getLocalBounds().top + choice.back().text.getLocalBounds().height / 2));
	choice.back().text.setPosition(round(rrect.getPosition().x + rrect.getGlobalBounds().width/2.f), rrect.getPosition().y + rectHeight / 2);
	cs.setPosition(rrect.getPosition().x - round(cs.getGlobalBounds().width*1.2f), round(rrect.getGlobalBounds().top + (rectHeight - cs.getGlobalBounds().height)/2.f));
	choice.back().cs = cs;
	choice.back().c = rrect;
	the += static_cast<int>(rrect.getGlobalBounds().height);
}

const bool ScenarioParser::CommentCheck(std::wstring &insr)
{ 
	size_t bt;
	if ((bt = insr.find(comment)) != std::string::npos)
	{
		insr.erase(bt, std::string::npos);
		if (insr.empty()) return true;
	}
	return false;
}

const bool ScenarioParser::statfind(const std::wstring &name, int &val)
{
	for (auto &x : i_stats){
		if (name == x.name){
			val = x.value;
			return true;
		}
	}
	for (auto &x : io_stats){
		if (name == x.name){
			val = x.value;
			return true;
		}
	}
	for (auto &x : Ints){
		if (name == x.name){
			val = x.value;
			return true;
		}
	}
	return false;
}

const bool ScenarioParser::statfind(const std::wstring &name, std::wstring &val)
{
	for (auto &x : s_stats) {
		if (name == x.name) {
			val = x.value;
			return true;
		}
	}
	return false;
}

void ScenarioParser::CreateChoice()
{
	choice.push_back(Choice());
	std::wstring value;
	for (;;)
	{
		getline(insr);
		if (insr[0] == '#')
		{
			sf::Uint8 to3;
			int bt, val;
			if ((bt = insr.rfind(L"hidden ")) != std::wstring::npos)
				choice.back().hidden = (insr[8] == 'y');
			else {
				if ((bt = insr.rfind(L"==")) != std::wstring::npos) to3 = 2;
				else if ((bt = insr.rfind(L"<=")) != std::wstring::npos) to3 = 3;
				else if ((bt = insr.rfind(L">=")) != std::wstring::npos) to3 = 4;
				else if ((bt = insr.rfind(L"!=")) != std::wstring::npos) to3 = 5;
				else if ((bt = insr.rfind(L'>')) != std::wstring::npos) to3 = 0;
				else if ((bt = insr.rfind(L'<')) != std::wstring::npos) to3 = 1;
				else throw w_err(L"Improper choice command [" + std::to_wstring(sgoto) + L']');
				value = insr.substr(bt + (to3 > 1 ? 2U : 1U));
				value.pop_back();
				insr.erase(bt, std::wstring::npos);
				insr.erase(0U, 4U);
				if (choice.back().avaible)
				{
					if (!statfind(insr, bt))
					{
						std::wstring sval;
						if (!statfind(insr, sval)) throw w_err(L"Improper choice command [" + std::to_wstring(sgoto) + L']');
						else choice.back().avaible = (sval == value);
						continue;
					}
					else if (!stoicheck(value, val)) throw w_err(L"[Choice]FATAL stoicheck failure while evaluating \"#if\" result [" + std::to_wstring(sgoto) + L']');;
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
				}
			}
		}
		else if (choice.back().avaible || (!choice.back().avaible && !choice.back().hidden))
		{
			the += text.getCharacterSize();
			//if (debug) warn(L"[Choice]Searching for \"{\". If infinite loop occurs (program is stuck and yields no repsonse) you probably forgot to write \"}\" at the end of choice[" + sgoto + L']'); 
			bool first = true;
			for (std::wstring insrt;;)
			{
				if (!first) {
					getline(insr);
				}
				else first = false;
				if (CommentCheck(insr)) continue;
				//IfCheck(insr);
				if (insr.empty() || insr == L"\n")
					SplitText(true, insrt);
				else if (insr == empty)
				{
					insrt += L'\n';
					SplitText(true, insrt);
				}
				else if (insr.find(L'{') != std::wstring::npos)
				{
					choice.back().text.setFont(*text.getFont());
					choice.back().text.setCharacterSize(text.getCharacterSize());
					choice.back().text.setFillColor(text.getFillColor());
					choice.back().text.setPosition(w2, static_cast<float>(the));
					//choice.back().text.setFillColor(choice.back().avaible ? choice.back().text.getFillColor() : *textchoiceunavaiblecolor); //change the color 
					SplitText(true, insrt);
					RoundRect();
					choiceneed = true;
					choice.back().gto = sgoto;
					//if (debug) warn(L"[Choice]Searching for \"}\". If infinite loop occurs (program is stuck and yields no repsonse) you probably forgot to write \"}\" at the end of choice[" + sgoto + L']');
					for (int ssgoto = 1; ssgoto != 0;) {
						getline(insr);
						while (insr.find(L'{') != std::wstring::npos)
						{
							insr.erase(insr.find(L'{'), 1U);
							++ssgoto;
						}
						while (insr.find(L'}') != std::wstring::npos)
						{
							insr.erase(insr.find(L'}'), 1U);
							--ssgoto;
						}
					}
					choice.back().dgto = sgoto - 1;
					insr.clear();
					if (!choice.back().avaible) {
						choice.back().text.setFillColor(*textchoiceunavaiblecolor); choice.back().c.setOutlineColor(*textchoiceunavaiblecolor); choice.back().cs.setOutlineColor(*textchoiceunavaiblecolor);
					}
					return;
				}
				else if (insr[0] == L'\t') {
					if (!text.getString().isEmpty()) insrt += L'\n';
					insrt += insr;
					SplitText(true, insrt);
				}
				else {
					insrt += insr;
					if (formattype) SplitText(true, insrt);
					else insrt += L" ";
				} http://stackoverflow.com/questions/41353227/does-stdstring-char-expression-create-another-stdstring
				insr.clear();
			}
		}
		else {
			choice.pop_back();
			bool first = true;
			for (int ssgoto = 1; ssgoto != 0;) {
				getline(insr);
				while (insr.find(L'{') != std::wstring::npos)
				{
					insr.erase(insr.find(L'{'), 1U);
					if (!first) ++ssgoto;
					else first = false;
				}
				while (insr.find(L'}') != std::wstring::npos)
				{
					insr.erase(insr.find(L'}'), 1U);
					--ssgoto;
				}
			}
			insr.clear(); return;
		}
	}
}

bool ScenarioParser::chName(const std::wstring &name, bool fatal)
{	
	for (auto &x : s_stats){
		if (name == x.name){
			if (fatal) throw w_err(L"Error: there is a name conflict! There cannot be 2 variables with the same name(already exists one of type StringStat) \"" + name + L"\" [" + std::to_wstring(sgoto) + L']');
			else return true;
		}
	}
	for (auto &x : i_stats){
		if (name == x.name){
			if (fatal) throw w_err(L"Error: there is a name conflict! There cannot be 2 variables with the same name(already exists one of type IntStat) \"" + name + L"\" [" + std::to_wstring(sgoto) + L']');
			else return true;
		}
	}
	for (auto &x : io_stats){
		if (name == x.name){
			if (fatal) throw w_err(L"Error: there is a name conflict! There cannot be 2 variables with the same name(already exists one of type IntStatOpposite) \"" + name + L"\" [" + std::to_wstring(sgoto) + L']');
			else return true;
		}
	}
	for (auto &x : Ints){
		if (name == x.name){
			if (fatal) throw w_err(L"Error: there is a name conflict! There cannot be 2 variables with the same name(already exists one of type Int) \"" + name + L"\" [" + std::to_wstring(sgoto) + L']');
			else return true;
		}
	}
	return false;
}

void ScenarioParser::MergeText()
{
	if (tinsr.empty()) return;
	tinsr.pop_back();
	text.setString(tinsr);
	the += static_cast<int>(floor(text.getLocalBounds().top + text.getGlobalBounds().height + text.getCharacterSize()));
	tinsr.clear();
}

void ScenarioParser::Show_stats()
{
	sf::Text astat;
	sf::Color c = astat.getFillColor(); c.a = 0;
	astat.setFont(*text.getFont());
	int th = static_cast<int>(round(text.getCharacterSize() * 0.9f));
	she = static_cast<int>(1.4f * th);
	astat.setCharacterSize(th);
	for (int prior = priorlimit; prior >= 0; --prior)
	{
		for (auto &s : s_stats)
		{
			if (!s.read && s.prior == prior && !s.hidden)
			{
				s.t = astat;
				s.t.setString(s.name + L": ");
				if (!s.vhidden) s.t.setString(s.t.getString() + s.value);
				s.t.setOrigin(0, round(s.t.getLocalBounds().top));
				s.t.setPosition(round(w / 12.f), static_cast<float>(she));
				s.pos = static_cast<sf::Vector2i>(s.t.getPosition());
				she += static_cast<int>(round(th * 1.25f));
				s.read = true;
			}
		}
		for (auto &i : io_stats)
		{
			if (!i.read && i.prior == prior && !i.hidden)
			{
				astat.setFillColor(statcolor);
				astat.setStyle(sf::Text::Bold);
				for (auto &t : i.t) t = astat;
				i.t[0].setString(i.name);
				i.t[0].setOrigin(0, round(i.t[0].getLocalBounds().top + i.t[0].getLocalBounds().height / 2.f));

				i.t[1].setString(i.opposite);
				i.t[1].setOrigin(1, round(i.t[1].getLocalBounds().top + i.t[1].getLocalBounds().height / 2.f));

				i.t[2].setString(std::to_wstring(i.value));
				i.t[2].setOrigin(2, round(i.t[2].getLocalBounds().top + i.t[2].getLocalBounds().height / 2.f));

				astat.setFillColor(c);
				astat.setStyle(sf::Text::Regular);

				i.setSprite(IOStatspecial(static_cast<int>(round(w / 1.45f)), static_cast<int>(round(th * 1.2f)), i.value, i.min, i.max, i.threshold));
				i.s.setPosition(round(w / 12.f), static_cast<float>(she));
				i.s.setColor(sf::Color(255, 255, 255, 0));
				i.pos[3] = sf::Vector2i(static_cast<int>(round(w / 12.f)), static_cast<int>(i.s.getPosition().y));

				float y = round(i.s.getPosition().y + i.s.getGlobalBounds().height / 2.f);
				she += static_cast<int>(round(th * 1.65f));
				i.read = true;

				i.t[0].setPosition(round(w / 11.f), y);
				i.pos[0] = static_cast<sf::Vector2i>(i.t[0].getPosition());
				float x = i.t[0].getGlobalBounds().left + i.t[0].getGlobalBounds().width; //i.t[0].getGlobalBounds().left + i.t[0].getGlobalBounds().width double times looks rather bad
				i.t[1].setPosition(round(i.s.getGlobalBounds().left + i.s.getGlobalBounds().width - (w / 11.f - w / 12.f) - i.t[1].getGlobalBounds().width), y);
				i.pos[1] = static_cast<sf::Vector2i>(i.t[1].getPosition());
				i.t[2].setPosition(round(x  + (i.t[1].getGlobalBounds().left - x - i.t[2].getGlobalBounds().width) / 2.f), y);
				i.pos[2] = static_cast<sf::Vector2i>(i.t[2].getPosition());
			}
		}
		for (auto &i : i_stats)
		{
			if (!i.read && i.prior == prior && !i.hidden)
			{
				astat.setFillColor(statcolor);
				astat.setStyle(sf::Text::Bold);
				int arg[3] = { i.value, i.min, i.max };
				if (arg[1] < 0)
				{
					arg[0] -= arg[1];
					arg[2] -= arg[1];
					arg[1] = 0;
				}
				i.t = astat;
				i.t.setString(i.name + L": " + std::to_wstring(static_cast<int>(round(arg[0] * 100.f / arg[2]))) + L"%");
				i.t.setOrigin(0, round(i.t.getLocalBounds().top + i.t.getLocalBounds().height / 2.f));
				i.setSprite(IntSpecial(static_cast<int>(round(w / 1.45f)), static_cast<int>(round(th * 1.2f)), arg[0], arg[1], arg[2]));
				i.s.setPosition(round(w / 12.f), static_cast<float>(she));
				i.s.setColor(sf::Color(255, 255, 255, 0));
				i.pos[1] = sf::Vector2i(static_cast<int>(round(w / 12.f)), static_cast<int>(i.s.getPosition().y));
				i.t.setPosition(round(w / 11.f), round(i.s.getPosition().y + i.s.getGlobalBounds().height / 2.f));
				i.pos[0] = static_cast<sf::Vector2i>(i.t.getPosition());

				astat.setFillColor(c);
				astat.setStyle(sf::Text::Regular);

				she += static_cast<int>(round(th *1.65f));
				i.read = true;
			}
		}
		for (auto &i : Ints)
		{
			if (!i.read && i.prior == prior && !i.hidden)
			{
				i.t = astat;
				i.t.setString(i.name + L": " + std::to_wstring(i.value));
				i.t.setOrigin(0,round(i.t.getLocalBounds().top));
				i.t.setPosition(round(w / 12.f), static_cast<float>(she));
				i.pos = static_cast<sf::Vector2i>(i.t.getPosition());
				she += static_cast<int>(round(th * 1.25f));
				i.read = true;
			}
		}
	}
	for (auto &s : s_stats) s.read = false;
	for (auto &i : io_stats) i.read = false;
	for (auto &i : i_stats) i.read = false;
	for (auto &i : Ints) i.read = false;
	ssreload = false;
}

const sf::Image ScenarioParser::IOStatspecial(const int w, const int h, int value, int min, int max, int threshold)
{
	sf::Image img;
	img.create(w, h);
	if (min < 0)
	{
		value -= min;
		max -= min;
		threshold -= min;
		min = 0;
	}
	//the number of certain pixels
	int valuepos;
	if (value > threshold)
		valuepos = static_cast<int>(round(w * (0.5f + (0.5f * (value - threshold)) / (max - threshold))));
	else valuepos = static_cast<int>(round(w * (value/static_cast<float>(2*threshold))));
	//manages the number of needed pixels to create image
	int x = 0;
	while (x < valuepos)
	{
		for (int y = 0; y < h; ++y)
		{
			img.setPixel(x, y, statgaincolor);
		}
		++x;
	}
	while (x < w)
	{
		for (int y = 0; y < h; ++y)
		{
			img.setPixel(x, y, statoppositecolor);
		}
		++x;
	}
	return img; //w razie lagów zastosować skalowanie = in case of lags use setScale()
}

const sf::Image ScenarioParser::IntSpecial(const int w, const int h, int value, int min, int max)
{
	sf::Image img;
	img.create(w, h);
	//the number of certain pixels
	int valuepos = static_cast<int>(round(w * static_cast<float>(value) / max));
	//manages the number of needed pixels to create image
	int x = 0;
	while (x < valuepos)
	{
		for (int y = 0; y < h; ++y)
		{
			img.setPixel(x, y, statgaincolor);
		}
		++x;
	}
	while (x < w)
	{
		for (int y = 0; y < h; ++y)
		{
			img.setPixel(x, y, statlosscolor);
		}
		++x;
	}
	return img; //w razie lagów zastosować skalowanie = in case of lags use setScale()
}

void ScenarioParser::IfCheck(std::wstring &insr)
{
	int bt;
	if ((bt = insr.find(L"#if(")) != std::wstring::npos)
	{
		insr.erase(bt, 4U);
		std::wstring name, value;
		size_t to3, val;
		bool IF = false;
		if ((val = insr.find(L"==", bt)) != std::wstring::npos) to3 = 2;
		else if ((val = insr.find(L"<=", bt)) != std::wstring::npos) to3 = 3;
		else if ((val = insr.find(L">=", bt)) != std::wstring::npos) to3 = 4;
		else if ((val = insr.find(L"!=", bt)) != std::wstring::npos) to3 = 5;
		else if ((val = insr.find(L'>', bt)) != std::wstring::npos) to3 = 0;
		else if ((val = insr.find(L'<', bt)) != std::wstring::npos) to3 = 1;
		else throw w_err(L"Improper \"if\" command [" + std::to_wstring(sgoto) + L']');
		name = insr.substr(bt, val - bt);
		insr.erase(bt, (to3 > 1 ? 2U : 1U) + name.size() - bt);
		value = insr.substr(bt, val = insr.find(L')', bt) - bt);
		insr.erase(bt, 1U + value.size() - bt);
		int cval = 0;
		if (!statfind(name, cval))
		{
			std::wstring sval;
			if (!statfind(name, sval)) throw w_err(L"Couldnt find a stat with name " + name +  L" [" + std::to_wstring(sgoto) + L']');
			else IF = (sval == value);
		}
		else
		{
			if (!stoicheck(value, val)) throw w_err(L"[Choice]FATAL stoicheck failure while evaluating \"#if\" result [" + std::to_wstring(sgoto) + L']');;
			switch (to3)
			{
			case 0:
				IF = (cval> val);
				break;
			case 1:
				IF = (cval < val);
				break;
			case 2:
				IF = (cval == val);
				break;
			case 3:
				IF = (cval <= val);
				break;
			case 4:
				IF = (cval >= val);
				break;
			case 5:
				IF = (cval != val);
				break;
			}
		}
		if (IF && formattype)
		{
			std::wstring str;
			if (insr.find(L'{', bt) == std::wstring::npos) str = insr.substr(bt);
			else str = insr.substr(bt, insr.find(L'{', bt) - bt);
			insr.erase(str.size());
			SplitText(false, str);
		}
		while (value.find(L'{') == std::wstring::npos)
		{
			if (value[0U] == L'#' && value.substr(0U, 7U) == L"#choice") 
				throw w_err(L"FATAL ERROR: There should be nothing between \"#if\" command and its \"{\", writing #choice there is a grievous mistake");
			getline(value);
		}
		value.erase(0U, bt + 1U);
		insr += value;
		insr += L'\n';
		while (value.find(L'}') == std::wstring::npos)
		{
			if (value[0U] == L'#')
			{
				if (IF) ExecuteCommand(value);
				else if (value.substr(0U, 7U) == L"#choice") {
					while (!value.find(L'}')) {
						getline(value);
					}
				}
			}
			else if (IF)
			{
				if (formattype) SplitText(false, insr);
				insr += value;
				insr += L'\n';
			}
		}
		//if (formattype) SplitText(false, insr);
		//insr += value;
		//insr += L'\n';
		insr.erase(insr.find(L'}'), 1U);
		if (formattype && IF) SplitText(false, insr);
	}
}

void ScenarioParser::ParseMainBody()
{
	std::wstring preinsr;
	preinsr.reserve(200);
	bool first = true;
	for (;;)
	{
		if (dgoto != 0 && sgoto >= dgoto) { SplitText(false, insr); break; }
		getline(preinsr);
		if (first)
		{
			if (preinsr[0] == 0xFEFF) preinsr.erase(0U, 1U);
			else if (preinsr[0] == 0xef && preinsr[1] == 0xbb && preinsr[2] == 0xbf) preinsr.erase(0U, 3U);
			first = false;
		}
		if (CommentCheck(preinsr)) continue;
		//IfCheck(preinsr);
		if (preinsr[0] == '#')
		{
			if (preinsr == L"#end")
			{
				SplitText(false, insr);
				MergeText();
				break;
			}
			else if (preinsr == L"#next") //!debug, will end after constructor
			{
				SplitText(false, insr);
				MergeText();
				next.setPosition(round(w / 2 - next.getGlobalBounds().width / 2.f), round(the + next.getGlobalBounds().height / 2.f));
				the += static_cast<int>(round(next.getGlobalBounds().height * 1.6f));
				drawnext = true;
				break;
			}
			else if (preinsr.substr(0U, 6U) == L"#goto(")
			{
				int line;
				if (stoicheck(preinsr.substr(6U, preinsr.size() - 7U), line)) GotoLine(line - 1);
				else throw w_err(L"\"#goto\" command's stoicheck failure! Check if you didn't use a letter or if you put too many non-digit characters [" + std::to_wstring(sgoto) + L']');
				dgoto = 0;
				continue;
			}
			else ExecuteCommand(preinsr);
			continue;
		}
		if (preinsr.empty() || preinsr == L"\n")
			SplitText(false, insr);
		else if (preinsr == empty)
		{
			insr += L'\n';
			SplitText(false, insr);
		}
		else if (preinsr[0] == L'\t') {
			if (!text.getString().isEmpty()) insr += L'\n';
			insr += preinsr;
			SplitText(false, insr);
		}
		else if (preinsr == split) formattype = !formattype;
		else {
			insr += preinsr;
			if (formattype) SplitText(false, insr);
			else insr += L" ";
		}
	}
	MergeText();
}

void ScenarioParser::getline(std::wstring &preinsr)
{
	std::getline(in, preinsr);
	++sgoto;
}

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
#include <algorithm>
extern unsigned int priorlimit;
constexpr wchar_t* const split = L"`/`"; //Add an option to change it, for user preference
const size_t split_l = std::wcslen(split);
constexpr wchar_t* const comment = L"//"; //Add an option to change it, for user preference
constexpr wchar_t* const empty = L"`"; //Add an option to change it, for user preference
//todo: add type function, add achievements, add custom texts, add gain text//change the colors
//todo: naprawić ifcheck()
void ScenarioParser::GotoLine(const int num)
{
	in.seekg(std::wifstream::beg);
	for (int i = 0U; i < num; ++i){
		in.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
	}
	cgoto = sgoto = num;
}

void ScenarioParser::Parse()
{
	PlayerTurn = choiceneed = DrawNext = false;
	choice.clear();
	typeboxes.clear();
	tinsr.clear();
	text.setString(L"");
	slideratv = false;
	dmargin = *h / 12;
	typesel = choicesel = -1;
	if (pempty)
	{
		text.setPosition(round(*w / 24.f), static_cast<float>(dmargin));
		text.setString("Unable to save the game.\nAdd at least one profile.");
		return;
	}
	else if (sempty)
	{
		text.setPosition(round(*w / 24.f), static_cast<float>(dmargin));
		text.setString("Unable to save the game.\nAdd at least one story.");
		return;
	}
	in.open(path);
	if (!in) throw w_err(L"File that contains story couldn't be open [" + std::to_wstring(sgoto) + L']');
	in.imbue(utf8_locale);
	ScanForWaypoints();
	GotoLine(cgoto);
	ParseMainBody();
	in.close();
	scrolltimes = static_cast<int>(round((dmargin - *h) / (100.f *(*w + *h) / 1400.f)));
	if (!Debug) {
		loadtextonly = true;
		Save();
	}
	if (dmargin > *h) slideratv = true;
	if (ssreload) Show_stats();
}

void ScenarioParser::Save()
{
	if (sempty || pempty || Debug) return;
	std::wofstream save(savefile);
	save.imbue(utf8_locale);
	if (save)
	{
		save << cgoto << std::endl;
		save << dgoto << std::endl;
		save << static_cast<int>(loadtextonly) << std::endl;
		save << path << std::endl;
		save << '}' << std::endl;

		for (auto &x : io_stats) save << x.second.name << ',' << x.second.value << ',' << x.second.max << ',' << x.second.min << ',' << x.second.threshold << ',' << x.second.hidden << ',' << x.first << ',' << x.second.opposite << std::endl;
		save << '}' << std::endl;

		for (auto &x : i_stats) save << x.second.name << ',' << x.second.value << ',' << x.second.max << ',' << x.second.min << ',' << x.second.hidden << ',' << x.first << std::endl;
		save << '}' << std::endl;

		for (auto &x : s_stats) save << x.second.name << ',' << x.second.value << ',' << x.second.hidden << ',' << x.second.vhidden << ',' << x.first << std::endl;
		save << '}' << std::endl;

		for (auto &x : Ints) save << x.second.name << ',' << x.second.value << ',' << x.second.hidden << ',' << x.first << std::endl;
		save << '}' << std::endl;
	}
	else throw w_err(L"Error: Couldn't load save [while saving]: missing file or invalid path \"" + savefile + L"\" [" + std::to_wstring(sgoto) + L']');
	SaveStcs();
}

void ScenarioParser::SaveStcs()
{
	std::wofstream save(ScenarioParser::apath + L"\\Stc.txt");
	save.imbue(utf8_locale);
	if (save)
	{
		for (auto &x : stc_i) save << x.name << ',' << x.value << std::endl;
		save << '}' << std::endl;

		for (auto &x : stc_s) save << x.name << ',' << x.value << std::endl;
		//save << '}' << std::endl;
	}
	else throw w_err(L"Static Stats couldn't be loaded, maybe game needs administrator privileges \"" + savefile + L"\" [" + std::to_wstring(sgoto) + L']');
}

void ScenarioParser::ExecuteCommand(std::wstring &insrtttt)
{
	auto CCommand = [&insrtttt](const wchar_t command[])->bool
	{
		if (insrtttt.find(command) == 0U) {
			insrtttt.erase(0U, std::wcslen(command));
			insrtttt.erase(insrtttt.find(L')'));
			return true;
		}
		return false;
	};
	if (insrtttt.find(L"#choice") == 0U)
	{
		if (insrtttt.size() > 7U)
		{
			std::wstring arg = insrtttt.substr(8U, insrtttt.size()-9U);
			stoiCheck(arg, ttignore);
		}
		SplitText(false, insr);
		MergeText();
		CreateChoice();
	}
	else if (CCommand(L"#enter("))
	{
		std::wstring name = insrtttt.substr(0U, insrtttt.find(L','));
		insrtttt.erase(0U, insrtttt.find(L',') + 1U);
		std::pair<unsigned, unsigned> limits; 
		stoiCheck(insrtttt.substr(0U, insrtttt.find(L',')), limits.first);
		stoiCheck(insrtttt.substr(insrtttt.find(L',') + 1), limits.second);
		std::wstring *type = &FindSStat(name)->value;
		if (!FindSStat(name)) warn(L"Error! TypeBox hasn't been created. There's no such a Stat with name \"" + insrtttt + L"\" [" + std::to_wstring(sgoto) + L']');
		else
		{
			typeboxes.push_back(TypeBox(type, limits));
			SplitText(false, insr);
			MergeText();
			CreateTypeBox();
		}
	}
	else if (CCommand(L"#gt("))
	{
		CreateGainText();
	}
	else if (insrtttt == L"#debug")
	{
		Debug = true;
		std::wofstream save(savefile);
		dgoto = cgoto = 0;
		loadtextonly = false;
	}
	else if (insrtttt == L"#showstats") //it will be changed so stats will appear
	{

	}
	else if (CCommand(L"#t("))
	{
		stoiCheck(insrtttt, ttignore);
	}
	else if (CCommand(L"#piorlimit("))
	{
		if (stoiCheck(insrtttt, priorlimit)) throw w_err(L"FATAL stoicheck failure while exectuing \"#priorlimit\" command [" + std::to_wstring(sgoto) + L']');
	}
	else if (!loadtextonly)
	{
		if (CCommand(L"#IntStatOpposite(")) Thingy(0, insrtttt);
		else if (CCommand(L"#IntStat(")) Thingy(1, insrtttt);
		else if (CCommand(L"#StringStat(")) Thingy(2, insrtttt);
		else if (CCommand(L"#Int(")) Thingy(3, insrtttt);
		else if (CCommand(L"#set("))
		{
			size_t n;
			n = Pfind(insrtttt, L',');
			std::wstring name = insrtttt.substr(0U, n);
			insrtttt.erase(0U, n);
			std::wstring value = insrtttt.substr(1U);
			insrtttt.erase(0U, n);
			if (auto x = FindIStatO(name))
			{
				if (!stoiCheck(value, x->value)) if (!FindInt(value, x->value)) throw w_err(L"FATAL stoicheck failure while exectuing \"#set\" command(1st argument) [" + std::to_wstring(sgoto) + L']');

				if ((n = insrtttt.find(L',')) == std::wstring::npos) goto iocalc;
				value = insrtttt.substr(0U, n);
				insrtttt.erase(0U, n);
				if (!stoiCheck(value, x->min)) throw w_err(L"FATAL stoicheck failure while exectuing \"#set\" command(2nd argument) [" + std::to_wstring(sgoto) + L']');

				if ((n = insrtttt.find(L',')) == std::wstring::npos) goto iocalc;
				value = insrtttt.substr(0U, n);
				insrtttt.erase(0U, n);
				if (!stoiCheck(value, x->max)) throw w_err(L"FATAL stoicheck failure while exectuing \"#set\" command(3nd argument) [" + std::to_wstring(sgoto) + L']');

				if ((n = insrtttt.find(L',')) == std::wstring::npos) goto iocalc;
				value = insrtttt.substr(0U, n);
				if (!stoiCheck(value, x->threshold)) throw w_err(L"FATAL stoicheck failure while exectuing \"#set\" command(4nd argument) [" + std::to_wstring(sgoto) + L']');
			iocalc:
				x->t[2].setString(std::to_wstring(x->value));
				x->t[2].setOrigin(2, round(x->t[2].getLocalBounds().top + x->t[2].getLocalBounds().height / 2.f));
				x->setSprite(IOStatspecial(static_cast<int>(round(*w / 1.45f)), x->s.getGlobalBounds().height, x->value, x->min, x->max, x->threshold));
				x->t[2].setPosition(static_cast<sf::Vector2f>(x->pos[2]));
			}
			else if (auto x = FindIStat(name))
			{
				if (!stoiCheck(value, x->value)) if (!FindInt(value, x->value)) throw w_err(L"FATAL stoicheck failure while exectuing \"#set\" command(1st argument) [" + std::to_wstring(sgoto) + L']');

				if ((n = insrtttt.find(L',')) == std::wstring::npos) goto icalc;
				value = insrtttt.substr(0U, n);
				insrtttt.erase(0U, n);
				if (!stoiCheck(value, x->min)) throw w_err(L"FATAL stoicheck failure while exectuing \"#set\" command(2nd argument) [" + std::to_wstring(sgoto) + L']');

				if ((n = insrtttt.find(L',')) == std::wstring::npos) goto icalc;
				value = insrtttt.substr(0U, n);
				if (!stoiCheck(value, x->max)) throw w_err(L"FATAL stoicheck failure while exectuing \"#set\" command(3nd argument) [" + std::to_wstring(sgoto) + L']');
			icalc:
				int arg[3] = { x->value, x->min, x->max };
				if (arg[1] < 0)
				{
					arg[0] -= arg[1];
					arg[2] -= arg[1];
					arg[1] = 0;
				}
				x->t.setString(x->name + L": " + std::to_wstring(static_cast<int>(round(arg[0] * 100.f / arg[2]))) + L"%");
				x->t.setOrigin(0, round(x->t.getLocalBounds().top + x->t.getLocalBounds().height / 2.f));
				x->setSprite(IntSpecial(static_cast<int>(round(*w / 1.45f)), x->s.getGlobalBounds().height, arg[0], arg[1], arg[2]));
				x->t.setPosition(static_cast<sf::Vector2f>(x->pos[0]));
			}
			else if (auto x = FindInt(name))
			{
				if (!stoiCheck(value, x->value)) if (!FindInt(value, x->value)) throw w_err(L"FATAL stoicheck failure while exectuing \"#set\" command(1st argument) [" + std::to_wstring(sgoto) + L']');
				x->t.setString(x->name + L": " + std::to_wstring(x->value));
				x->t.setOrigin(0, round(x->t.getLocalBounds().top));
				x->t.setPosition(static_cast<sf::Vector2f>(x->pos));
			}
			else if (auto x = FindSStat(name))
			{
					if (value[0] != L'$' || !FindString(value, x->value))
						x->value = value;
					x->t.setString(x->name + L": ");
					if (!x->vhidden) x->t.setString(x->t.getString() + x->value);
					x->t.setOrigin(0, round(x->t.getLocalBounds().top));
					x->t.setPosition(static_cast<sf::Vector2f>(x->pos));
			}
			else if (auto x = FindStcI(name))
				if (!stoiCheck(value, x->value)) if (!FindInt(value, x->value)) throw w_err(L"FATAL stoicheck failure while exectuing \"#set\" command(1st argument) [" + std::to_wstring(sgoto) + L']');
			else if (auto x = FindStcS(name))
				if (!FindString(value, x->value)) x->value = value;
		}
		else if (CCommand(L"#hide("))
		{
			if (auto x = FindIStat(insrtttt)) x->hidden = !x->hidden;
			if (auto x = FindIStatO(insrtttt)) x->hidden = !x->hidden;
			if (auto x = FindSStat(insrtttt)) x->hidden = !x->hidden;
			if (auto x = FindInt(insrtttt)) x->hidden = !x->hidden;
		}
		else if (CCommand(L"#vhide("))
		{
			if (StringStat *x = FindSStat(insrtttt))
			{
				x->vhidden = !x->vhidden;
				x->t.setString(x->name + L": ");
				if (!x->vhidden) x->t.setString(x->t.getString() + x->value);
				x->t.setOrigin(0, round(x->t.getLocalBounds().top));
				x->t.setPosition(static_cast<sf::Vector2f>(x->pos));
			}
		}
		else if (CCommand(L"#prior(")) //Setting prior is harder in multimap, but I think it is still better for performance to switch from vector (watch Show_Stats())
		{
			size_t n;
			n = Pfind(insrtttt, L',');
			std::wstring name = insrtttt.substr(0U, n);
			insrtttt.erase(0U, n);
			int val;
			if (!stoiCheck(insrtttt.substr(n), val) || val < 0) throw w_err(L"FATAL stoicheck failure or value is below 0 while exectuing \"#prior\" command [" + std::to_wstring(sgoto) + L']');
			for (auto x = i_stats.begin(); x != i_stats.end(); ++x)
				if (insrtttt == x->second.name)
				{
					auto copy = x->second;
					i_stats.erase(x);
					i_stats.emplace(val, copy);
					return;
				}
		}
		else if (CCommand(L"#Stc("))
		{
			size_t n;
			if ((n = insrtttt.find(L',')) == std::wstring::npos) throw w_err(L"\"#stc\" command needs 2 arguments, not one or none [" + std::to_wstring(sgoto) + L']');;
			std::wstring name = insrtttt.substr(0U, n);
			if (checkName(name)) return;
			std::wstring value = insrtttt.substr(n + 1U, insrtttt.size() - 1U - n);
			int val;
			if (stoiCheck(value, val)) stc_i.emplace_back(name, val);
			else stc_s.emplace_back(name, value);
		}
		else if (CCommand(L"#erase("))
		{
			for (auto x = i_stats.begin(); x != i_stats.end(); ++x) {
				if (insrtttt == x->second.name){
					i_stats.erase(x);
					return;
				}
			}

			for (auto x = io_stats.begin(); x != io_stats.end(); ++x) {
				if (insrtttt == x->second.name) {
					io_stats.erase(x);
					return;
				}
			}

			for (auto x = Ints.begin(); x != Ints.end(); ++x) {
				if (insrtttt == x->second.name) {
					Ints.erase(x);
					return;
				}
			}

			for (auto x = s_stats.begin(); x != s_stats.end(); ++x) {
				if (insrtttt == x->second.name) {
					s_stats.erase(x);
					return;
				}
			}
			for (auto x = stc_i.begin(); x != stc_i.end(); ++x) {
				if (insrtttt == x->name) {
					stc_i.erase(x);
					return;
				}
			}	

			for (auto x = stc_s.begin(); x != stc_s.end(); ++x) {
				if (insrtttt == x->name) {
					stc_s.erase(x);
					return;
				}
			}
		}
		else if (CCommand(L"file("))
		{
			path = L"../../bin/Scripts/" + insrtttt;
			in.open(path);
			cgoto = sgoto = dgoto = 0;
			choicesel = -1;
		}
		else if (Debug) w_err(L"Unknown command: " + insrtttt + L'[' + std::to_wstring(sgoto) + L']');
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
		if (!insrt.substr(0U, d).empty()) SplitText(w, insrt.substr(0U, d));
		insrt.erase(0U, d+1);
	}
	sf::Text tekst = w ? choice.back().text : text;
	tekst.setString(insrt);
	if ((tekst.getLocalBounds().left + tekst.getGlobalBounds().left + tekst.getGlobalBounds().width) < static_cast<float>(rmargin) || insrt.find(L' ') == std::wstring::npos) str = insrt + L'\n';
	else
	{
		for (size_t pos = 0U;;) {
			pos = insrt.find(L' ', pos + 1U);
			tekst.setString(insrt.substr(0U, pos));
			if ((tekst.getLocalBounds().left + tekst.getGlobalBounds().left + tekst.getGlobalBounds().width) > rmargin)
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

const int ScenarioParser::stoiCheck(std::string &checked, const int def)
{
	if (checked.empty())
	{
		if (Debug) warn(L"[Stoicheck failure] stoicheck performed on an empty string [" + std::to_wstring(sgoto) + L']');
		return def;
	}
	for (char c : checked){
		if (!isdigit(c, utf8_locale))
		{
			if (checked[0] == 0xFEFF)
			{
				checked.erase(0U);
				continue;
			}
			else if (checked[0] == 0xef && checked[1] == 0xbb && checked[2] == 0xbf)
			{
				checked.erase(0U, 3U);
				continue;
			}
			std::wstring_convert<std::codecvt_utf8<wchar_t>> converter; //http://stackoverflow.com/questions/17103925/how-well-is-unicode-supported-in-c11/17106065#17106065
			if (Debug) warn(L"[Stoicheck failure] stoicheck performed on \"" + converter.from_bytes(checked) + L"\" failed on char \"" + static_cast<wchar_t>(c) + L"\" [" + std::to_wstring(sgoto) + L']');
			return def;
		}
	}
	return stoi(checked);
}

const bool ScenarioParser::stoiCheck(const std::wstring& checked, int &number, int def)
{
	int type = 6; //(=) += -= *= /= %=
	if (checked.empty())
	{
		number = def;
		if (Debug) warn(L"[Stoicheck failure] stoicheck performed on an empty string [" + std::to_wstring(sgoto) + L']');
		return false;
	}
	bool minus = false;
	unsigned int ec = 0U;
	while (!isdigit(checked[ec], utf8_locale))
	{
		if (checked[ec] == L'+' && checked[ec + 1U] == L'=') {
			type = 1;
			ec += 2U;
		}
		else if (checked[ec] == L'-' && checked[ec + 1U] == L'=') {
			type = 2;
			ec += 2U;
		}
		else if (checked[ec] == L'*' && checked[ec + 1U] == L'=') {
			type = 3;
			ec += 2U;
		}
		else if (checked[ec] == L'/' && checked[ec + 1U] == L'=') {
			type = 4;
			ec += 2U;
		}
		else if (checked[ec] == L'%' && checked[ec + 1U] == L'=') {
			type = 5;
			ec += 2U;
		}
		else if (checked[ec] == L'-') {
			minus = true;
			ec += 1U;
		}
		else if (checked[0] == 0xFEFF) ec += 1U; //not sure if necessary, I think the second one recognizes BOM correctly
		else if (checked[0] == 0xef && checked[1U] == 0xbb && checked[2U] == 0xbf) ec += 3U;
		else {
			number = def;
			if (Debug) warn(L"[Stoicheck failure] stoicheck performed on \"" + checked + L"\" failed on char \"" + checked[ec] + L"\" [" + std::to_wstring(sgoto) + L']');
			return false;
		}
	}
	if (ec != 0) def = stoi(checked.substr(ec)); //performance
	else def = stoi(checked);
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

const bool ScenarioParser::stoiCheck(std::wstring &checked, unsigned int &number, const int def)
{
	if (checked.empty())
	{
		number = def;
		if (Debug) warn(L"[Stoicheck failure] stoicheck performed on an empty string [" + std::to_wstring(sgoto) + L']');
		return false;
	}
	for (wchar_t c : checked) {
		if (!isdigit(c, utf8_locale))
		{
			if (checked[0] == 0xFEFF)
			{
				checked.erase(0U);
				continue;
			}
			else if (checked[0] == 0xef && checked[1] == 0xbb && checked[2] == 0xbf) //in linux it isn't necessary
			{
				checked.erase(0U, 3U);
				continue;
			}
			number = def;
			if (Debug) warn(L"[Stoicheck failure] stoicheck performed on \"" + checked + L"\" failed on char \"" + c + L"\" [" + std::to_wstring(sgoto) + L']');
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
			checkName(names[0]);
			++namelist;
			break;
		case 1:	
			if (state == 2){
				names[1] = insert.substr(0U, s_position);
				++namelist;
			}
			else if (!stoiCheck(insert.substr(0U, s_position), arguments[0])) throw w_err(L"[LoadingSave, Stat]Error: An/a " + name + L"\" failed its stoicheck on argument 1 [" + std::to_wstring(sgoto) + L']');
			break;
		default:
			if (!stoiCheck(insert.substr(0U, s_position), arguments[arglist - 1])) throw w_err(L"[LoadingSave, Stat]Error: An/a " + name + L" with name \"" + names[0] + L"\" failed its stoicheck on argument " + std::to_wstring(arglist) + L" [" + std::to_wstring(sgoto) + L']');
			break;
		}
		insert.erase(0U, s_position + 1U);
	}
	if (arglist == arglistx)
	{
		if (!insert.empty())
		{
			if (state == 0) names[namelist] = insert;
			else if (!stoiCheck(insert, arguments[arglist - namelist])) throw w_err(L"[LoadingSave, Stat]Error: An/a " + name + L" with name \"" + names[0] + L"\" failed its stoicheck on argument " + std::to_wstring(arglist - namelist) + L" [" + std::to_wstring(sgoto) + L']');
			insert.clear();
			if (state == 0) io_stats.emplace(arguments[5], IntStatOpposite(names[0], arguments[0], arguments[1], arguments[2], arguments[3], arguments[4], names[1]));
			else if (state == 1) i_stats.emplace(arguments[4], IntStat(names[0], arguments[0], arguments[1], arguments[2], arguments[3]));
			else if (state == 2) s_stats.emplace(arguments[2], StringStat(names[0], names[1], arguments[0], arguments[1]));
			else if (state == 3) Ints.emplace(arguments[2], Int(names[0], arguments[0], arguments[1]));
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
	float X = 0, Y = 0, ratio = (*w + *h) / 1400.f;
	int radius = static_cast<int>(round(15.f * ratio));
	int rectHeight = static_cast<int>(round(choice.back().text.getGlobalBounds().height + (*w + *h) / 350.f));
	if (rectHeight < radius*2) rectHeight = radius*2;
	float add = radius / 15.f;
	int rectWidth = static_cast<int>(choice.back().text.getGlobalBounds().width + 1.5f * radius);
	sf::CircleShape cs(static_cast<float>(radius));
	cs.setFillColor(sf::Color(static_cast<sf::Uint8>(0), static_cast<sf::Uint8>(0), static_cast<sf::Uint8>(0), static_cast<sf::Uint8>(0))); //change the color
	cs.setOutlineThickness(round(2.f * ratio));
	cs.setOutlineColor(text.getFillColor());
	rrect.setPointCount(60);
	rrect.setOutlineThickness(round(2.f * (*h + *w) / 1400.f));
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
	rrect.setPosition(round(choice.back().text.getGlobalBounds().left - choice.back().text.getLocalBounds().left - (*w+*h)/700.f), static_cast<float>(dmargin));
	choice.back().text.setOrigin(round(choice.back().text.getLocalBounds().left + choice.back().text.getLocalBounds().width/2), round(choice.back().text.getLocalBounds().top + choice.back().text.getLocalBounds().height / 2));
	choice.back().text.setPosition(round(rrect.getPosition().x + rrect.getGlobalBounds().width/2.f), rrect.getPosition().y + rectHeight / 2);
	cs.setPosition(rrect.getPosition().x - round(cs.getGlobalBounds().width*1.2f), round(rrect.getGlobalBounds().top + (rectHeight - cs.getGlobalBounds().height)/2.f));
	choice.back().cs = cs;
	choice.back().c = rrect;
	dmargin += static_cast<int>(rrect.getGlobalBounds().height);
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

void ScenarioParser::CreateChoice()
{
	choice.emplace_back();
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
			else if (insr.substr(0U, 4U) == L"#if(") {
				insr.erase(0U, 4U); insr.pop_back();
				if ((bt = insr.rfind(L"==")) != std::wstring::npos) to3 = 2;
				else if ((bt = insr.rfind(L"<=")) != std::wstring::npos) to3 = 3;
				else if ((bt = insr.rfind(L">=")) != std::wstring::npos) to3 = 4;
				else if ((bt = insr.rfind(L"!=")) != std::wstring::npos) to3 = 5;
				else if ((bt = insr.rfind(L'>')) != std::wstring::npos) to3 = 0;
				else if ((bt = insr.rfind(L'<')) != std::wstring::npos) to3 = 1;
				else throw w_err(L"Improper choice command [" + std::to_wstring(sgoto) + L']');
				value = insr.substr(bt + (to3 > 1 ? 2U : 1U));
				insr.erase(bt, std::wstring::npos);
				if (choice.back().avaible)
				{
					if (!FindInt(insr, bt))
					{
						std::wstring sval;
						if (!FindString(insr, sval) && to3 == 2) throw w_err(L"Couldn't find a Stat with name \"" + insr + L"\" [" + std::to_wstring(sgoto) + L']');
						else choice.back().avaible = (sval == value);
						continue;
					}
					else if (!stoiCheck(value, val)) if (!FindInt(value, val)) throw w_err(L"[Choice]FATAL stoicheck failure while evaluating \"#if\" result [" + std::to_wstring(sgoto) + L']');;
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
			dmargin += text.getCharacterSize();
			//if (debug) warn(L"[Choice]Searching for \"{\". If infinite loop occurs (program is stuck and yields no repsonse) you probably forgot to write \"}\" at the end of choice[" + sgoto + L']'); 
			bool first = true;
			for (std::wstring insrt;;)
			{
				if (!first) {
					getline(insr);
				}
				else first = false;
				if (CommentCheck(insr)) continue;
				IfCheck(insr);
				if (insr == empty || NewlineCheck(insr))
					SplitText(true, insrt);
				else if (insr.empty())
				{
					insrt += L'\n';
					SplitText(true, insrt);
				}
				else if (insr.find(L'{') != std::wstring::npos)
				{
					choice.back().text.setFont(*text.getFont());
					choice.back().text.setCharacterSize(text.getCharacterSize());
					choice.back().text.setFillColor(text.getFillColor());
					choice.back().text.setPosition(w2, static_cast<float>(dmargin));
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
					choice.back().dgto = sgoto;
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
				} //http://stackoverflow.com/questions/41353227/does-stdstring-char-expression-create-another-stdstring
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

bool ScenarioParser::checkName(const std::wstring &name, bool fatal)
{	
	for (auto &x : s_stats){
		if (name == x.second.name){
			if (fatal) throw w_err(L"Error: there is a name conflict! There cannot be 2 variables with the same name(already exists one of type StringStat) \"" + name + L"\" [" + std::to_wstring(sgoto) + L']');
			else return true;
		}
	}
	for (auto &x : i_stats){
		if (name == x.second.name){
			if (fatal) throw w_err(L"Error: there is a name conflict! There cannot be 2 variables with the same name(already exists one of type IntStat) \"" + name + L"\" [" + std::to_wstring(sgoto) + L']');
			else return true;
		}
	}
	for (auto &x : io_stats){
		if (name == x.second.name){
			if (fatal) throw w_err(L"Error: there is a name conflict! There cannot be 2 variables with the same name(already exists one of type IntStatOpposite) \"" + name + L"\" [" + std::to_wstring(sgoto) + L']');
			else return true;
		}
	}
	for (auto &x : Ints){
		if (name == x.second.name){
			if (fatal) throw w_err(L"Error: there is a name conflict! There cannot be 2 variables with the same name(already exists one of type Int) \"" + name + L"\" [" + std::to_wstring(sgoto) + L']');
			else return true;
		}
	}
	for (auto &x : stc_i) {
		if (name == x.name) {
			if (fatal) throw w_err(L"Error: there is a name conflict! There cannot be 2 variables with the same name(already exists one of type Int) \"" + name + L"\" [" + std::to_wstring(sgoto) + L']');
			else return true;
		}
	}
	for (auto &x : stc_s) {
		if (name == x.name) {
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
	dmargin += static_cast<int>(floor(text.getLocalBounds().top + text.getGlobalBounds().height + text.getCharacterSize()));
	tinsr.clear();
}

void ScenarioParser::Show_stats()
{
	sf::Text astat;
	sf::Color c = astat.getFillColor(); c.a = 0;
	astat.setFont(*text.getFont());
	int th = static_cast<int>(round(text.getCharacterSize() * 0.9f));
	sdmargin = static_cast<int>(1.4f * th);
	astat.setCharacterSize(th);
	for (auto prior = priorlimit; prior != -1; --prior)
	{
		for (auto it = s_stats.equal_range(prior); it.first != it.second; ++it.first)
		{
			auto &s = it.first->second;
			if (!s.hidden)
			{
				s.t = astat;
				s.t.setString(s.name + L": ");
				if (!s.vhidden) s.t.setString(s.t.getString() + s.value);
				s.t.setOrigin(0, round(s.t.getLocalBounds().top));
				s.t.setPosition(round(*w / 12.f), static_cast<float>(sdmargin));
				s.pos = static_cast<sf::Vector2i>(s.t.getPosition());
				sdmargin += static_cast<int>(round(th * 1.25f));
			}
		}
		for (auto it = io_stats.equal_range(prior); it.first != it.second; ++it.first)
		{
			auto &i = it.first->second; 
			if (!i.hidden)
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

				i.setSprite(IOStatspecial(static_cast<int>(round(*w / 1.45f)), static_cast<int>(round(th * 1.2f)), i.value, i.min, i.max, i.threshold));
				i.s.setPosition(round(*w / 12.f), static_cast<float>(sdmargin));
				i.s.setColor(sf::Color(255, 255, 255, 0));
				i.pos[3] = sf::Vector2i(static_cast<int>(round(*w / 12.f)), static_cast<int>(i.s.getPosition().y));

				float y = round(i.s.getPosition().y + i.s.getGlobalBounds().height / 2.f);
				sdmargin += static_cast<int>(round(th * 1.65f));

				i.t[0].setPosition(round(*w / 11.f), y);
				i.pos[0] = static_cast<sf::Vector2i>(i.t[0].getPosition());
				float x = round(i.t[0].getGlobalBounds().left + i.t[0].getGlobalBounds().width); //i.t[0].getGlobalBounds().left + i.t[0].getGlobalBounds().width double times looks rather bad
				i.t[1].setPosition(round(i.s.getGlobalBounds().left + i.s.getGlobalBounds().width - (*w / 11.f - *w / 12.f) - i.t[1].getGlobalBounds().width), y);
				i.pos[1] = static_cast<sf::Vector2i>(i.t[1].getPosition());
				i.t[2].setPosition(round(x  + (i.t[1].getGlobalBounds().left - x - i.t[2].getGlobalBounds().width) / 2.f), y);
				i.pos[2] = static_cast<sf::Vector2i>(i.t[2].getPosition());
			}
		}
		for (auto it = i_stats.equal_range(prior); it.first != it.second; ++it.first)
		{
			auto &i = it.first->second;
			if (!i.hidden)
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
				i.setSprite(IntSpecial(static_cast<int>(round(*w / 1.45f)), static_cast<int>(round(th * 1.2f)), arg[0], arg[1], arg[2]));
				i.s.setPosition(round(*w / 12.f), static_cast<float>(sdmargin));
				i.s.setColor(sf::Color(255, 255, 255, 0));
				i.pos[1] = sf::Vector2i(static_cast<int>(round(*w / 12.f)), static_cast<int>(i.s.getPosition().y));
				i.t.setPosition(round(*w / 11.f), round(i.s.getPosition().y + i.s.getGlobalBounds().height / 2.f));
				i.pos[0] = static_cast<sf::Vector2i>(i.t.getPosition());

				astat.setFillColor(c);
				astat.setStyle(sf::Text::Regular);

				sdmargin += static_cast<int>(round(th *1.65f));
			}
		}
		for (auto it = Ints.equal_range(prior); it.first != it.second; ++it.first)
		{
			auto &i = it.first->second;
			if (!i.hidden)
			{
				i.t = astat;
				i.t.setString(i.name + L": " + std::to_wstring(i.value));
				i.t.setOrigin(0,round(i.t.getLocalBounds().top));
				i.t.setPosition(round(*w / 12.f), static_cast<float>(sdmargin));
				i.pos = static_cast<sf::Vector2i>(i.t.getPosition());
				sdmargin += static_cast<int>(round(th * 1.25f));
			}
		}
	}
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
	return img; //*w razie lagów zastosować skalowanie = in case of lags use setScale()
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
	return img; //*w razie lagów zastosować skalowanie // in case of lags use setScale()
}

bool ScenarioParser::IfCheck(std::wstring &insr)
{
		size_t beg = insr.find(L"#if(");
		if (beg == std::wstring::npos) return false;
		size_t end = insr.find(L')', beg);
		std::wstring IF = insr.substr(insr.find(L"#if(") + 4U, end - 4U);
		insr.erase(beg, end - beg + 1U);
	std::wstring name, value;
	int to3, val;
	bool IFb;
	if ((val = IF.find(L"==")) != std::wstring::npos) to3 = 2;
	else if ((val = IF.find(L"<=")) != std::wstring::npos) to3 = 3;
	else if ((val = IF.find(L">=")) != std::wstring::npos) to3 = 4;
	else if ((val = IF.find(L"!=")) != std::wstring::npos) to3 = 5;
	else if ((val = IF.find(L'>')) != std::wstring::npos) to3 = 0;
	else if ((val = IF.find(L'<')) != std::wstring::npos) to3 = 1;
	else throw w_err(L"Improper \"if\" command [" + std::to_wstring(sgoto) + L']');
	name = IF.substr(0, val);
	value = IF.substr(IF.size() - val);
	int cval;
	if (!FindInt(name, cval))
	{
		std::wstring sval;
		if (!FindString(name, sval)) throw w_err(L"Couldnt find a stat with name " + name +  L" [" + std::to_wstring(sgoto) + L']');
		FindString(value, value);
		IFb = (sval == value);
		if (to3 == 5) IFb = !IFb;
	}
	else
	{
		if (!stoiCheck(value, val)) if (!FindInt(value, val)) throw w_err(L"[Choice]FATAL stoicheck failure while evaluating \"#if\" result [" + std::to_wstring(sgoto) + L']');
		switch (to3)
		{
		case 0:
			IFb = (cval> val);
			break;
		case 1:
			IFb = (cval < val);
			break;
		case 2:
			IFb = (cval == val);
			break;
		case 3:
			IFb = (cval <= val);
			break;
		case 4:
			IFb = (cval >= val);
			break;
		case 5:
			IFb = (cval != val);
			break;
		}
	}
	end = 0U;
	while ((beg = insr.find(L'{')) == std::wstring::npos) getline(insr);
	insr.erase(0U, beg + 1U);
	for (int ssgoto = 1;; getline(insr)) {
		CommentCheck(insr);
		while ((end = insr.find(L'{', end + 1U)) != std::wstring::npos) ++ssgoto;
		end = 0U;
		while ((end = insr.find(L'}', end + 1U)) != std::wstring::npos) 
			if (!--ssgoto) 
			{ insr.erase(end, 1U); TextProcess(insr, ScenarioParser::insr); return true; };
		if (IFb)
			if (!IfCheck(insr)) TextProcess(insr, ScenarioParser::insr);
	}
}

void ScenarioParser::ParseMainBody()
{
	std::wstring preinsr;
	preinsr.reserve(200);
	getline(preinsr);
	if (preinsr[0] == 0xFEFF) preinsr.erase(0U, 1U);
	else if (preinsr[0] == 0xef && preinsr[1] == 0xbb && preinsr[2] == 0xbf) preinsr.erase(0U, 3U);
	for (;PlayerTurn == false;)
	{
		if (dgoto != 0 && sgoto >= dgoto) { SplitText(false, insr); PlayerTurn = true; }
		if (CommentCheck(preinsr)) continue;
		if (!IfCheck(preinsr)) TextProcess(preinsr, insr);
		if (PlayerTurn == false) getline(preinsr);
	}
	MergeText();
}

inline void ScenarioParser::getline(std::wstring &preinsr)
{
	if (!std::getline(in, preinsr))
	{
		if (in.eof()) throw w_err(L"Tried to read past eof");
		else if (in.fail()) throw w_err(L"Logical operation failed");
		throw w_err(L"Reading operation failed");
	}
	++sgoto;
}

bool ScenarioParser::NewlineCheck(const std::wstring& checked)
{
	for (const wchar_t c : checked)
		if (c != L'\n') return false;
	return true;
}

size_t ScenarioParser::Pfind(const std::wstring& str, wchar_t c)
{
	size_t r = str.find(c);
	if (r == std::wstring::npos) w_err(L"Critical function failed in string \"" + str + L"\" while searching for \'" + c + L"\' [" + std::to_wstring(sgoto) + L']'); //it will controll flow, so don't worry about the warrning
	else return r;
}

inline IntStat* ScenarioParser::FindIStat(const std::wstring &name)
{
	for (auto &x : i_stats)
	{
		auto &i = x.second;
		if (name == i.name)
			return &i;
	}
	return nullptr;
}

inline bool ScenarioParser::FindIStat(const std::wstring &name, const IntStat *&rt)
{
	for (auto &x : i_stats)
	{
		const auto &i = x.second;
		if (name == i.name) {
			rt = &i;
			return true;
		}
	}
	return false;
}

inline IntStatOpposite* ScenarioParser::FindIStatO(const std::wstring &name)
{
	for (auto &x : io_stats)
	{
		auto &i = x.second;
		if (name == i.name)
			return &i;
	}
	return nullptr;
}

inline bool ScenarioParser::FindIStatO(const std::wstring &name, const IntStatOpposite *&rt)
{
	for (auto &x : io_stats)
	{
		const auto &i = x.second;
		if (name == i.name) {
			rt = &i;
			return true;
		}
	}
	return false;
}

inline Int* ScenarioParser::FindInt(const std::wstring &name)
{
	for (auto &x : Ints)
	{
		auto &i = x.second;
		if (name == i.name)
			return &i;
	}
	return nullptr;
}

inline bool ScenarioParser::FindInt(const std::wstring &name, const Int *&rt)
{
	for (auto &x : Ints)
	{
		const auto &i = x.second;
		if (name == i.name) {
			rt = &i;
			return true;
		}
	}
	return false;
}

inline StringStat* ScenarioParser::FindSStat(const std::wstring &name)
{
	for (auto &x : s_stats)
	{
		auto &s = x.second;
		if (name == s.name)
			return &s;
	}
	return nullptr;
}

inline bool ScenarioParser::FindSStat(const std::wstring &name, const StringStat *&rt)
{
	for (auto &x : s_stats)
	{
		const auto &s = x.second;
		if (name == s.name) {
			rt = &s;
			return true;
		}
	}
	return false;
}


inline StcInt* ScenarioParser::FindStcI(const std::wstring &name)
{
	for (StcInt &i : stc_i)
		if (name == i.name)
			return &i;
	return nullptr;
}

inline bool ScenarioParser::FindStcI(const std::wstring &name, const StcInt *&rt)
{
	for (const StcInt &i : stc_i) {
		if (name == i.name) {
			rt = &i;
			return true;
		}
	}
	return false;
}

inline StcString* ScenarioParser::FindStcS(const std::wstring &name)
{
	for (StcString &s : stc_s) 
		if (name == s.name)
			return &s;
	return nullptr;
}

inline bool ScenarioParser::FindStcS(const std::wstring &name, const StcString *&rt)
{
	for (const StcString &s : stc_s) {
		if (name == s.name) {
			rt = &s;
			return true;
		}
	}
	return false;
}


bool ScenarioParser::FindString(const std::wstring &name, std::wstring &r)
{
	const StringStat *rt1 = nullptr;
	const StcString *rt2 = nullptr;
	bool succ = false;

	if (succ = FindSStat(name, rt1)) r = rt1->value;
	else if (succ = FindStcS(name, rt2)) r = rt2->value;

	return succ;
}

bool ScenarioParser::FindInt(const std::wstring &name, int &r)
{
	const IntStat *rt1 = nullptr;
	const IntStatOpposite *rt2 = nullptr;
	const Int *rt3 = nullptr;
	const StcInt *rt4 = nullptr;
	bool succ = false;

	if (succ = FindIStat(name, rt1)) r = rt1->value;
	else if (succ = FindIStatO(name, rt2)) r = rt2->value;
	else if (succ = FindInt(name, rt3)) r = rt3->value;
	else if (succ = FindStcI(name, rt4)) r = rt4->value;

	return succ;
}

void ScenarioParser::CreateTypeBox()
{
	TypeBox &tb = typeboxes.back();
	tb.t.setFont(*text.getFont());
	tb.t.setFillColor(sf::Color(0, 0, 0, 0));
	tb.t.setCharacterSize(static_cast<unsigned int>(text.getCharacterSize() * 0.9f));

	sf::Text t;
	t.setFont(*text.getFont());
	t.setCharacterSize(static_cast<unsigned int>(text.getCharacterSize() * 0.9f));
	t.setString("yW");

	tb.rt.setSize(sf::Vector2f(*w - 2*w2 + 8.f, t.getGlobalBounds().height + 8.f));
	tb.rt.setOutlineThickness(static_cast<unsigned int>(4.f * (*w+*h)/(1400.f)));
	tb.rt.setOutlineColor(typeboxcolor);
	tb.rt.setFillColor(sf::Color(0, 0, 0, 0));
	tb.t.setPosition(sf::Vector2f(round(w2 - tb.t.getLocalBounds().left), static_cast<float>(dmargin - tb.t.getLocalBounds().top)));
	tb.rt.setPosition(sf::Vector2f(round(w2 - 4.f), static_cast<float>(dmargin - 4)));
	dmargin += typeboxes.back().rt.getSize().y * 1.05f;
	tb.t.setString(*tb.s); //it is fixed size for now
}

void ScenarioParser::TextProcess(std::wstring &preinsr, std::wstring &insr)
{
	IgnoreTabs(preinsr);
	if (preinsr[0U] == '#' || ElTabs(preinsr))
	{
		if (preinsr == L"#end")
		{
			SplitText(false, insr);
			MergeText();
			PlayerTurn = true;
		}
		else if (preinsr == L"#next") //!debug, will end after constructor
		{
			SplitText(false, insr);
			MergeText();
			next.setPosition(round(*w / 2 - Bnext.width / 2.f), round(dmargin + Bnext.height / 2.f));
			Bnext = next.getGlobalBounds();
			dmargin += static_cast<int>(round(Bnext.height * 1.6f));
			DrawNext = true;
			PlayerTurn = true;
		}
		else if (preinsr.find(L"#goto(") == 0U)
		{
			preinsr.erase(0U, 6U);
			preinsr.pop_back();
			int line;
			if (stoiCheck(preinsr, line)) GotoLine(line - 1);
			else if (waypoints.find(preinsr) != waypoints.end()) GotoLine(waypoints.at(preinsr));
			else throw w_err(L"\"#goto\" command's stoicheck failure! Check if you didn't use a letter or if you put too many non-digit characters [" + std::to_wstring(sgoto) + L']');
			dgoto = 0;
			return;
		}
		else ExecuteCommand(preinsr);
		return;
	}
	if (choiceneed) return;
	if (preinsr == empty || NewlineCheck(preinsr))
		SplitText(false, insr);
	else if (preinsr.empty())
	{
		insr += L'\n';
		SplitText(false, insr);
	}
	else if (preinsr[0U] == L'\t') {
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

bool ScenarioParser::ElTabs(std::wstring &insr)
{
	unsigned int pos;
	for (pos = 0U; insr[pos] == L'\t'; ++pos);
	if (pos == L'#')
	{
		insr.erase(0U, pos);
		return true;
	}
	else return false;
}

void ScenarioParser::IgnoreTabs(std::wstring &insr)
{
	int x;
	for (x = 0; x != ttignore; ++x)
	{
		if (insr[x] != L'\t') break;
	}
	insr.erase(0U, x);
}

inline void ScenarioParser::CreateGainText()//add args
{
	sf::Text t = text;
	t.setFillColor(gaintextcolor);
	t.setPosition(text.getPosition().x,dmargin);
	gaintext.push_back(t);
}

void ScenarioParser::ScanForWaypoints()
{
	std::wstring insr;
	insr.reserve(200U);
	for (int gto = 0;std::getline(in, insr);++gto)
	{
		CommentCheck(insr);
		IgnoreTabs(insr);
		if (insr.find(L"#t(") == 0U)
		{
			insr.erase(0U, 3U); insr.pop_back();
			stoiCheck(insr, ttignore);
		}
		else if (insr.find(L"#wp(") == 0U)
		{
			insr.erase(0U, 4U);
			insr.pop_back();
			size_t n;
			n = Pfind(insr, L',');
			std::wstring name = insr.substr(0U, n);
			waypoints[name] = gto;
		}
	}
	in.clear();
}
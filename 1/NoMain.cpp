#include "NoMain.h"

#include <cstring>

using namespace Promt;
using namespace Write;
using namespace Composits;
using namespace Pers;
using namespace Help;


void Help:: ClearBuf()
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return;
}

int Help::Action()
{
	int action{};
	std::cin >> action;
	if (std::cin.eof())
		throw std::runtime_error("This is end of file. Goodbye");
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		throw std::runtime_error("This is not a number");
	}
	if (std::cin.bad())
		throw std::runtime_error("It is bad. Error");
	return action;
}
int Help::Menu()
{
	std::ifstream file("Menu.txt");
	if (file.is_open())
	{
		char ch;
		while (file.get(ch))
		{
			std::cout << ch;
		}
		file.close();
	}
	return 0;
}
std::string Help::RecNoXml(Rec& recover, std::string namerec)
{
	std::string bigstring = std::format("Name Record: {}\n\tYour Word: {}\n\tYour Meaning: {}\n\tYour Emphasis: {}\n",
		namerec, recover.word, recover.meaning, recover.emphasis);
	return bigstring;
}
std::string Help::RecXml(Rec& record, std::string namerec)
{
	std::string bigstring = std::format("<{}>\n\t<word>{}</word>\n\t<meaning>{}</meaning>\n\t<emphasis>{}</emphasis>\n</{}>",
		namerec, record.word, record.meaning, record.emphasis, namerec);
	return bigstring;
}

int Write::WriteWord(std::string& word, std::vector<int>& glas)
{

	std::cout << "Ok\n" << "Please write word" << std::endl;
	std::cin >> word;
	if (std::cin.eof())
		throw std::runtime_error("This is end of file. Goodbye");

	if (word.size() > 20)
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		throw std::runtime_error("Long word");
	}
	for (int i = 0; i < word.size(); i++)
	{
		if (word[i] == 'e' || word[i] == 'a' || word[i] == 'u' || word[i] == 'o' || word[i] == 'i')
			glas.push_back(i + 1);
	}
	if (glas.size() == 0) throw std::runtime_error("Dont have emphasis in word");
	return 0;
}

int Write::WriteMeaning(std::string& meaning)
{
	std::cout << "Write meaning" << std::endl;
	std::cin >> meaning;
	if (std::cin.eof())
		throw std::runtime_error("This is end of file. Goodbye");
	return 0;
}

int Write::WriteEmphasis(int& emphasis, std::vector<int> glas)
{
	std::cout << "Write emphasis" << std::endl;
	std::cin >> emphasis;
	if (std::cin.eof())
		throw std::runtime_error("This is end of file. Goodbye");
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		throw std::runtime_error("Your input not number durak");
	}
	for (int i = 0; i < glas.size(); i++)
	{
		if (emphasis == glas[i])
			return 0;
	}
	throw std::runtime_error("Not emphasis in word");
}

int Write::Writes(Rec& instance)
{
	int flag1 = -1;
	int flag2 = -1;
	int flag3 = -1;
	std::vector<int> glas;
	while (flag1 != 0 || flag2 != 0 || flag3 != 0)
	{
		try
		{
			if (flag1 != 0)
			{
				flag1 = WriteWord(instance.word, glas);
				continue;
			}
		}
		catch (std::runtime_error& ex)
		{
			std::string str_er = ex.what();
			if (str_er == "This is end of file. Goodbye") {
				throw std::runtime_error("This is end of file. Goodbye");
			}
			std::cout << str_er << std::endl;
			continue;
		}
		try {
			if (flag2 != 0)
			{
				flag2 = WriteMeaning(instance.meaning);
				continue;
			}
		}
		catch (std::runtime_error& ex)
		{
			std::string str_er = ex.what();
			if (str_er == "This is end of file. Goodbye") {
				throw std::runtime_error("This is end of file. Goodbye");
			}
			std::cout << str_er << std::endl;
			continue;
		}

		try
		{
			if (flag3 != 0)
			{
				flag3 = WriteEmphasis(instance.emphasis, glas);
				continue;
			}
		}
		catch (std::runtime_error& ex)
		{
			std::string str_er = ex.what();
			if (str_er == "This is end of file. Goodbye") {
				throw std::runtime_error("This is end of file. Goodbye");
			}
			std::cout << str_er << std::endl;
			continue;
		}
	}
	return 0;
}

int Promt::PromtWord(Rec record)
{
	if (record.word == "") throw std::runtime_error("Error: you are enter not words");
	if (record.word.size() < 2) throw std::runtime_error("Error: you are enter one character, but this is not string");
	if (record.word.size() > 20) throw std::runtime_error("Error: your word is biger");
	return 0;
}

int Promt::PromtMeaning(Rec record)
{
	if (record.meaning == "") throw std::runtime_error("Error: you are enter not meaning");
	return 0;
}

int Promt::PromtEmphasis(Rec record)
{
	std::vector <int> glas{};
	bool flag = false;
	for (int i = 0; i < record.word.size(); i++)
	{
		if (record.word[i] == 'e' || record.word[i] == 'a' || record.word[i] == 'u' || record.word[i] == 'o' || record.word[i] == 'i')
			glas.push_back(i + 1);
	}
	if (glas.size() == 0) throw std::runtime_error("Error: your word has no vowels");
	for (int i = 0; i < glas.size(); i++)
	{
		if (record.emphasis == glas[i])
			flag = true;
	}

	if (flag == false) throw std::runtime_error("Error: Your emphasis is not located in word");
	return 0;
}

const char* Pers::Per(Rec& record, const char* line, size_t cap)
{
	std::string newline = line;
	std::erase(newline, ' ');
	std::istringstream lineseperate(line);
	char* temp = new char[cap];
	int flag = 0;
	std::string recording;
	if (lineseperate.getline(temp, cap, '<') && lineseperate.getline(temp, cap, '>')) recording = temp;
	while (lineseperate.getline(temp, cap, '>') && lineseperate.getline(temp, cap, '<'))
	{
		char sim = temp[0];
		if (sim == '\0')
		{
			flag++;
			continue;
		}
		if (flag == 0)
		{
			record.word = temp;
			cap += record.word.size();
		}
		if (flag == 2)
		{
			record.meaning = temp;
			cap += record.meaning.size();
		}
		if (flag == 4)
		{
			record.emphasis = temp[0] - '0';
			cap += 1;
		}
		flag++;
	}
	PromtWord(record);
	PromtMeaning(record);
	PromtEmphasis(record);
	if (flag != 6) throw std::runtime_error("Error: you are enter is not format");
	std::string feedback = RecNoXml(record, recording);
	char* rec = new char[cap+1];
	for (int i = 0; i < cap; i++) {
		rec[i] = feedback[i];
		if (feedback[i+1] == '\0') break;
	}

	rec[feedback.size()] = '\0';
	delete[] temp;
	return rec;


}


std::string Pers::Per(Rec& record, std::string line)
{
	std::erase(line, ' ');
	std::istringstream lineseperate(line);
	size_t cap = line.size() + 1;
	char* temp = new char[cap];
	int flag = 0;
	std::string recording;
	if (lineseperate.getline(temp, cap, '<') && lineseperate.getline(temp, cap, '>')) recording = temp;
	while (lineseperate.getline(temp, cap, '>') && lineseperate.getline(temp, cap, '<'))
	{
		char sim = temp[0];
		if (sim == '\0')
		{
			flag++;
			continue;
		}
		if (flag == 0) record.word = temp;
		if (flag == 2) record.meaning = temp;
		if (flag == 4) record.emphasis = temp[0] - '0';
		flag++;
	}
	PromtWord(record);
	PromtMeaning(record);
	PromtEmphasis(record);
	if (flag != 6) throw std::runtime_error("Error: you are enter is not format");
	delete[] temp;
	return RecNoXml(record, recording);
}

const char* Pers::Per(Rec& record, const char* line)
{
	std::string newline = line;
	std::erase(newline, ' ');
	std::istringstream lineseperate(line);
	size_t cap = newline.size() + 1;
	char* temp = new char[cap];
	int flag = 0;
	std::string recording;
	if (lineseperate.getline(temp, cap, '<') && lineseperate.getline(temp, cap, '>')) recording = temp;
	size_t mala = recording.size();
	char* rec = new char[mala];
	while (lineseperate.getline(temp, cap, '>') && lineseperate.getline(temp, cap, '<'))
	{
		char sim = temp[0];
		if (sim == '\0')
		{
			flag++;
			continue;
		}
		if (flag == 0) record.word = temp;
		if (flag == 2) record.meaning = temp;
		if (flag == 4) record.emphasis = temp[0] - '0';
		flag++;
	}
	PromtWord(record);
	PromtMeaning(record);
	PromtEmphasis(record);
	if (flag != 6) throw std::runtime_error("Error: you are enter is not format");
	std::string feedback = RecNoXml(record, recording);
	for (int i = 0; i < mala; i++)
		rec[i] = feedback[i];
	rec[mala] = '\0';
	delete[] temp;
	return rec;
}

const char* Composits::Composit(Rec& record, const char* namerec)
{
	if (!record.emphasis)
		throw std::runtime_error("Eror: Haven`t struct word");
	std::string strs = RecXml(record, namerec);
	size_t size = strs.size();
	char* line = new char[size];
	for (int i = 0; i < size; i++)
		line[i] = strs[i];
	line[size] = '\0';
	return line;
}

std::string Composits::Composit(Rec& record, std::string namerec)
{
	if (!record.emphasis)
		throw std::runtime_error("Eror: Haven`t struct word");
	std::string str = RecXml(record, namerec);
	return str;
}

const char* Composits::Composit(Rec& record, const char* namerec, size_t cap)
{
	if (!record.emphasis)
		throw std::runtime_error("Eror: Haven`t struct word");
	std::string strs = RecXml(record, namerec);
	char* line = new char[cap+1];
	for (int i = 0; i < cap; i++)
		line[i] = strs[i];
	line[cap] = '\0';
	return line;
}
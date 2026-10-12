#include "NoMain.h"

using namespace Promt;
using namespace Write;
using namespace Composits;
using namespace Pers;
using namespace Help;


int main()
{
	bool iter = true;
	//Rec man{};
	//Rec& instance = man;
	Rec instance;

	while (iter)
	{
		try {
			Menu();
			std::cout << "You are write action" << std::endl;
			int action = Action();
			switch (action)
			{
			case 1:
			{
				Writes(instance);
				void Clear();
				break;
			}
			case 2:
			{
				std::cout << "Please write name record\n";
				std::string namerecord{};
				std::cin >> namerecord;
				if (std::cin.eof()) throw "This is end of file.Goodbye";
				const char* constnamerecord = namerecord.c_str();
				size_t capacity = namerecord.size() * 2 + 1 + instance.meaning.size() + instance.word.size() + 65;
				const char* result = Composit(instance, constnamerecord, capacity);
				/*const char* result = Composit(instance, constnamerecord);*/
				/*std::string result = Composit(instance, namerecord);*/

				if (!std::cin.good())
					throw std::runtime_error("You write bad namerecord, please try again");
				std::cout << result<< std::endl;
				delete[] result;
				break;
			}
			case 3:
			{
				while (true)
				{
					try {
						std::string format = "Please write format xml:\n<namerecor>\n\t<word>yourword</word>\n\t<meaning>yourmeaning</meaning>\n\t<emphasis>youremphasis</emphasis>\n</namerecor>";
						std::cout << format << std::endl;
						std::string line{};
						if (std::cin.eof()) return 0;
						std::cin >> line;
						const char* constline = line.c_str();
						size_t capacity = format.size();//64;
						/*const char* res = Per(instance, line);*/
						/*const char* res = Per(instance, constline);*/
						const char* res = Per(instance, constline,capacity);
						std::cout << res <<std::endl;
						ClearBuf();
						delete[] res;
						break;
					}
					catch (std::runtime_error& ex)
					{
						std::cout << ex.what() << std::endl;
						ClearBuf();
						continue;
					}
				}
				break;
			}
			case 4:
			{
				iter = false;
				std::cout << "Bye-Bye" << std::endl;
				break;
			}
			}
		}
		catch (std::exception &ex)
		{
			std::string str_er = ex.what();

			if (str_er == "This is end of file. Goodbye") {
				iter = false;
				break;
			}
			std::cout << str_er << "\n" << "Try again" << std::endl;
			ClearBuf();
		}
	}
	return 0;
}
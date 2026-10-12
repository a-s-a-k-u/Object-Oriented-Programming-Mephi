#include "libery_all.h"

void Help::ErCin() {
    if (std::cin.eof()) throw std::runtime_error("EOF");
    if (std::cin.fail()) throw std::runtime_error("Fail");
}


void Help::menuEs() {
    std::cout << "1 - Initialisation signal\n";
    std::cout << "2 - Getting signal\n";
    std::cout << "3 - Separating signal\n";
    std::cout << "4 - Plus duration of signal\n";
    std::cout << "5 - Minus duration of signal\n";
    std::cout << "6 - Enter on display signal/signals\n";
    std::cout << "7 - Exit" << std::endl;
}
void Help::menuHr() {
    std::cout << "1 - Initialisation timing diagram\n";
    std::cout << "2 - Getting timing diagram\n";
    std::cout << "3 - Merge signals of the timing diagram\n";
    std::cout << "4 - Plus duration of signal\n";
    std::cout << "5 - Minus duration of signal\n";
    std::cout << "6 - Enter on display signal/signals\n";
    std::cout << "7 - Plus num timing diagram\n";
    std::cout << "8 - Minus num timing diagram\n";
    std::cout << "9 - Exit" << std::endl;
}

void Help::action(HrCl& tests, HrCl& second, int &ac)
{
    try {
        std::string signal{};
        EsCl* trash;
        menuHr();
        std::cout << "Please give me action\n";
        std::cin>>ac;
        ErCin();
        int val{};
        std::string name{};
        try {
            switch (ac) {
                case 1:
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::getline(std::cin, name, '\n');
                    if (tests.GetCapacity() == 0) {tests.Input(name); break;}
                    second.Input(name);
                    break;
                case 2:
                    // PromtClass(tests);
                    // PrintSignal(tests, second);
                    if (second.GetCapacity() == 0) tests.PrintList();
                    else {
                        std::cout << "This 1 timing diagram:" << std::endl;
                        tests.PrintList();
                        std::cout << "This 2 timing diagram:" << std::endl;
                        second.PrintList();
                    }
                    break;
                 case 3:
                    tests.Merge();
                    tests.PrintList();
                    break;
                case 4:
                    tests += second;
                    second.trash();
                    break;
                // case 5:
                //     std::cout << "Write number: ";
                //     std::cin >> val;
                //     ErCin();
                //     tests -= val;
                //     break;
                case 6:
                    std::cout << "write number that multiplicative timing diagram" << std::endl;
                    std::cin >> val;
                    tests * val;
                    tests.PrintList();
                    break;
                case 7:
                    std::cout << "write number that plus timing diagram" << std::endl;
                    std::cin >> val;
                    tests >> val;
                    tests.PrintList();
                    break;
                case 8:
                    std::cout << "write number that minus timing diagram" << std::endl;
                    std::cin >> val;
                    tests << val;
                    tests.PrintList();
                    break;
                case 9:
                    std::cout << "Ok, bye-bye" << std::endl;
                    break;
            }

        }
        catch (const std::runtime_error &er) {
            std::string error = er.what();
            if (error == "Error: You are could not write this") {
                std::cout << error << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            else{throw std::runtime_error(er.what());}
        }
    }catch (std::runtime_error &ex) {
        throw ex;
    }

}


void Help::action(EsCl& tests, EsCl& second, int &ac)
{
    try {
        std::string signal{};
        menuEs();
        std::cout << "Please give me action\n";
        std::cin>>ac;
        ErCin();
        int val{};
        std::string name{};
        try {
            switch (ac) {
                case 1:
                    std::cin >> tests;
                    break;
                case 2:
                    PromtClass(tests);
                    PrintSignal(tests, second);
                    break;
                case 3:
                    PromtClass(tests);
                    std::cout << "Write second that separate signal\n";
                    std::cin >> val;
                    ErCin();
                    tests(second, val);
                    break;
                case 4:
                    std::cout << "Write number: ";
                    std::cin >> val;
                    ErCin();
                    tests += val;
                    break;
                case 5:
                    std::cout << "Write number: ";
                    std::cin >> val;
                    ErCin();
                    tests -= val;
                    break;
                case 6:
                    tests.EnterOnDisplay(tests, second);
                    break;
                case 7:
                    std::cout << "Ok, bye-bye" << std::endl;
                    break;
            }

        }
        catch (const std::runtime_error &er) {
            std::string error = er.what();
            if (error == "Error: You are could not write this") {
                std::cout << error << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            else{throw std::runtime_error(er.what());}
        }
    }catch (std::runtime_error &ex) {
        throw ex;
    }

}

void Help::FindErrorCin() {
    if (std::cin.eof()) {throw std::runtime_error("This is end of file");}
    if (std::cin.bad()) {throw std::runtime_error("Fatal Error: cin.bad()");}
    if (std::cin.fail()) {throw std::runtime_error("Error: You are could not write this");}
}

char Help::PromtSignal(char &signal) {
    if (signal != '1' && signal != '0') {
        signal = 'X';
        std::cout << "Your signal not 1 or 0, this mark 'X'" << std::endl;
    }
    return signal;
}

void Help::PromtClass(EsCl &pop) {
    if (pop.GetDuration() == 0) throw std::runtime_error("Error: You are could not read this, because have not signal");
}

void Help::PrintSignal(EsCl &signal, EsCl &second) {

    if (second.GetDuration() == 0) {
        std::cout << signal;
        return;
    }
    std::string name;
    std::cout << "\nWhich signal? (first/second)" << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, name);
    if (name == "first" || name.empty()) std::cout << signal;
    else std::cout << second;
}

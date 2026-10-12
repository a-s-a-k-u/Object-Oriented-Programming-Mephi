#include "libery_all.h"

int main()
{
    int action{};
    EsCl tests, second;
    HrCl list, seplist;

    while (action != 9) { //EsCl != 7
        try {
            // Help::action(tests, second, action);
            Help::action(list, seplist, action);
        }
        catch (const std::runtime_error &er) {
            std::string error = er.what();
            if (error == "EOF") action = 7;
            std::cout << error << std::endl;
        }
        catch (const std::invalid_argument &er) {
            std::cout << er.what() << std::endl;
        }

    }
    return 0;
}

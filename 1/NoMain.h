#include <iostream>
#include <string>
#include <vector>
#include <format>
#include <fstream>
#include <sstream>
#include <ranges>

struct Rec
{
    std::string word{};
    std::string meaning{};
    int emphasis{};
};

namespace Help
{
    int Action();
    int Menu();
    void ClearBuf();
    std::string RecNoXml(Rec& recover, std::string namerec);
    std::string RecXml(Rec& recover, std::string namerec);
}

namespace Write
{
    int WriteWord(std::string& word, std::vector<int>& glas);
    int WriteMeaning(std::string& meaning);
    int WriteEmphasis(int& emphasis, std::vector<int> glas);
    int Writes(Rec& instance);
}

namespace Promt
{
    int PromtWord(Rec record);
    int PromtMeaning(Rec record);
    int PromtEmphasis(Rec record);
}

namespace Composits
{
    const char* Composit(Rec& record, const char* namerec);
    std::string Composit(Rec& record, std::string namerec);
    const char* Composit(Rec& record, const char* str, size_t pr);
}

namespace Pers
{
    const char* Per(Rec& record, const char* line);
    std::string Per(Rec& record, std::string line);
    const char* Per(Rec& record, const char* line, size_t cap);
}
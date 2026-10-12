#include "libery_all.h"

int EsCl::PromtDuration(std::string& line) const{
    int i = 0;
    for (i; i < line.size(); i++) {
        if (line[i] != line[i+1]) break;
    }
    return i + 1;
}


void EsCl::Initialisation (std::string& line) {
    if (line.empty()) return;
    EsCl signal(line);
    this->duration = EsCl::PromtDuration(line);
    this->signal = Help::PromtSignal(signal.signal);
}

EsCl& EsCl::operator+= (int val) {
    duration = duration + val;
    return *this;
}

EsCl& EsCl::operator-= (int val) {
    duration = duration - val;
    return *this;
}


EsCl& EsCl::operator ()(EsCl &second, int val) {
    int temp = duration - val;
    second.signal = signal;
    second.duration = duration - temp;
    duration = val;
    return *this;
}

std::istream & operator>>(std::istream &input, EsCl &signal) {
    std::cout << "Write signal\n";
    std::string line;
    input >> line;
    Help::ErCin();
    if (line.size() > 1 || line.empty()) {signal.Initialisation(line); return input;}
    signal.signal = Help::PromtSignal(line[0]);
    std::cout << "Write duration of signal\n";
    input >> signal.duration;
    return input;

}

std::ostream &operator<<(std::ostream & output, EsCl &signal) {
    output << "Signal: " << signal.GetSignal() << '\n' << "Duration: " << signal.GetDuration() << '\n';
    return output;
}

void EsCl::EnterOnDisplay(EsCl& signal) const{
    for (int i = 0; i < signal.GetDuration(); i++) {
        if (signal.GetSignal() == '0') {std::cout << "_"; continue;}
        if (signal.GetSignal() == '1') {std::cout << "¯"; continue;}
        if (signal.GetSignal() == 'X') {std::cout << "-";}
    }
    std::cout <<std::endl;
}

void EsCl::EnterOnDisplay(EsCl& first_signal, EsCl& second_signal) const{
    if (second_signal.GetDuration() == 0) {
        EnterOnDisplay(first_signal);
        return;
    }
    EnterOnDisplay(first_signal);
    EnterOnDisplay(second_signal);
}

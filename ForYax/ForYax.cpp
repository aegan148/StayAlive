#include"Start.h"
#include <memory>

void choose_mode(int& setting);
void check_choose(const int& setting, std::unique_ptr<game>& g1);

int main()
{
    std::unique_ptr<game> g1(new random_game());
    int setting = NULL;
    choose_mode(setting);
    check_choose(setting, g1);

    g1->start();
}




void choose_mode(int& setting) {
    std::cout << "What mode of game do you prefer? 0-random mode/1- txt mode\n";
    while (!(std::cin >> setting) || (std::cin.peek() != '\n') || (setting < 0) || (setting > 1)) {
        std::cin.clear();
        while (std::cin.get() != '\n');
        std::cout << "Error!Reenter the number: 0/1\n";
    }
}

void check_choose(const int& setting, std::unique_ptr<game>& g1) {
    if (setting == 0) { std::cout << "Welcome to random mode!\n"; }
    else if (setting == 1) {
        std::unique_ptr<game> g2(new txt_game());
        g1 = std::move(g2);
        std::cout << "Welcome to txt mode!\n";
    }
    else { std::cout << "Total crash!\n"; }
}
#include"Start.h"
#include <memory>

class mode {
public:
    static std::unique_ptr<game> game_mode(const int& setting);
};
void choose_mode(int& setting);

int main()
{
    std::unique_ptr<game> g1;
    int setting = NULL;
    choose_mode(setting);

    g1= mode::game_mode(setting);
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


std::unique_ptr<game> mode::game_mode(const int& setting) {
        std::unique_ptr<game> g1(new random_game());
        if (setting == 0) {
            std::cout << "Welcome to random mode!\n";
            ;
        }
        else if (setting == 1) {
            std::unique_ptr<game> g2(new txt_game());
            g1 = std::move(g2);
            std::cout << "Welcome to txt mode!\n";
        }
        else { std::cout << "Total crash!\n"; }
        return std::move(g1);
}

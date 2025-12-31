#include <iostream>

#include "include/Game.h"
#include "include/Error.h"

int main() {

    try {
        Game::get_instance().play();
    } catch (const team_empty& e) {
        std::cout << e.what() << "\n";
    }

    return 0;
}
#include <iostream>

#include "include/Game.h"
#include "include/Error.h"


int main() {

    // Get the singleton instance
    Game::get_instance();


    try {
        Game::play();
    } catch (const team_empty& e) {
        std::cout << e.what() << "\n";
    }


    return 0;
}
#include "include/Game.h"


int main() {

    // Get the singleton instance
    Game::get_instance();


    Game::play();

    return 0;
}
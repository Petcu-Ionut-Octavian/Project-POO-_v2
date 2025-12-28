#ifndef RESTAURANT_GAME_H
#define RESTAURANT_GAME_H

#include <vector>
#include "Employer.h"
#include "Order.h"

class Game {
private:
    // Singleton instance
    static Game* instance;

    // Private constructor
    Game() = default;

    // Prevent copying
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    static std::vector<Employer*> team;
    static std::vector<Order*> orders;

public:

    // Accessor for singleton instance
    static Game& get_instance() {
        if (!instance)
            instance = new Game();
        return *instance;
    }

    // Destructor
    ~Game() = default;


    static void print_team();

    static void print_orders();

    static void set_team();

    static void start();

    static void play();

    static void run_role(const std::string& role_name);


};

#endif //RESTAURANT_GAME_H
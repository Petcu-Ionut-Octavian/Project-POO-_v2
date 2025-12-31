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

    std::vector<Employer*> team = {};
    std::vector<Order*> orders = {};

public:

    // Prevent copying
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    // Accessor for singleton instance
    static Game& get_instance() {
        static Game instance;
        return instance;
    }

    // Destructor
    ~Game(){
        for (auto* ord : orders)
            delete ord;

        for (auto* emp : team)
            delete emp;
    }


    void print_team() const;

    void print_orders() const;

    void set_team();

    void start();

    void play();

    void run_role(const std::string& role_name);

    void run_rest();


};

#endif //RESTAURANT_GAME_H
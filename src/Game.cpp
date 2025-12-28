//
// Created by User on 12/28/2025.
//

#include <iostream>
#include <vector>
#include <limits>
#include "../include/Employer.h"
#include "../include/Order.h"
#include "../include/Game.h"


Game* Game::instance = nullptr;
std::vector<Employer*> Game::team;
std::vector<Order*> Game::orders;

void Game::print_team() {
    std::cout << "#####################\n";
    if (team.empty()) {
        std::cout << "Team is empty.\n";
        return;
    }

    std::cout << "Your team:\n";

    for (auto* emp : team) {
        std::cout << emp->get_role() << " "
                  << emp->getEnergy() << " "
                  << (emp->getUsed() ? "used" : "not used")
                  << "\n";
    }
    std::cout << "#####################\n";
}


void Game::print_orders() {
    std::cout << "#####################\n";
    if (orders.empty()) {
        std::cout << "No orders yet.\n";
        std::cout << "#####################\n";
        return;
    }

    std::cout << "Orders:\n";

    for (auto* ord : orders) {
        std::cout << "Order #" << ord->get_ID()
                  << " | State: " << ord->get_state();

        if (ord->get_state() == "preparing") {
            std::cout << " | Remaining: " << ord->get_remaining_energy();
        }

        std::cout << "\n";
    }
    std::cout << "#####################\n";
}





static int read_int(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (!std::cin.fail())
            return value;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid number. Try again.\n";
    }
}

void Game::set_team() {
    int points = 1000;
    std::cout << "Make your team of employers, you have " << points << " points!\n";

    while (true) {
        std::cout << "\nChoose an employer:\n";
        std::cout << "1. Cook (250 points)\n";
        std::cout << "2. Cashier (100 points)\n";
        std::cout << "3. Delivery (150 points)\n";
        std::cout << "4. Start the simulator\n";

        int choice = read_int("Your choice: ");

        if (choice == 4) {
            std::cout << "Starting the simulator...\n";
            break;
        }

        if (choice == 1) {
            if (points < 250) {
                std::cout << "Not enough points!\n";
                continue;
            }
            team.push_back(new Cook());
            points -= 250;
            std::cout << "Added Cook. Remaining points: " << points << "\n";
        }
        else if (choice == 2) {
            if (points < 100) {
                std::cout << "Not enough points!\n";
                continue;
            }
            team.push_back(new Cashier());
            points -= 100;
            std::cout << "Added Cashier. Remaining points: " << points << "\n";
        }
        else if (choice == 3) {
            if (points < 150) {
                std::cout << "Not enough points!\n";
                continue;
            }
            team.push_back(new Delivery());
            points -= 150;
            std::cout << "Added Delivery. Remaining points: " << points << "\n";
        }
        else {
            std::cout << "Invalid option.\n";
        }
    }

    std::cout << "\nTeam created with " << team.size() << " employers.\n";
    print_team();
}


void Game::start() {
    int cycle = 0;
    while (true) {
        cycle++;
        std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>> Current cycle: " << cycle << "\n";
        print_team();
        print_orders();

        int choice;

        // ask until user enters 1, 2, or 3
        while (true) {
            std::cout << "\nMenu:\n";
            std::cout << "1. Add an order\n";
            std::cout << "2. Skip (no more orders this cycle)\n";
            std::cout << "3. End simulation\n";

            choice = read_int("Choice: ");

            if (choice == 1 || choice == 2 || choice == 3)
                break;

            std::cout << "Invalid option. Please enter 1, 2, or 3.\n";
        }

        if (choice == 1) {
            auto ord = new Order();
            orders.push_back(ord);
            std::cout << "Order #" << ord->get_ID() << " added.\n";
        }
        else if (choice == 2) {
            std::cout << "Skipping cycle...\n";
        }
        else if (choice == 3) {
            std::cout << "Ending simulation...\n";
            break;   // exits the while(true) cycle loop
        }

        std::cout << "\n";



        /// Processing the events
        std::cout << "########## Starting the simulator...\n\n";

        // 1. Cashiers first
        run_role("Cashier");

        // 2. Then cooks
        run_role("Cook");

        // 3. Then delivery
        run_role("Delivery");



    /// End results
    std::cout<<"\n<<<<<<<End of cycle: \n";
    print_team();
    print_orders();

    // Reset all employers
    for (auto* emp : team) {
        emp->reset();
    }



    }

}



void Game::play() {
    set_team();
    start();
}





void Game::run_role(const std::string& role_name) {

    for (auto* emp : team) {

        if (emp->getUsed())
            continue;

        if (emp->get_role() != role_name)
            continue;

        // Determine the optimal state for this role
        std::string optimal;
        if (role_name == "Cashier")   optimal = "processing";
        if (role_name == "Cook")      optimal = "preparing";
        if (role_name == "Delivery")  optimal = "delivering";

        bool worked = false;

        // ============================
        // 1. Try OPTIMAL state first
        // ============================
        for (auto it = orders.begin(); it != orders.end(); ++it) {

            Order* order = *it;
            std::string state = order->get_state();

            if (state == optimal) {

                // Perform the correct action
                if (state == "processing") emp->process(*order);
                else if (state == "preparing") emp->prepare(*order);
                else if (state == "delivering") {
                    emp->deliver(*order);
                    delete order;
                    orders.erase(it);
                }

                worked = true;
                break;
            }
        }

        if (worked)
            continue;

        // ============================
        // 2. FALLBACK: first available order
        // ============================
        for (auto it = orders.begin(); it != orders.end(); ++it) {

            Order* order = *it;
            std::string state = order->get_state();

            // Do the correct action for the state
            if (state == "processing") {
                emp->process(*order);
            }
            else if (state == "preparing") {
                emp->prepare(*order);
            }
            else if (state == "delivering") {
                emp->deliver(*order);
                delete order;
                orders.erase(it);
            }

            break; // employer used
        }
    }
}
//
// Created by User on 12/28/2025.
//

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include "../include/Employer.h"
#include "../include/Order.h"
#include "../include/Game.h"
#include "../include/Error.h"
#include "../include/Events.h"



void Game::print_team() const {
    std::cout << "#####################\n";
    if (team.empty()) {
        throw team_empty();
    }

    std::cout << "Your team:\n";

    for (auto* emp : team) {
        std::cout << *emp << "\n";
    }

    std::cout << "#####################\n";
}


void Game::print_orders() const {
    std::cout << "#####################\n";
    if (orders.empty()) {
        std::cout << "No orders yet.\n";
        std::cout << "#####################\n";
        return;
    }

    std::cout << "Orders:\n";

    for (auto* ord : orders) {
        std::cout << *ord << '\n';
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


    if (team.empty()) {
        throw team_empty();
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
            try {
                auto ord = new Order();

                // If the order is empty, throw
                if (ord->is_empty()) {
                    delete ord;
                    throw order_empty("Error: Order has no products.");
                }

                orders.push_back(ord);
                std::cout << "Order #" << ord->get_ID() << " added.\n";

            } catch (const order_empty& e) {
                std::cout << e.what() << "\n";
            }
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


        /// Random events

        /// For employers
        for (auto emp : team) {

            // 1. Got sick
            if (!emp->getUsed()) {
                trigger_event(0.1, [&]() {
                    emp->setUsed(true);
                    std::cout << "Event: " << *emp << " got sick and is unable to work this turn!\n";
                });
            }

            // 2. Unexpected emergency
            if (!emp->getUsed()) {
                trigger_event(0.1, [&]() {
                    emp->setUsed(true);
                    std::cout << "Event: " << *emp << " had an unexpected emergency and is unable to work this turn!\n";
                });
            }

            // 3. Minor injury
            if (!emp->getUsed()) {
                trigger_event(0.1, [&]() {
                    emp->setUsed(true);
                    std::cout << "Event: " << *emp << " suffered a minor injury and is unable to work this turn!\n";
                });
            }

            // 4. Personal matters
            if (!emp->getUsed()) {
                trigger_event(0.1, [&]() {
                    emp->setUsed(true);
                    std::cout << "Event: " << *emp << " is dealing with personal matters and is unable to work this turn!\n";
                });
            }

            // 5. Transportation issue
            if (!emp->getUsed()) {
                trigger_event(0.1, [&]() {
                    emp->setUsed(true);
                    std::cout << "Event: " << *emp << " ran into transportation issues and is unable to work this turn!\n";
                });
            }

            // 6. Exhaustion
            if (!emp->getUsed()) {
                trigger_event(0.1, [&]() {
                    emp->setUsed(true);
                    std::cout << "Event: " << *emp << " is too exhausted to work this turn!\n";
                });
            }

        }

        /// For orders
        for (auto order : orders) {

            // Order spilled
            if (order->get_state() != "processing") {
                trigger_event(0.1, [&]() {
                    order->set_remaining_energy(order->energy_to_make());
                    order->set_state("processing");
                    std::cout << "Event: Order #" << order->get_ID()
                              << " was spilled and has to be redone.\n";
                });
            }

        }



        /// Sorting the orders
        std::ranges::sort(orders, [](const Order* a, const Order* b) {

            auto priority = [](const std::string& s) {
                if (s == "delivering") return 0;
                if (s == "preparing")  return 1;
                if (s == "processing") return 2;   // added explicitly for readability
                return 3; // fallback, should never happen
            };

            const int pa = priority(a->get_state());

            if (const int pb = priority(b->get_state()); pa != pb)
                return pa < pb;

            return a->get_remaining_energy() < b->get_remaining_energy();
            }
        );


        try {
            // 1. Cashiers first
            run_role("Cashier");

            // 2. Then cooks
            run_role("Cook");

            // 3. Then delivery
            run_role("Delivery");

            // 4. The rest
            run_rest();

        } catch (const no_more_orders& e) {
            std::cout << e.what() << "\n";
        }




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

        if (orders.empty())
            throw no_more_orders();

        if (emp->get_role() != role_name)
            continue;

        // Determine optimal state
        std::string optimal;
        if (role_name == "Cashier")   optimal = "processing";
        if (role_name == "Cook")      optimal = "preparing";
        if (role_name == "Delivery")  optimal = "delivering";

        // Try to find an order in the optimal state
        for (auto it = orders.begin(); it != orders.end(); ++it) {

            Order* order = *it;

            if (order->get_state() == optimal) {

                // Perform correct action
                if (optimal == "processing") {
                    emp->process(*order);
                }
                else if (optimal == "preparing") {
                    emp->prepare(*order);
                }
                else if (optimal == "delivering") {
                    emp->deliver(*order);
                    delete order;
                    orders.erase(it);
                }

                break;
            }
        }
    }
}





void Game::run_rest() {

    for (auto* emp : team) {

        if (emp->getUsed())
            continue;

        if (orders.empty())
            throw no_more_orders();

        // Fallback: first available order
        auto it = orders.begin();
        Order* order = *it;
        const std::string state = order->get_state();

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
    }
}

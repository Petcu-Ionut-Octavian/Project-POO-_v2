//
// Created by User on 12/28/2025.
//

#include <utility>
#include <iostream>
#include <limits>

#include "../include/Order.h"

/// Constructors
Product::Product(std::string name, double grams)
    : name(std::move(name))
{
    while (true) {
        if (grams >= 150 && grams <= 800) {
            this->grams = grams;
            break;
        }

        std::cout << "Invalid grams (" << grams << "). Must be between 150 and 800. Re-enter: ";

        std::cin >> grams;

        // optional: handle cin failure
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            grams = -1; // force retry
        }
    }
}
Drink::Drink(std::string name, double grams, bool pet) : Product(std::move(name),grams), pet(pet) {}
Desert::Desert(std::string name, double grams, std::string serving_type) : Product(std::move(name), grams) {
    // validating serving_type
    while (true) {
        if (serving_type == "slice" ||
        serving_type == "cup" ||
        serving_type == "portion")
        {
            this->serving_type = serving_type;
            break;
        }

        std::cout << "Invalid serving type. Please choose one of: slice, cup, portion.\n";
        std::cout << "Enter serving type: ";
        std::cin >> serving_type;
    }
}



Burger::Burger(std::string name, double grams) : Product(std::move(name), grams) {
    std::cout << "Creating a burger\n";

    auto ask = [&](const std::string& text, const std::string& ingredient) {
        std::string choice;

        while (true) {
            std::cout << "[y/n] " << text;
            std::cin >> choice;

            if (choice == "y" || choice == "Y") {
                ingredients.push_back(ingredient);
                break;
            }
            else if (choice == "n" || choice == "N") {
                break;
            }
            else {
                std::cout << "Invalid input. Please type y or n.\n";
            }
        }
    };


    ask("Add extra beef patty? ", "beef patty");
    ask("Add extra lettuce? ", "lettuce");
    ask("Add extra tomato slices? ", "tomato slices");
    ask("Add extra cheddar cheese? ", "cheddar cheese");
    ask("Add extra onions? ", "onions");

    // If no ingredients were added, add a default one
    if (ingredients.empty()) {
        std::cout << "No ingredients selected.\n";
        ingredients.emplace_back("default");
    }

    std::cout << "Burger created with ingredients:\n";
    for (const auto& ing : ingredients)
        std::cout << " - " << ing << "\n";
}


/// Destructors
Product::~Product() = default;
Drink::~Drink() = default;
Desert::~Desert() = default;
Burger::~Burger() = default;

/// energy to make function
double Drink::energy_to_make() {
    if (this->pet) return 25;
    return this->grams * 0.25;
}

double Desert::energy_to_make() {
    if (this->serving_type == "slice") return 25;
    if (this->serving_type == "cup") return 2*this->grams;
    if (this->serving_type == "portion") return 0.5*this->grams;

    return 0;
}

double Burger::energy_to_make() {
    return this->grams * static_cast<double>(this->ingredients.size());
}


/// Order

static int read_int(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (!std::cin.fail())
            return value;

        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid number. Try again.\n";
    }
}

static double read_double(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (!std::cin.fail())
            return value;

        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid number. Try again.\n";
    }
}

static bool read_bool(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (!std::cin.fail() && (value == 0 || value == 1))
            return value;

        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid input. Enter 1 or 0.\n";
    }
}


Order::Order() : ID(++ID_generator), state("processing") {
    std::cout << "Creating order: " << this->ID << "\n\n";

    auto default_if_d = [](const std::string& name, const std::string& fallback) {
        return (name == "d" ? fallback : name);
    };

    while (true) {
        std::cout << "Choose product type:\n";
        std::cout << "1. Drink\n";
        std::cout << "2. Desert\n";
        std::cout << "3. Burger\n";
        std::cout << "0. Finish order\n";

        int choice = read_int("Your choice: ");

        if (choice == 0) {
            this->energy_until_done = this->energy_to_make();
            break;
        }

        if (choice == 1) {
            // DRINK
            std::string name;
            std::cout << "Drink name(d = default): ";
            std::cin >> name;

            name = default_if_d(name, "Water");

            double grams = read_double("Grams(150-800): ");
            bool pet = read_bool("Is PET? (1/0): ");

            products.push_back(new Drink(name, grams, pet));
        }
        else if (choice == 2) {
            // DESERT
            std::string name, serving;
            std::cout << "Desert name(d = default): ";
            std::cin >> name;

            name = default_if_d(name, "Cake");

            double grams = read_double("Grams(150-800): ");

            // Clear leftover newline
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Serving type (slice/cup/portion): ";
            std::cin >> serving;

            products.push_back(new Desert(name, grams, serving));
        }
        else if (choice == 3) {
            // BURGER
            std::string name;
            std::cout << "Burger name(d = default): ";
            std::cin >> name;

            name = default_if_d(name, "ClassicBurger");

            double grams = read_double("Grams(150-800): ");

            products.push_back(new Burger(name, grams));
        }
        else {
            std::cout << "Invalid option. Try again.\n";
        }
    }
}


Order::~Order() {
    for (auto p : products)
        delete p;
}

double Order::energy_to_make() const {
    double total = 0;

    for (auto p : products) {
        if (p != nullptr)
            total += p->energy_to_make();
    }

    return total;
}

void Order::next_state() {
    if (state == "processing") {
        state = "preparing";
    }
    else if (state == "preparing") {
        state = "delivering";
    }
    else if (state == "delivering") {
        std::cout << "Order already delivered!\n";
    }
}



std::ostream& operator<<(std::ostream& os, const Product& product) {
    product.print();   // call the virtual print() of the derived class
    return os;
}


void Drink::print() const {
    std::cout << name << " (" << grams << "g)"
              << " | PET: " << (pet ? "yes" : "no");
}

void Desert::print() const {
    std::cout << name << " (" << grams << "g)"
              << " | Serving: " << serving_type;
}

void Burger::print() const {
    std::cout << name << " (" << grams << "g)"
              << " | Ingredients: ";

    for (const auto& ing : ingredients) {
        std::cout << ing << " ";
    }
}


std::ostream& operator<<(std::ostream& os, const Order& ord) {
    os << "Order #" << ord.get_ID()
       << " | State: " << ord.get_state();

    if (ord.get_state() == "preparing") {
        os << " | Remaining: " << ord.get_remaining_energy();
    }

    // The products printing here
    os << "\nProducts:\n";
    for (auto* product : ord.products) {
        os << " - " << *product << "\n";
    }

    return os;
}




//
// Created by User on 12/28/2025.
//

#ifndef RESTAURANT_COMANDA_H
#define RESTAURANT_COMANDA_H

#include <string>
#include <vector>


class Product {
protected:
    std::string name;
    double grams;
public:
    Product(std::string name, double grams);
    virtual ~Product();
    virtual double energy_to_make() = 0;
};


class Drink final : public Product {
private:
    bool pet = false;   // pet nu e sticla
public:
    Drink(std::string name, double grams, bool pet);
    ~Drink() override;
    double energy_to_make() override;
};


class Desert final : public Product {
private:
    std::string serving_type; /// slice cup portion
public:
    Desert(std::string name, double grams, std::string serving_type);
    ~Desert() override;
    double energy_to_make() override;
};


class Burger final : public Product {
private:
    std::vector<std::string> ingredients;
public:
    Burger(std::string name, double grams);
    ~Burger() override;
    double energy_to_make() override;
};


class Order {
private:
    int ID;
    inline static int ID_generator = 0;
    std::vector<Product*> products;
    std::string state; // processing preparing delivering
    double energy_until_done;
public:
    Order();
    ~Order();
    [[nodiscard]] double energy_to_make() const;
    void next_state();

    [[nodiscard]] int get_ID() const { return ID; }
    [[nodiscard]] const std::string& get_state() const { return state; }
    [[nodiscard]] double get_remaining_energy() const { return energy_until_done; }

    void set_remaining_energy(double amount) { energy_until_done = amount;}

};

#endif //RESTAURANT_COMANDA_H
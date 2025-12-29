//
// Created by User on 12/28/2025.
//

#include <iostream>

#include "../include/Employer.h"

Employer::Employer() : energy(100), ID(++ID_generator) {}
Cashier::Cashier() = default;
Cook::Cook() = default;
Delivery::Delivery() = default;

Employer::~Employer() = default;
Cashier::~Cashier() = default;
Cook::~Cook() = default;
Delivery::~Delivery() = default;





void Employer::process(Order &order) {
    std::cout << this->get_role() << " (ID: " << this->getID() << ") " << "processing order " << order.get_ID() << "...\n";

    this->energy -= 100;
    this->used = true;
    order.next_state();
}

void Employer::prepare(Order &order) {
    std::cout << this->get_role() << " (ID: " << this->getID() << ") " << "preparing order: "<<order.get_ID()<<"\n";
    this->used = true;

    double remaining = order.get_remaining_energy();

    // Case 1: employer has LESS energy than the order needs
    if (this->energy < remaining) {
        // Employer uses all his energy
        order.set_remaining_energy(remaining - this->energy);
        this->energy = 0;
        return; // order stays in "preparing"
    }

    // Case 2: employer has ENOUGH energy
    // Use exactly what the order needs
    this->energy -= remaining;
    order.set_remaining_energy(0);

    // Order is now fully prepared → go to next state
    order.next_state();
}

void Employer::deliver(Order &order) {
    std::cout << this->get_role() << " (ID: " << this->getID() << ") " << "delivering order: "<<order.get_ID()<<"\n";
    this->used = true;
    this->energy -= 100;
}

void Employer::reset() {
    this->energy = 100;
    this->used = false;
}

std::string Employer::get_role() const {
    if (dynamic_cast<const Cook*>(this))      return "Cook";
    if (dynamic_cast<const Cashier*>(this))   return "Cashier";
    if (dynamic_cast<const Delivery*>(this))  return "Delivery";
    return "Employer";
}


double Employer::getEnergy() const {
    return energy;
}

bool Employer::getUsed() const {
    return used;
}

int Employer::getID() const {
    return ID;
}


void Cashier::process(Order &order) {
    std::cout << this->get_role() << " (ID: " << this->getID() << ") " << "processing order: "<<order.get_ID()<<"\n";
    this->energy -= 25;
    this->used = true;
    order.next_state();
}

void Delivery::deliver(Order &order) {
    std::cout << this->get_role() << " (ID: " << this->getID() << ") " << "delivering order: "<<order.get_ID()<<"\n";
    this->used = true;
    this->energy -= 25;
}

void Cook::prepare(Order &order) {
    std::cout << this->get_role() << " (ID: " << this->getID() << ") " << "preparing order: "<<order.get_ID()<<"\n";
    this->used = true;

    double remaining = order.get_remaining_energy();

    // Cook's special ability: 1 energy = 2 effective energy
    double effective_power = this->energy * 2;

    // Case 1: Cook can finish the order
    if (effective_power >= remaining) {
        // How much real energy does he need to spend?
        double real_energy_needed = remaining / 2.0;

        // Spend only what is needed
        this->energy -= real_energy_needed;

        // Order is done preparing
        order.set_remaining_energy(0);
        order.next_state();
        return;
    }

    // Case 2: Cook cannot finish the order
    // He uses all his energy → reduces remaining by double
    order.set_remaining_energy(remaining - effective_power);

    // Cook is exhausted
    this->energy = 0;
}

void Cook::reset() {
    this->energy += 100;
    this->used = false;
}

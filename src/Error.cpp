//
// Created by User on 12/29/2025.
//

#include <utility>

#include "../include/Error.h"

// ---------- team_empty ----------

team_empty::team_empty(std::string  msg)
    : message(std::move(msg)) {}

const char* team_empty::what() const noexcept {
    return message.c_str();
}

// ---------- no_more_orders ----------

no_more_orders::no_more_orders(std::string  msg)
    : message(std::move(msg)) {}

const char* no_more_orders::what() const noexcept {
    return message.c_str();
}


// ---------- order_empty ----------

order_empty::order_empty(std::string msg)
    : message(std::move(msg)) {}

const char* order_empty::what() const noexcept {
    return message.c_str();
}

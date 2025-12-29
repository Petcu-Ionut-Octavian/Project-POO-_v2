//
// Created by User on 12/29/2025.
//

#include "../include/Error.h"

// ---------- team_empty ----------

team_empty::team_empty(const std::string& msg)
    : message(msg) {}

const char* team_empty::what() const noexcept {
    return message.c_str();
}

// ---------- no_more_orders ----------

no_more_orders::no_more_orders(const std::string& msg)
    : message(msg) {}

const char* no_more_orders::what() const noexcept {
    return message.c_str();
}
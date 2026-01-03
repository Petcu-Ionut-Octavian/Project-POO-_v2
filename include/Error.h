#ifndef RESTAURANT_ERROR_H
#define RESTAURANT_ERROR_H

#include <exception>
#include <string>

class team_empty : public std::exception {
public:
    explicit team_empty(std::string  msg = "Team is empty");

    [[nodiscard]] const char* what() const noexcept override;

private:
    std::string message;
};

class no_more_orders : public std::exception {
public:
    explicit no_more_orders(std::string  msg = "No more orders available");

    [[nodiscard]] const char* what() const noexcept override;

private:
    std::string message;
};

class order_empty : public std::exception {
public:
    explicit order_empty(std::string msg = "Order is empty");

    [[nodiscard]] const char* what() const noexcept override;

private:
    std::string message;
};

#endif // RESTAURANT_ERROR_H
//
// Created by User on 12/28/2025.
//

#ifndef RESTAURANT_EMPLOYER_H
#define RESTAURANT_EMPLOYER_H

#include "Order.h"

class Employer {
protected:
    double energy = 0;
    bool used = false;
public:
    Employer();
    virtual ~Employer();
    virtual void process(Order& order);
    virtual void prepare(Order& order);
    virtual void deliver(Order& order);
    virtual void reset();

    [[nodiscard]] std::string get_role() const;
    [[nodiscard]] double getEnergy() const;
    [[nodiscard]] bool getUsed() const;

};

class Cashier final : public Employer {
public:
    void process(Order& order) override;
};
class Delivery final : public Employer {
public:
    void deliver(Order& order) override;
};
class Cook final : public Employer {
public:
    void prepare(Order& order) override;
    void reset() override;
};



#endif //RESTAURANT_EMPLOYER_H
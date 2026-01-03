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
    int ID;
    inline static int ID_generator = 0;
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
    [[nodiscard]] int getID() const;

    void setUsed(bool _used);

    friend std::ostream& operator<<(std::ostream& os, const Employer& emp);

};

class Cashier final : public Employer {
public:
    Cashier();
    ~Cashier() override;
    void process(Order& order) override;
};
class Delivery final : public Employer {
public:
    Delivery();
    ~Delivery() override;
    void deliver(Order& order) override;
};
class Cook final : public Employer {
public:
    Cook();
    ~Cook() override;
    void prepare(Order& order) override;
    void reset() override;
};



#endif //RESTAURANT_EMPLOYER_H
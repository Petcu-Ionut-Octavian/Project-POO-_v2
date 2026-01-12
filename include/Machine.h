#ifndef RESTAURANT_MACHINE_H
#define RESTAURANT_MACHINE_H

class Machine {
private:
    int ID;
    inline static int ID_generator = 0;

    int max_energy;
    int energy;
    bool need_fix;
    bool used = false;

public:

    Machine() : ID(++ID_generator), max_energy(100), energy(100), need_fix(false), used(false) {};
    ~Machine() = default;

    void reset() {
        this->used = false;
    }

    void use() {
        this->used = true;
        this->energy = this->energy -20;
        if(this->energy < 20) { need_fix = true; }
    }

    bool can_work() const {
        return !this->need_fix;
    }

    void fix() {
        this->used = false;
        this->energy = this->max_energy;
        this->need_fix = false;
    }

    [[nodiscard]] int get_ID() const {
        return this->ID;
    }
}


#endif //RESTAURANT_MACHINE_H
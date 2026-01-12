#include <iostream>

#include "../include/Machine.h"


std::ostream& operator<<(std::ostream& os, const Machine& machine){
        os<<"Machine (ID = " << machine.ID << ") (Energy " << machine.energy << "/" << machine.max_energy << ") Used: " << machine.used << " Need fix: " << machine.need_fix;
        return os;
    }
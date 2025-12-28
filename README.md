🍔 Restaurant Simulation System
A C++ OOP Project
This project is a fully interactive restaurant workflow simulator built in modern C++. It models the real‑world pipeline of a fast‑food restaurant, where orders move through multiple stages and are handled by different types of employees with unique roles, energy levels, and behaviors.
The simulation is designed around clean object‑oriented architecture, state‑driven order processing, and a role‑priority execution model that ensures realistic and deterministic behavior.

🎯 Features
✔ Dynamic Team Building
At the start of the simulation, the player assembles a team of employees using a point‑based system:
- Cook – prepares food
- Cashier – processes new orders
- Delivery – delivers completed orders
Each employee has:
- Energy
- A role
- A “used” flag per cycle
- Role‑specific actions

🧾 Order System
Orders are composed of multiple products:
- Drinks
- Deserts
- Burgers (with customizable ingredients)
Each order has:
- A unique ID
- A state (processing → preparing → delivering)
- A total required energy
- Remaining energy that decreases as employees work on it

🔄 Simulation Cycle
Each cycle consists of:
- Team reset
All employees start as “not used”.
- Order intake
The user can add new orders or skip.
- Role‑based processing
The simulation runs in strict order:
- Cashiers handle processing
- Cooks handle preparing
- Delivery handles delivering
- Fallback logic
If an employee’s optimal state is unavailable, they take the first available order and perform the correct action for its current state.
- Order completion
Delivery employees remove finished orders from the system.
- Cycle summary
The system prints the team status and remaining orders.

🧠 Core Logic Highlights
✔ Role‑priority execution
Employees are processed one by one.
Each employee:
- Searches for the first order in their optimal state
- If none exist, they take the first available order and perform the correct action
- Delivery deletes orders safely
- No employee touches a deleted order
✔ State‑driven order progression
Orders automatically transition through:
processing → preparing → delivering → completed


✔ Energy‑based work
Each action consumes energy.
Employees cannot work once their energy reaches zero.

🏗 Object‑Oriented Architecture
The project uses:
- Inheritance for employee types
- Polymorphism for actions (process, prepare, deliver)
- Encapsulation for order and product data
- Dynamic memory management with safe deletion
- Iterators for order traversal and removal

🎮 Interactive Console UI
The simulation runs entirely in the console with:
- Menus
- Order creation prompts
- Ingredient selection
- Cycle summaries
- Real‑time feedback on employee actions

🚀 Why This Project Is Interesting
This project demonstrates:
- Clean OOP design
- Realistic simulation logic
- State machines
- Memory‑safe container manipulation
- Role‑based task assignment
- Dynamic user interaction
It’s a great example of how to model a real‑world workflow using C++ classes, polymorphism, and simulation loops.























## Instrucțiuni de compilare

Proiectul este configurat cu CMake.

Instrucțiuni pentru terminal:

1. Pasul de configurare
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
# sau ./scripts/cmake.sh configure
```

Sau pe Windows cu GCC:
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -G Ninja
# sau ./scripts/cmake.sh configure -g Ninja
```

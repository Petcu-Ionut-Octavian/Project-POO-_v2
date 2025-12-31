#ifndef RESTAURANT_EVENTS_H
#define RESTAURANT_EVENTS_H

#include <random>

template<typename Func>
void trigger_event(double probability, Func event) {
    // Thread-safe, static random engine
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_real_distribution<double> dist(0.0, 1.0);

    if (dist(rng) < probability)
        event();
}

#endif // RESTAURANT_EVENTS_H
//
// Created by simone on 07/06/25.
//

#ifndef MINECRAFT_TIMER_HPP
#define MINECRAFT_TIMER_HPP


#include <chrono>

class Timer {
public:
    Timer();

    long long elapsed();

    void reset();

private:

    std::chrono::steady_clock::time_point start_time;
};


#endif //MINECRAFT_TIMER_HPP

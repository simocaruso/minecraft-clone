//
// Created by simone on 07/06/25.
//

#include "timer.hpp"

Timer::Timer() {
    reset();
}

void Timer::reset() {
    start_time = std::chrono::steady_clock::now();
}

long long Timer::elapsed()  {
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time).count();
}


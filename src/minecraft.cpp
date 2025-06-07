//
// Created by simone on 07/06/25.
//

#include <thread>
#include "minecraft.hpp"
#include "timer.hpp"
#include "iostream"

void Minecraft::start() {
    run_game_loop();
}

void Minecraft::run_game_loop() {
    Timer frame_time;
    const int FPS = 30;
    int frame_duration = 1000 / FPS;
    for (;;) {
        std::cout << "Starting a frame.\n";
        frame_time.reset();

        if (frame_time.elapsed() < frame_duration) {
            std::this_thread::sleep_for(std::chrono::milliseconds(frame_duration - frame_time.elapsed()));
        }
        std::cout << "Frame finished. Elapsed time: " << frame_time.elapsed() << std::endl;
    }
}

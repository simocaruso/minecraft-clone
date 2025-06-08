//
// Created by simone on 07/06/25.
//

#include <thread>
#include "minecraft.hpp"
#include "timer.hpp"
#include "iostream"
#include "systems/rendering_system.hpp"

void Minecraft::start() {
    init_systems();
    run_game_loop();
}

void Minecraft::run_game_loop() {
    Timer frame_time;
    const int FPS = 30;
    int frame_duration = 1000 / FPS;
    int elapsed;
    for (;;) {
        std::cout << "Starting a frame.\n";
        elapsed = frame_time.elapsed();
        frame_time.reset();

        for (auto &sys: systems) {
            sys.second->update(elapsed);
        }

        if (frame_time.elapsed() < frame_duration) {
            std::this_thread::sleep_for(std::chrono::milliseconds(frame_duration - frame_time.elapsed()));
        }
        std::cout << "Frame finished. Elapsed time: " << frame_time.elapsed() << std::endl;
    }
}

void Minecraft::init_systems() {
    systems[RENDERING] = std::make_unique<RenderingSystem>(registry);
}

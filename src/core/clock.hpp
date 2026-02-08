#pragma once
#include <chrono>
struct Clock {
    inline static constexpr float stepTime = 0.2f;
    inline static float accumulator1 = 0.f;
    inline static float accumulator2 = 0.f;

    inline static unsigned int frames = 0;

    inline static std::chrono::steady_clock::time_point lastTime;
    inline static std::chrono::steady_clock::time_point currentTime;
    inline static std::chrono::duration<float> delta;

    static void startTime() {
        lastTime = std::chrono::steady_clock::now();
    }

    static void calculateTime() {
        currentTime = std::chrono::steady_clock::now();
        delta = currentTime - lastTime;
        lastTime = currentTime;

        accumulator1 += delta.count();

        accumulator2 += delta.count();
        ++frames;
    }
};
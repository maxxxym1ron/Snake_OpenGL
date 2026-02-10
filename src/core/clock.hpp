#pragma once
#include <chrono>
struct Clock {
    inline static constexpr float stepTime = 0.2f;
    inline static float gameUpdateAccumulator = 0.f;
    inline static float fpsAccumulator = 0.f;

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

        gameUpdateAccumulator += delta.count();
        fpsAccumulator += delta.count();
        ++frames;
    }
};
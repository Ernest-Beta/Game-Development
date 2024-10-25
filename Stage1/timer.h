#pragma once
#include<chrono>
#include<iostream>
class Timer {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    bool running = false;

public:
    Timer() {}

    //start the timer
    void start() {
        start_time = std::chrono::high_resolution_clock::now();
        running = true;
 
    }

    //get the elapsed time in seconds
    double getElapsedTime() {
        if (running) {
            auto elapsed = std::chrono::high_resolution_clock::now() - start_time;
            return std::chrono::duration<double>(elapsed).count();
        }
        return 0.0;
    }
};


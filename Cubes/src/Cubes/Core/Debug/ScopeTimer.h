#pragma once
#include <chrono>
#include <iostream>

namespace Cubes {

    class ScopeTimer {
    public:
        ScopeTimer(const char* name)
            : _name(name), _stopped(false)
        {
            _startTimepoint = std::chrono::high_resolution_clock::now();
        }

        ~ScopeTimer() {
            Stop();
        }

        void Stop() {
            if (_stopped)
                return;

            auto endTimepoint = std::chrono::high_resolution_clock::now();
            double duration = std::chrono::duration_cast<std::chrono::microseconds>(endTimepoint - _startTimepoint).count() * 0.001;

            _stopped = true;
        }

    private:
        std::chrono::high_resolution_clock::time_point _startTimepoint;
        bool _stopped;
        const char* _name;
    };

}
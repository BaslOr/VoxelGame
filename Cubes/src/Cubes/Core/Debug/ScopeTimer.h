#pragma once
#include <chrono>

namespace Cubes {

	class ScopeTimer {
	public:
		ScopeTimer() {
			_startTime = std::chrono::high_resolution_clock::now();
		}

		~ScopeTimer() {
			std::chrono::time_point<std::chrono::high_resolution_clock> endTime = std::chrono::high_resolution_clock::now();
			//std::chrono::duration<std::chrono::high_resolution_clock, std::chrono::microseconds> duration = endTime - _startTime;
		}



	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> _startTime;

	};

}

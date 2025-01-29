#pragma once
#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include "../Core.h"


namespace Cubes {

	class CB_API Log
	{
	public:
		static void init();

		inline static std::shared_ptr<spdlog::logger> GetCoreLogger() { return _coreLogger; }
		inline static std::shared_ptr<spdlog::logger> GetClientLogger() { return _clientLogger; }

	private:
		inline static std::shared_ptr<spdlog::logger> _coreLogger;
		inline static std::shared_ptr<spdlog::logger> _clientLogger;
	};

}

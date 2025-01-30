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

//Engine Logger Makros
#define CB_CORE_ERROR(...) ::Cubes::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CB_CORE_WARN(...)  ::Cubes::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CB_CORE_INFO(...)  ::Cubes::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CB_CORE_TRACE(...) ::Cubes::Log::GetCoreLogger()->trace(__VA_ARGS__)


//Client Log Makros
#define CB_ERROR(...) ::Cubes::Log::GetClientLogger()->error(__VA_ARGS__)
#define CB_WARN(...)  ::Cubes::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CB_INFO(...)  ::Cubes::Log::GetClientLogger()->info(__VA_ARGS__)
#define CB_TRACE(...) ::Cubes::Log::GetClientLogger()->trace(__VA_ARGS__)

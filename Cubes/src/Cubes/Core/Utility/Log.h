#pragma once
#pragma warning(push)
#pragma warning(disable: 26498)
#pragma warning(push)
#pragma warning(disable: 26800)
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#pragma warning(pop)
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
#define CB_CORE_LOG_ERROR(...) ::Cubes::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CB_CORE_LOG_WARN(...)  ::Cubes::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CB_CORE_LOG_INFO(...)  ::Cubes::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CB_CORE_LOG_TRACE(...) ::Cubes::Log::GetCoreLogger()->trace(__VA_ARGS__)


//Client Log Makros
#define CB_LOG_ERROR(...) ::Cubes::Log::GetClientLogger()->error(__VA_ARGS__)
#define CB_LOG_WARN(...)  ::Cubes::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CB_LOG_INFO(...)  ::Cubes::Log::GetClientLogger()->info(__VA_ARGS__)
#define CB_LOG_TRACE(...) ::Cubes::Log::GetClientLogger()->trace(__VA_ARGS__)

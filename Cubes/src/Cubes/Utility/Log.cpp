#include "cbpch.h"
#include "Log.h"

namespace Cubes {

	void Log::init()
	{	
		spdlog::set_pattern("%^[%T] %n: %v%$");
		_coreLogger = spdlog::stdout_color_mt("Cubes");
		_coreLogger->set_level(spdlog::level::trace);

		_clientLogger = spdlog::stdout_color_mt("Voxel Game");
		_clientLogger->set_level(spdlog::level::trace);
	}
}

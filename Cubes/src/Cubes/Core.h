#include "Utility/Log.h"

#ifdef CB_PLATFORM_WINDOWS
    #ifdef CB_BUILD_DYNAMIC
        #ifdef CB_BUILD_DLL
            #define CB_API _declspec(dllexport)
        #else
            #define CB_API _declspec(dllimport)
        #endif // CB_BUILD_DLL
    #else
        #define CB_API
    #endif // CB_BUILD_DYNAMIC
#else
#error Cubes only supports Windows!
#endif // CB_PLATFORM_WINDOWS

//TODO: Only enable in Debug buils
#define CB_ASSERT(x, ...) { if(!(x)) { CB_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define CB_CORE_ASSERT(x, ...) { if(!(x)) { CB_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

#define BIT(x) 1 >> x

#define CB_BIND_EVENT_FUNC(fn) std::bind(&fn, this, std::placeholders::_1)

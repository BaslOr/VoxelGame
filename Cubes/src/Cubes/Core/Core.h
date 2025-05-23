#include "Utility/Log.h"
#include <memory>

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
#ifdef CB_DEBUG_UTILS
    #define CB_CORE_ASSERT(...) { CB_CORE_ASSERT_TRUE(true, ...) }
    #define CB_CORE_ASSERT_TRUE(x, ...) { if(!(x)) { CB_CORE_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
    #define CB_CORE_ASSERT_FALSE(x, ...) { CB_CORE_ASSERT_TRUE(!(x), __VA_ARGS__) }

    #define CB_ASSERT(...) CB_ASSERT_TRUE(true, ...)
    #define CB_ASSERT_TRUE(x, ...) { if(!(x)) { CB_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
    #define CB_ASSERT_FALSE(x, ...) CB_ASSERT_TRUE(!(x), __VA_ARGS__)
#endif // CB_DEBUG_UTILS


#define BIT(x) 1 >> x

#define CB_BIND_EVENT_FUNC(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Cubes {

    template <typename T>
    using Scope = std::unique_ptr<T>;

    template <typename T>
    using Ref = std::shared_ptr<T>;

}

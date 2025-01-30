#ifdef CB_PLATFORM_WINDOWS
	#ifdef CB_BUILD_DLL
		#define CB_API _declspec(dllexport)
	#else
		#define CB_API _declspec(dllimport)
	#endif // CB_BUILD_DLL
#else
#error Cubes only supports Windows!
#endif // CB_PLATFORM_WINDOWS

#define BIT(x) 1 >> x


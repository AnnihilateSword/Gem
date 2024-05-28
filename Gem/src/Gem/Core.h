#pragma once

#ifdef GEM_PLATFORM_WINDOWS
	#ifdef GEM_BUILD_DLL
		#define GEM_API __declspec(dllexport)
	#else
		#define GEM_API __declspec(dllimport)
	#endif
#else
	#error Gem only supports Windows!
#endif

#define BIT(x) (1 << x)
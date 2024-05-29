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

#ifdef GEM_ENABLE_ASSERTS
	#define GEM_ASSERT(x, ...) { if(!(x)) { GEM_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define GEM_CORE_ASSERT(x, ...) { if(!(x)) { GEM_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define GEM_ASSERT(x, ...)
	#define GEM_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define GEM_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
#pragma once

#ifdef ZAO_PLATFORM_WINDOWS
	#ifdef ZAO_BUILD_DLL
		#define ZAO_API __declspec(dllexport)
	#else
		#define ZAO_API __declspec(dllimport)
	#endif
#else
	#error	Zao is only for Windows
#endif

#ifdef ZAO_ENABLE_ASSERTS
//a bracket is needed to make the macro work correctly
	#define ZAO_CORE_ASSERT(x, ...) if (!(x)) { ZAO_CORE_ERRER("Assertion faild: {0}", __VA_ARGS__); __debugbreak(); }  
	#define ZAO_ASSERT(x, ...) if (!(x)) { ZAO_ERRER("Assertion faild: {0}", __VA_ARGS__); __debugbreak(); }
#else
	#define ZAO_CORE_ASSERT(x, ...)
	#define ZAO_ASSERT(x, ...) 
#endif

//used to create a mask
#define BIT(x) (1 << x)
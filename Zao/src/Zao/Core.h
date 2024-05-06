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
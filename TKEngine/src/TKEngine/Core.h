#pragma once

#ifdef TK_PLATFORM_WINDOWS

#ifdef TK_BUILD_DLL
#define TK_API __declspec(dllexport)
#else
#define TK_API __declspec(dllimport)
#endif // TK_BUILD_DLL

#else
#error TK only support Windows!
#endif // TK_PLATFORM_WINDOWS

#define BIT(x) (1 << x)
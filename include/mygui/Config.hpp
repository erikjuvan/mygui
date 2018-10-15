#pragma once

#if defined(_WIN32)

#define MYGUI_WINDOWS

#elif defined(__unix__)

#if defined(__linux__)
#define MYGUI_LINUX
#else
#error Only Linux of Unix type OS is supported by mygui library
#endif

#else

#error This operating system is not supported by mygui library

#endif

#if defined(MYGUI_WINDOWS)

#if defined(MYGUI_EXPORTS)
#define MYGUI_API __declspec(dllexport)
#else
#define MYGUI_API __declspec(dllimport)
#endif

#elif defined(MYGUI_LINUX)

#define MYGUI_API __attribute__((__visibility__("default")))

#endif
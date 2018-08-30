#pragma once

#if defined(MYGUI_EXPORTS)
	#define MYGUI_API __declspec(dllexport)
#else
	#define MYGUI_API __declspec(dllimport)
#endif
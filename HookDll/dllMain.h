#pragma once
#include <Windows.h>

extern "C"
{
	__declspec(dllexport) LRESULT WINAPI MouseProc(int nCode, WPARAM wParam, LPARAM lParam);
}

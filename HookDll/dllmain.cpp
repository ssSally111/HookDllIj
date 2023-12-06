#include "pch.h"
#include <psapi.h>
#include "dllMain.h"

LRESULT WINAPI MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case WM_LBUTTONDOWN:
		// ...
		OutputDebugString(L"HookDll BUTTONDOWN");
		break;
	default:
		break;
	}

	return CallNextHookEx(0, nCode, wParam, lParam);
}


DWORD WINAPI  Hax(LPVOID lpParameter)
{
	OutputDebugString(L"HookDll hax...");

	WCHAR szProcessName[MAX_PATH];
	GetProcessImageFileName(GetModuleHandle(NULL), szProcessName, MAX_PATH);

	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		OutputDebugString(L"HookDll ATTACH");
		CloseHandle(CreateThread(NULL, 0, Hax, NULL, 0, NULL));
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


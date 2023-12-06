#include <Windows.h>
#include <iostream>
#include <thread>

HMODULE g_hModule;
HHOOK g_hHook = NULL;

void Hook(WCHAR dllPath[])
{
	if (g_hHook) return;

	g_hModule = LoadLibrary(dllPath);
	if (!g_hModule)
	{
		std::cout << "LoadLibrary Fail..." << std::endl;
		return;
	}

	HOOKPROC pfn = (HOOKPROC)GetProcAddress(g_hModule, "MouseProc");

	g_hHook = SetWindowsHookEx(WH_MOUSE, pfn, g_hModule, 0);
	std::cout << "Hook" << std::endl;

	// 处理消息,否则程序会卡死
	MSG msg;
	while (1)
	{
		if (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
		else
			Sleep(0);
	}
}

void UnHook()
{
	if (g_hHook)
	{
		UnhookWindowsHookEx(g_hHook);
		g_hHook = NULL;
		FreeLibrary(g_hModule);
		std::cout << "UnHook" << std::endl;
	}
}

DWORD WINAPI ThreadProc(PVOID pParam)
{
	WCHAR dllPath[MAX_PATH];
	swprintf(dllPath, MAX_PATH, L"%hs", (char*)pParam);
	Hook(dllPath);

	return 0;
}

int main(int argc, char* argv[])
{
	CloseHandle(CreateThread(NULL, 0, ThreadProc, argv[1], 0, NULL));

	system("pause");
	UnHook();

	return 0;
}

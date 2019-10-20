#pragma once

#include <Windows.h>

HMODULE           WINAPI     Hooks_LoadLibraryExW(LPCWSTR, HANDLE, DWORD);
HMODULE           WINAPI     Hooks_LoadLibraryExW_SteamClient(LPCWSTR, HANDLE, DWORD);
FARPROC           WINAPI     Hooks_GetProcAddress(HMODULE, LPCSTR);
VOID              WINAPI     Hooks_GetSystemInfo(LPSYSTEM_INFO);
BOOL              WINAPI     Hooks_GetVersionExA(LPOSVERSIONINFOEXA);
UINT              WINAPI     Hooks_GetSystemDirectoryW(LPWSTR, UINT);
UINT              WINAPI     Hooks_GetWindowsDirectoryW(LPWSTR, UINT);
DWORD             WINAPI     Hooks_GetCurrentProcessId(VOID);
DWORD             WINAPI     Hooks_GetCurrentThreadId(VOID);

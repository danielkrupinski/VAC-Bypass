#include <Windows.h>

#include "Hooks.h"
#include "Utils.h"

HMODULE WINAPI Hooks_LoadLibraryExW(LPCWSTR lpLibFileName, HANDLE hFile, DWORD dwFlags)
{
    HMODULE result = LoadLibraryExW(lpLibFileName, hFile, dwFlags);

    Utils_hookImport(lpLibFileName, "kernel32.dll", "GetProcAddress", Hooks_GetProcAddress);
    Utils_hookImport(lpLibFileName, "kernel32.dll", "GetSystemInfo", Hooks_GetSystemInfo);

    return result;
}

FARPROC WINAPI Hooks_GetProcAddress(HMODULE hModule, LPCSTR lpProcName)
{
    FARPROC result = GetProcAddress(hModule, lpProcName);
 
    if (result) {
        if (!strcmp(lpProcName, "GetProcAddress"))
            return (FARPROC)Hooks_GetProcAddress;
        else if (!strcmp(lpProcName, "GetSystemInfo"))
            return (FARPROC)Hooks_GetSystemInfo;
    }
    return result;
}

VOID WINAPI Hooks_GetSystemInfo(LPSYSTEM_INFO lpSystemInfo)
{
    GetSystemInfo(lpSystemInfo);
    lpSystemInfo->dwPageSize = 1337;
}

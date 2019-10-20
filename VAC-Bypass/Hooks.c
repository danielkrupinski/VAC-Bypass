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

HMODULE WINAPI Hooks_LoadLibraryExW_SteamClient(LPCWSTR lpLibFileName, HANDLE hFile, DWORD dwFlags)
{
    HMODULE result = LoadLibraryExW(lpLibFileName, hFile, dwFlags);

    if (wcsstr(lpLibFileName, L"steamui.dll")) {
        Utils_hookImport(lpLibFileName, "kernel32.dll", "LoadLibraryExW", Hooks_LoadLibraryExW_SteamClient);
    } else if (wcsstr(lpLibFileName, L"steamservice.dll")) {
        PBYTE toPatch = Utils_findPattern(L"steamservice", "\x74\x47\x6A\x01\x6A", 0);
        if (toPatch) {
            DWORD old;
            VirtualProtect(toPatch, 1, PAGE_EXECUTE_READWRITE, &old);
            *toPatch = 0xEB;
            VirtualProtect(toPatch, 1, old, &old);
            Utils_hookImport(L"steamservice", "kernel32.dll", "LoadLibraryExW", Hooks_LoadLibraryExW);
            MessageBoxW(NULL, L"Initialization was successful! (VAC Bypass Loader)", L"VAC bypass", MB_OK | MB_ICONINFORMATION);
        }
    }
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
        else if (!strcmp(lpProcName, "GetVersionExA"))
            return (FARPROC)Hooks_GetVersionExA;
        else if (!strcmp(lpProcName, "GetSystemDirectoryW"))
            return (FARPROC)Hooks_GetSystemDirectoryW;
        else if (!strcmp(lpProcName, "GetWindowsDirectoryW"))
            return (FARPROC)Hooks_GetWindowsDirectoryW;
        else if (!strcmp(lpProcName, "GetCurrentProcessId"))
            return (FARPROC)Hooks_GetCurrentProcessId;
        else if (!strcmp(lpProcName, "GetCurrentThreadId"))
            return (FARPROC)Hooks_GetCurrentThreadId;
    }
    return result;
}

VOID WINAPI Hooks_GetSystemInfo(LPSYSTEM_INFO lpSystemInfo)
{
    GetSystemInfo(lpSystemInfo);
    lpSystemInfo->dwPageSize = 1337;
}

BOOL WINAPI Hooks_GetVersionExA(LPOSVERSIONINFOEXA lpVersionInformation)
{
    MessageBoxW(NULL, L"Bypass malfunction detected! Steam will close...", L"VAC bypass", MB_OK | MB_ICONERROR);
    ExitProcess(1);
    return FALSE;
}

UINT WINAPI Hooks_GetSystemDirectoryW(LPWSTR lpBuffer, UINT uSize)
{
    MessageBoxW(NULL, L"Bypass malfunction detected! Steam will close...", L"VAC bypass", MB_OK | MB_ICONERROR);
    ExitProcess(1);
    return 0;
}

UINT WINAPI Hooks_GetWindowsDirectoryW(LPWSTR lpBuffer, UINT uSize)
{
    MessageBoxW(NULL, L"Bypass malfunction detected! Steam will close...", L"VAC bypass", MB_OK | MB_ICONERROR);
    ExitProcess(1);
    return 0;
}

DWORD WINAPI Hooks_GetCurrentProcessId(VOID)
{
    return 0;
}

DWORD WINAPI Hooks_GetCurrentThreadId(VOID)
{
    return 0;
}

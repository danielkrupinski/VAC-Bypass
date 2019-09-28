#include "Hooks.h"
#include "Utils.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        if (GetModuleHandleW(L"steamservice")) {
            PBYTE toPatch = Utils_findPattern(L"steamservice", "\x74\x47\x6A\x01\x6A", 0);
            if (toPatch) {
                DWORD old;
                VirtualProtect(toPatch, 1, PAGE_EXECUTE_READWRITE, &old);
                *toPatch = 0xEB;
                VirtualProtect(toPatch, 1, old, &old);
                Utils_hookImport(L"steamservice", "kernel32.dll", "LoadLibraryExW", Hooks_LoadLibraryExW);
                MessageBoxW(NULL, L"Initialization was successful!", L"VAC bypass", MB_OK | MB_ICONINFORMATION);
            }
        } else {
            Utils_hookImport(NULL, "kernel32.dll", "LoadLibraryExW", Hooks_LoadLibraryExW_SteamClient);
        }
        DisableThreadLibraryCalls(hModule);
    }
    return TRUE;
}

#pragma once

#include <Windows.h>

PVOID Utils_findPattern(PCWSTR, PCSTR, SIZE_T);
VOID Utils_hookImport(PCWSTR, PCSTR, PCSTR, PVOID);

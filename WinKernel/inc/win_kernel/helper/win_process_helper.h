#pragma once

#include <Windows.h>
#include <TlHelp32.h>

namespace win_kernel
{
	PROCESSENTRY32* GetProcess(const wchar_t* processName);
}

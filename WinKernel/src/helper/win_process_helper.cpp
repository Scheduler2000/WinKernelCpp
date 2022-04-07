#include "win_kernel/helper/win_process_helper.h"

#include <iostream>

namespace win_kernel
{
	PROCESSENTRY32* GetProcess(const wchar_t* processName)
	{
		HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		if (hSnap == INVALID_HANDLE_VALUE)
			return nullptr;

		PROCESSENTRY32* process = nullptr;

		auto* processEntry = new PROCESSENTRY32();
		processEntry->dwSize = sizeof(PROCESSENTRY32);

		if (Process32First(hSnap, processEntry))
		{
			do
			{
				if (!_wcsicmp(processEntry->szExeFile, processName))
				{
					process = processEntry;
					break;
				}
			}
			while (Process32Next(hSnap, processEntry));
		}

		if (process == nullptr)
			delete processEntry;

		CloseHandle(hSnap);
		return process;
	}
}

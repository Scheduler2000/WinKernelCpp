#pragma once

#include <string_view>
#include <Windows.h>
#include <TlHelp32.h>

#include "win_kernel/memory/win_memory_reader.h"
#include "win_kernel/memory/win_memory_writer.h"

namespace win_kernel
{
	class WinProcess
	{
		private:
			PROCESSENTRY32* m_process;
			HANDLE m_handle;

			WinMemoryReader* m_processReader;
			WinMemoryWriter* m_processWriter;

		public:
			WinProcess(PROCESSENTRY32* process, DWORD desiredAccess);

			WinProcess(PROCESSENTRY32* process);

			~WinProcess();

			WCHAR* GetProcessName() const;

			DWORD GetProcessId() const;

			HANDLE GetProcessHandle() const;

			WinMemoryReader* GetProcessReader() const;

			WinMemoryWriter* GetProcessWriter() const;

			bool IsActive() const;

			MODULEENTRY32* FetchModule(const wchar_t* moduleName) const;

			bool InjectDll(const char* moduleName) const;
	};
}

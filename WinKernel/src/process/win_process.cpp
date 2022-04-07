#include "win_kernel/process/win_process.h"

#include <format>


namespace win_kernel
{
	WinProcess::WinProcess(PROCESSENTRY32* process, DWORD desiredAccess) : m_process(process)
	{
		m_handle = OpenProcess(desiredAccess, false, process->th32ProcessID);

		m_processReader = new WinMemoryReader(m_handle);
		m_processWriter = new WinMemoryWriter(m_handle);
	}

	WinProcess::WinProcess(PROCESSENTRY32* process) : WinProcess(process,PROCESS_ALL_ACCESS) {}


	WinProcess::~WinProcess()
	{
		CloseHandle(m_handle);

		delete m_process;
		delete m_processReader;
		delete m_processWriter;
	}

	WCHAR* WinProcess::GetProcessName() const { return m_process->szExeFile; }

	DWORD WinProcess::GetProcessId() const { return m_process->th32ProcessID; }

	HANDLE WinProcess::GetProcessHandle() const { return m_handle; }

	WinMemoryReader* WinProcess::GetProcessReader() const { return m_processReader; }

	WinMemoryWriter* WinProcess::GetProcessWriter() const { return m_processWriter; }

	bool WinProcess::IsActive() const
	{
		DWORD exitCode = NULL;

		if (GetExitCodeProcess(m_handle, &exitCode) == FALSE)
			return false;

		return exitCode == STILL_ACTIVE;
	}

	MODULEENTRY32W* WinProcess::FetchModule(const wchar_t* moduleName) const
	{
		HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, m_process->th32ProcessID);

		if (hSnap == INVALID_HANDLE_VALUE)
			return nullptr;

		MODULEENTRY32* module = nullptr;
		auto moduleEntry = new MODULEENTRY32();
		moduleEntry->dwSize = sizeof(MODULEENTRY32);

		if (Module32First(hSnap, moduleEntry))
			do
			{
				if (!_wcsicmp(moduleEntry->szModule, moduleName))
				{
					module = moduleEntry;
					break;
				}
			}
			while (Module32Next(hSnap, moduleEntry));

		if (module == nullptr)
			delete moduleEntry;

		CloseHandle(hSnap);
		return module;
	}

	bool WinProcess::InjectDll(const char* dll) const
	{
		if (m_handle == INVALID_HANDLE_VALUE)
			return false;

		SIZE_T dllSize = strlen(dll) + 1;

		LPVOID dllAddress = VirtualAllocEx(m_handle,
		                                   nullptr,
		                                   dllSize,
		                                   MEM_COMMIT | MEM_RESERVE,
		                                   PAGE_READWRITE);

		bool operationResult = WriteProcessMemory(m_handle, dllAddress, dll, dllSize, NULL);

		if (!operationResult)
			return false;

		HANDLE hThread = CreateRemoteThread(m_handle, nullptr, 0, (LPTHREAD_START_ROUTINE)(LoadLibraryA), dllAddress, 0,
		                                    nullptr);
		if (hThread)
			CloseHandle(hThread);
		else
			return false;
	}
}

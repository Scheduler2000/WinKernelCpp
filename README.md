# WinKernel

Lightweight library to interfere with windows kernel written in C++, useful for hacking.

## Features :

- Binaries Reading in big endian (see `win_kernel\memory\WinMemoryReader`)
- Binaries Reading in litle endian (see `win_kernel\memory\WinMemoryReader.cs`)
- Binaries Writing in big endian (see `win_kernel\memory\WinMemoryWriter.cs`)
- Binaries Writing in little endian (see `win_kernel\memory\WinMemoryWriter.cs`)
- Native dll injection (see `win_kernel\memory\\WinProcess.cs`) for x86 and x64 processes

## Example of Reading and Writing in memory and DLL injection

```cpp
auto processEntry = win_kernel::GetProcess(L"ac_client.exe");
	auto winProcess = new win_kernel::WinProcess(processEntry);

	auto moduleEntry = winProcess->FetchModule(L"ac_client.exe");
	auto moduleBaseAddress = moduleEntry->modBaseAddr;

	std::wcout << winProcess->GetProcessName() << " " << winProcess->GetProcessId() << std::endl;


	auto memoryWriter = winProcess->GetProcessWriter();
	auto memoryReader = winProcess->GetProcessReader();

	int playerPtr = memoryReader->ReadInt32(moduleBaseAddress + 0x10F4F4, endianness_enum::LittleEndian);

	memoryWriter->WriteInt64((LPVOID)(playerPtr + 0xF8), 10000, endianness_enum::LittleEndian);

	int playerHealth = memoryReader->ReadInt32((LPCVOID)(playerPtr + 0xF8), endianness_enum::LittleEndian);
	std::cout << playerHealth << std::endl;


	bool injected = winProcess->InjectDll("./DragnipurV2.0.dll");

	if (injected)
		std::cout << "DLL successfully injected !" << std::endl;
	else
		std::cout << "An error has occurred during the dll injection !" << std::endl;

	free(moduleEntry);

```

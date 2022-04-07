#include "win_kernel/memory/win_memory_reader.h"

#include <exception>
#include <format>

namespace win_kernel
{
	WinMemoryReader::WinMemoryReader(HANDLE processHandle) : m_processHandle(processHandle) {}

	BYTE* WinMemoryReader::Read(LPCVOID address, int size) const
	{
		auto buffer = new BYTE(size);
		SIZE_T bytesRead = NULL;

		DWORD oldProtect;
		VirtualProtectEx(m_processHandle, (LPVOID)address, size, PAGE_EXECUTE_READWRITE, &oldProtect);

		bool opResult = ReadProcessMemory(m_processHandle, address, buffer, size, &bytesRead);

		VirtualProtectEx(m_processHandle, (LPVOID)address, size, oldProtect, NULL);

		if (bytesRead != size || !opResult)
			throw new
				std::exception(
					std::format(
						"The reading at the address {} read {} byte(s) for a total of {} byte(s) has failed !",
						address,
						bytesRead,
						size).data());


		return buffer;
	}

	short WinMemoryReader::ReadInt16(LPCVOID address, endianness_enum endianness) const
	{
		return _read<short>(address, endianness);
	}

	int WinMemoryReader::ReadInt32(LPCVOID address, endianness_enum endianness) const
	{
		return _read<int>(address, endianness);
	}

	long WinMemoryReader::ReadInt64(LPCVOID address, endianness_enum endianness) const
	{
		return _read<long>(address, endianness);
	}

	unsigned short WinMemoryReader::ReadUInt16(LPCVOID address, endianness_enum endianness) const
	{
		return _read<unsigned short>(address, endianness);
	}

	unsigned WinMemoryReader::ReadUInt32(LPCVOID address, endianness_enum endianness) const
	{
		return _read<unsigned int>(address, endianness);
	}

	unsigned long WinMemoryReader::ReadUInt64(LPCVOID address, endianness_enum endianness) const
	{
		return _read<unsigned long>(address, endianness);
	}

	float WinMemoryReader::ReadDouble(LPCVOID address, endianness_enum endianness) const
	{
		return _read<float>(address, endianness);
	}

	double WinMemoryReader::ReadFloat(LPCVOID address, endianness_enum endianness) const
	{
		return _read<double>(address, endianness);
	}


	bool WinMemoryReader::ReadBool(LPCVOID address, endianness_enum endianness) const
	{
		return _read<bool>(address, endianness);
	}
}

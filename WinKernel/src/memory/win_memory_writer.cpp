#include "win_kernel/memory/win_memory_writer.h"

#include <format>
#include <iostream>


namespace win_kernel
{
	WinMemoryWriter::WinMemoryWriter(HANDLE processHandle) : m_processHandle(processHandle) {}

	void WinMemoryWriter::Write(LPVOID address, const BYTE* data, int size) const
	{
		SIZE_T bytesWritten = NULL;

		DWORD oldProtect;
		VirtualProtectEx(m_processHandle, address, size, PAGE_EXECUTE_READWRITE, &oldProtect);

		bool opResult = WriteProcessMemory(m_processHandle, address, data, size, &bytesWritten);

		VirtualProtectEx(m_processHandle, address, size, oldProtect, NULL);

		if (bytesWritten != size || !opResult)
			throw new
				std::exception(
					std::format(
						"The writing at the address {} read {} byte(s) for a total of {} byte(s) has failed !",
						address,
						bytesWritten,
						size).data());
	}

	void WinMemoryWriter::WriteInt16(LPVOID address, short value, endianness_enum endianness) const
	{
		_write(address, value, endianness);
	}

	void WinMemoryWriter::WriteInt32(LPVOID address, int value, endianness_enum endianness) const
	{
		_write(address, value, endianness);
	}

	void WinMemoryWriter::WriteInt64(LPVOID address, long value, endianness_enum endianness) const
	{
		_write(address, value, endianness);
	}

	void WinMemoryWriter::WriteUInt16(LPVOID address, unsigned short value, endianness_enum endianness) const
	{
		_write(address, value, endianness);
	}

	void WinMemoryWriter::WriteUInt32(LPVOID address, unsigned value, endianness_enum endianness) const
	{
		_write(address, value, endianness);
	}

	void WinMemoryWriter::WriteUInt64(LPVOID address, unsigned long value, endianness_enum endianness) const
	{
		_write(address, value, endianness);
	}

	void WinMemoryWriter::WriteDouble(LPVOID address, double value, endianness_enum endianness) const
	{
		_write(address, value, endianness);
	}

	void WinMemoryWriter::WriteFloat(LPVOID address, float value, endianness_enum endianness) const
	{
		_write(address, value, endianness);
	}

	void WinMemoryWriter::WriteBool(LPVOID address, bool value, endianness_enum endianess) const
	{
		SIZE_T bytesWritten = NULL;

		WriteProcessMemory(m_processHandle, address, &value, sizeof(bool), &bytesWritten);

		std::cout << bytesWritten << " bytes written" << std::endl;
	}
}

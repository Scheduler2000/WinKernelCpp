#pragma once

#include <Windows.h>

#include "endianness_enum.h"

namespace win_kernel
{
	class WinMemoryReader
	{
		private:
			HANDLE m_processHandle;

			template <typename T>
			T _read(LPCVOID address, endianness_enum endianness) const;

		public:
			WinMemoryReader(HANDLE processHandle);

			BYTE* Read(LPCVOID address, int size) const;

			short ReadInt16(LPCVOID address, endianness_enum endianness) const;

			int ReadInt32(LPCVOID address, endianness_enum endianness) const;

			long ReadInt64(LPCVOID address, endianness_enum endianness) const;

			unsigned short ReadUInt16(LPCVOID address, endianness_enum endianness) const;

			unsigned int ReadUInt32(LPCVOID address, endianness_enum endianness) const;

			unsigned long ReadUInt64(LPCVOID address, endianness_enum endianness) const;

			float ReadDouble(LPCVOID address, endianness_enum endianness) const;

			double ReadFloat(LPCVOID address, endianness_enum endianness) const;

			bool ReadBool(LPCVOID address, endianness_enum endianess) const;
	};

	template <typename T>
	T WinMemoryReader::_read(LPCVOID address, endianness_enum endianness) const
	{
		BYTE* data = this->Read(address, sizeof(T));
		T result = 0;
			
		auto dst = (BYTE*)(&result);

		if (endianness == endianness_enum::LittleEndian)
			for (size_t i = 0; i < sizeof(int); i++)
				dst[i] = data[i];
		else
			for (size_t i = 0; i < sizeof(int); i++)
				dst[i] = data[sizeof(int) - i - 1];
		return result;
	}
}

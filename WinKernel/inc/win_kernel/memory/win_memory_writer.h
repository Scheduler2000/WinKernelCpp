#pragma once

#include <Windows.h>

#include "endianness_enum.h"


namespace win_kernel
{
	class WinMemoryWriter
	{
		private:
			HANDLE m_processHandle;

			template <typename T>
			void _write(LPVOID address, const T& value, endianness_enum endianness) const;

		public:
			WinMemoryWriter(HANDLE processHandle);

			void Write(LPVOID address, const BYTE* data, int size) const;

			void WriteInt16(LPVOID address, short value, endianness_enum endianness) const;

			void WriteInt32(LPVOID address, int value, endianness_enum endianness) const;

			void WriteInt64(LPVOID address, long value, endianness_enum endianness) const;

			void WriteUInt16(LPVOID address, unsigned short value, endianness_enum endianness) const;

			void WriteUInt32(LPVOID address, unsigned int value, endianness_enum endianness) const;

			void WriteUInt64(LPVOID address, unsigned long value, endianness_enum endianness) const;

			void WriteDouble(LPVOID address, double value, endianness_enum endianness) const;

			void WriteFloat(LPVOID address, float value, endianness_enum endianness) const;


			void WriteBool(LPVOID address, bool value, endianness_enum endianess) const;


	};

	template <typename T>
	void WinMemoryWriter::_write(LPVOID address, const T& value, endianness_enum endianness) const
	{
		size_t size = sizeof(T);

		if (endianness == endianness_enum::LittleEndian)
			Write(address, reinterpret_cast<const BYTE*>(&value), size);
		else
		{
			BYTE* buffer = new BYTE[size];

			auto arr = reinterpret_cast<const BYTE*>(&value);

			for (int i = 0; i < size; i++)
				buffer[i] = arr[size - i - 1];


			Write(address, buffer, size);
		}
	}
}

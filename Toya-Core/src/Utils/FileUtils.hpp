#pragma once
#include <string>

namespace Toya
{
	namespace Utils
	{
		inline std::string read_file(const char* filePath)
		{
			auto file = fopen(filePath, "rt");
			fseek(file, 0, SEEK_END);
			unsigned long length = ftell(file);
			auto data = new char[length + 1];
			memset(data, 0, length + 1);
			fseek(file, 0, SEEK_SET);
			fread(data, 1, length, file);
			fclose(file);

			std::string result(data);
			// ReSharper disable once CppNonConsistentAcquisitionReclaimPair
			delete data;
			return result;
		}

		inline static size_t _hash(const char* str)
		{
			unsigned h = 0x71452F;
			while (*str)
				h = h * 101 + (unsigned)*str++;
			return h;
		}
	}
}

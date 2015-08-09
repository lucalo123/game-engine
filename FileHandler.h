#pragma once
#include <vector>
#include <string>
namespace npe {
	class FileHandler
	{
	public:
		static bool ReadFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
	};
}


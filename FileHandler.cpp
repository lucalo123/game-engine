#include "FileHandler.h"

#include <fstream>

bool npe::FileHandler::ReadFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer)
{
	// Read as binary.
	std::ifstream file(filePath, std::ios::binary);
	if (file.fail()) {
		perror(filePath.c_str());
		return false;
	}

	// Seek to end of file.
	file.seekg(0, std::ios::end);
	// Get filesize.
	int fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	// Reduce filesize by any headerbytes.
	fileSize -= file.tellg();
	// Set size of vector to fileSize.
	buffer.resize(fileSize);
	file.read((char*)&buffer[0], fileSize);
	file.close();

	return true;
}
#pragma once
#include "GLTexture.h"

#include <string>
namespace npe {
	class ImageLoader
	{
	public:
		static GLTexture loadPNG(std::string filePath);
	};
}


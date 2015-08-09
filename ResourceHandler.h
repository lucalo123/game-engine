#pragma once
#include "TextureCache.h"
#include <string>
namespace npe {
	class ResourceHandler
	{
		static TextureCache _textureCache;
	public:
		static GLTexture GetTexture(std::string filePath);
	};
}

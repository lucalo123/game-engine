#pragma once
#include "GLTexture.h"
#include <map>
namespace npe {
	class TextureCache
	{
		std::map<std::string, GLTexture> _textureMap;
	public:
		TextureCache();

		GLTexture GetTexture(std::string filePath);

		~TextureCache();
	};
}


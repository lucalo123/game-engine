#include "TextureCache.h"
#include "ImageLoader.h"

using namespace npe;

TextureCache::TextureCache()
{
}

GLTexture TextureCache::GetTexture(std::string filePath)
{
	// Search for texture.
	auto mit =_textureMap.find(filePath);

	// Check if its not in the map.
	if (mit == _textureMap.end()) {
		// Load texture.
		GLTexture newTexture = ImageLoader::loadPNG(filePath);

		// Insert into map.
		_textureMap.insert(make_pair(filePath, newTexture));

		std::printf("LOADED Cached Texture from %s\n", filePath.c_str());
		return newTexture;
	}
	std::printf("USED Cached Texture\n");
	// Return value.
	return mit->second;
}

TextureCache::~TextureCache()
{
}

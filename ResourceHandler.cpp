#include "ResourceHandler.h"

using namespace npe;

TextureCache ResourceHandler::_textureCache;

GLTexture ResourceHandler::GetTexture(std::string filePath)
{
	return _textureCache.GetTexture(filePath);
}
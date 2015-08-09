#pragma once
#include <GL\glew.h>
#include "GLTexture.h"
#include <string>
namespace npe {
	class Sprite
	{
		float _x, _y, _width, _height;
		GLuint _vboID;
		GLTexture _texture;
	public:
		Sprite();

		void Init(float x, float y, float width, float height, std::string texturePath);

		void Draw();

		~Sprite();
	};
}


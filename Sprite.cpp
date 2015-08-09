#include <cstddef>

#include "Sprite.h"
#include "Vertex.h"
#include "ResourceHandler.h"

npe::Sprite::Sprite()
{
	_vboID = 0;
}

void npe::Sprite::Init(float x, float y, float width, float height, std::string texturePath)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;

	_texture = ResourceHandler::GetTexture(texturePath);

	if (_vboID == 0){
		glGenBuffers(1, &_vboID);
	}
	// Draw a quad(6 vertices * 2).
	// Quad/Square coords.
	Vertex vertexData[6];
	// ## First triangle ##
	// 1
	vertexData[0].SetPosition(x + width, y + height);
	vertexData[0].SetUV(1.0f, 1.0f);

	// Middlepoint
	vertexData[1].SetPosition(x, y + height);
	vertexData[1].SetUV(0.0f, 1.0f);

	// 3
	vertexData[2].SetPosition(x, y);
	vertexData[2].SetUV(0.0f, 0.0f);

	// ## Second triangle ##
	// 1
	vertexData[3].SetPosition(vertexData[2].position.x, vertexData[2].position.y);
	vertexData[3].SetUV(0.0f, 0.0f);

	// Middlepoint inverse
	vertexData[4].SetPosition(x + width, y);
	vertexData[4].SetUV(1.0f, 0.0f);

	// 3
	vertexData[5].SetPosition(vertexData[0].position.x, vertexData[0].position.y);
	vertexData[5].SetUV(1.0f, 1.0f);
	// Vertexcolors.
	for (int i = 0; i < 6; i++) {
		vertexData[i].SetColor(255, 0, 255, 255);
	}

	//vertexData[1].SetColor(0, 0, 255, 255);
	//vertexData[4].SetColor(0, 255, 0, 255);

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	// Unbind vertex buffer object.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void npe::Sprite::Draw()
{
	// Bind textureobject.
	glBindTexture(GL_TEXTURE_2D, _texture.id);

	// Bind vertexobject.
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	// Always disable Vertex attribute array.
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

npe::Sprite::~Sprite()
{
	// Free up GPU-memory.
	if (_vboID != 0) {
		glDeleteBuffers(1, &_vboID);
	}
}

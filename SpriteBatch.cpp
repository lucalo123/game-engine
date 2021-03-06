#include "SpriteBatch.h"

#include <algorithm>

using namespace npe;

SpriteBatch::SpriteBatch() : _vbo(0), _vao(0)
{
}

void SpriteBatch::Init()
{
	_createVertexArray();
}
// Default TEXTURE.
void SpriteBatch::Load(GlyphSortType sortType)
{
	_sortType = sortType;
	_renderBatches.clear();
	// Delete glyphs before clearing to prevent memoryleak.
	for (int i = 0; i < _glyphs.size(); i++) {
		delete _glyphs[i];
	}
	_glyphs.clear();
}

void SpriteBatch::UnLoad()
{
	_sortGlyphs();
	_createRenderBatches();
}

void SpriteBatch::Draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color)
{
	Glyph* newGlyph = new Glyph;
	newGlyph->texture = texture;
	newGlyph->depth = depth;
	// Top left corner.
	newGlyph->topLeft.color = color;
	newGlyph->topLeft.SetPosition(destRect.x, destRect.y + destRect.w);
	newGlyph->topLeft.SetUV(uvRect.x, uvRect.y + uvRect.w);
	// Bottom left corner.
	newGlyph->bottomLeft.color = color;
	newGlyph->bottomLeft.SetPosition(destRect.x, destRect.y);
	newGlyph->bottomLeft.SetUV(uvRect.x, uvRect.y);
	// Bottom right corner.
	newGlyph->bottomRight.color = color;
	newGlyph->bottomRight.SetPosition(destRect.x + destRect.z, destRect.y);
	newGlyph->bottomRight.SetUV(uvRect.x + uvRect.z, uvRect.y);
	// Top right corner.
	newGlyph->topRight.color = color;
	newGlyph->topRight.SetPosition(destRect.x + destRect.z, destRect.y + destRect.w);
	newGlyph->topRight.SetUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

	_glyphs.push_back(newGlyph);
}

void SpriteBatch::Render()
{
	glBindVertexArray(_vao);
	for (int i = 0; i < _renderBatches.size(); i++) {
		glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);

		glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numVertices);
	}
	// Unbind.
	glBindVertexArray(0);
}

void SpriteBatch::_createRenderBatches()
{
	std::vector<Vertex> vertices;

	vertices.resize(_glyphs.size() * 6);

	if (_glyphs.empty())
		return;
	
	int offset = 0;

	int cv = 0; // Current vertex.
	_renderBatches.emplace_back(0, 6, _glyphs[0]->texture);
	// First triangle.
	vertices[cv++] = _glyphs[0]->topLeft;
	vertices[cv++] = _glyphs[0]->bottomLeft;
	vertices[cv++] = _glyphs[0]->bottomRight;
	// Second triangle.
	vertices[cv++] = _glyphs[0]->bottomRight;
	vertices[cv++] = _glyphs[0]->topRight;
	vertices[cv++] = _glyphs[0]->topLeft;

	offset += 6;

	for (int cg = 1; cg < _glyphs.size(); cg++) {
		if (_glyphs[cg]->texture != _glyphs[cg - 1]->texture) {
			_renderBatches.emplace_back(offset, 6, _glyphs[cg]->texture);
		}
		else{
			_renderBatches.back().numVertices += 6;
		}
		// First triangle.
		vertices[cv++] = _glyphs[cg]->topLeft;
		vertices[cv++] = _glyphs[cg]->bottomLeft;
		vertices[cv++] = _glyphs[cg]->bottomRight;
		// Second triangle.
		vertices[cv++] = _glyphs[cg]->bottomRight;
		vertices[cv++] = _glyphs[cg]->topRight;
		vertices[cv++] = _glyphs[cg]->topLeft;
		offset += 6;
	}

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	// Orphan buffer.
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
	// Upload data.
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
	// Unbind buffer.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteBatch::_createVertexArray()
{
	if (_vao == 0) {
		glGenVertexArrays(1, &_vao);
	}
	glBindVertexArray(_vao);

	if (_vbo == 0) {
		glGenBuffers(1, &_vbo);
	}
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	// Tell opengl that we want to use first attribute array.
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// Position attribute pointer.
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	// Color attribute pointer(normalized).
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	// UV attribute pointer.
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	// Unbind vertexarray.
	glBindVertexArray(0);
	
}

void SpriteBatch::_sortGlyphs()
{
	switch (_sortType)
	{
	case GlyphSortType::BACK_TO_FRONT:
		std::stable_sort(_glyphs.begin(), _glyphs.end(), _compareFrontToBack);
		break;
	case GlyphSortType::FRONT_TO_BACK:
		std::stable_sort(_glyphs.begin(), _glyphs.end(), _compareBackToFront);
		break;
	case GlyphSortType::TEXTURE:
		std::stable_sort(_glyphs.begin(), _glyphs.end(), _compareTexture);
		break;
	default:
		break;
	}
	
}

bool SpriteBatch::_compareFrontToBack(Glyph* a, Glyph* b)
{
	return (a->depth < b->depth);
}
bool SpriteBatch::_compareBackToFront(Glyph* a, Glyph* b)
{
	return (a->depth > b->depth);
}
bool SpriteBatch::_compareTexture(Glyph* a, Glyph* b)
{
	return (a->texture < b->texture);
}

SpriteBatch::~SpriteBatch()
{
}
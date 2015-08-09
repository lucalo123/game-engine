#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <vector>

#include "Vertex.h"

namespace npe{

	enum class GlyphSortType {
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};

	struct Glyph
	{
		GLuint texture;
		float depth;
		Vertex topLeft, bottomLeft, topRight, bottomRight;
	};

	class RenderBatch
	{
		
	public:
		GLuint offset, numVertices, texture;
		RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) : offset(Offset), numVertices(NumVertices), texture(Texture) {}
	};

	class SpriteBatch
	{
		// Private
		GLuint _vbo, _vao;
		GlyphSortType _sortType;
		std::vector<Glyph*> _glyphs;
		std::vector<RenderBatch> _renderBatches;
		void _createVertexArray();
		void _createRenderBatches();
		void _sortGlyphs();
		static bool _compareFrontToBack(Glyph* a, Glyph* b);
		static bool _compareBackToFront(Glyph* a, Glyph* b);
		static bool _compareTexture(Glyph* a, Glyph* b);
	public:
		SpriteBatch();

		void Init();
		// Begin
		void Load(GlyphSortType sortType = GlyphSortType::TEXTURE);
		// End
		void UnLoad();

		void Draw(const glm::vec4& destRectm, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color);

		void Render();

		~SpriteBatch();
	};
}


#pragma once
#include <GL\glew.h>
namespace npe {
	struct Position {
		float x, y;
	};

	struct Color {
		// Default to color white and max alpha.
		GLubyte r = 255, g = 255, b = 255, a = 255;
	};

	struct UV {
		float u, v;
	};

	struct Vertex {
		// Position x and y.
		Position position;
		// Color rgba.
		Color color;
		// UV Texture coordinates.
		UV uv;

		void SetPosition(float x, float y) {
			position.x = x;
			position.y = y;
		}

		void SetColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
			color.r = r;
			color.g = g;
			color.b = b;
			color.a = a;
		}

		void SetUV(float u, float v){
			uv.u = u;
			uv.v = v;
		}
	};
}
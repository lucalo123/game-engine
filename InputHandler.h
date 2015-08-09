#pragma once
#include <unordered_map>
#include <glm\glm.hpp>

namespace npe {

	class InputHandler
	{
		std::unordered_map<unsigned int, bool> _keyMap;
		glm::vec2 _mouseCoords;
	public:
		InputHandler();

		void KeyDown(unsigned int keyID);
		void KeyUp(unsigned int keyID);

		// Setters
		void SetMouseCoords(float x, float y);

		bool IsKeyDown(unsigned int keyID);

		// Getters.
		glm::vec2 GetMouseCoords() const { return _mouseCoords; };

		~InputHandler();
	};

}

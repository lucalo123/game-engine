#pragma once
#include <SDL.h>
#include <GL\glew.h>
#include <string>
namespace npe {
	enum WindowFlags{ INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

	class Window
	{
		SDL_Window* _window;
		unsigned int _screenWidth, _screenHeight;
	public:
		Window();

		bool Create(std::string title, int _screenWidth, int _screenHeight, unsigned int currentFlags);
		void SwapBuffer();

		int GetScreenWidth(){ _screenWidth; }
		int GetScreenHeight(){ _screenHeight; }

		~Window();
	};
}


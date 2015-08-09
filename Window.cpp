#include "Window.h"
#include "ErrorHandler.h"

using namespace npe;

Window::Window()
{
}

bool Window::Create(std::string title, int screenWidth, int screenHeight, unsigned int currentFlags)
{
	Uint32 flags = SDL_WINDOW_OPENGL;

	if (currentFlags & INVISIBLE) {
		flags |= SDL_WINDOW_HIDDEN;
	}
	if (currentFlags & FULLSCREEN) {
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}
	if (currentFlags & BORDERLESS) {
		flags |= SDL_WINDOW_BORDERLESS;
	}

	// Open window.
	_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_OPENGL);
	if (_window == nullptr)
	{
		ErrorHandler::Message("SDL_Window could not be created.");
		return false;
	}
	// OpenGL Context, TODO: Implement.
	SDL_GLContext context = SDL_GL_CreateContext(_window);
	if (context == nullptr)
	{
		ErrorHandler::Message("SDL_GL_CreateContext could not be created.");
		return false;
	}
	// Helps with crossplatform.
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		ErrorHandler::Message("Could not initialize glew.");
		return false;
	}

	// When we use glClear set to this color.
	// Set to blue(rgba).
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	// Enable VSYNC.
	SDL_GL_SetSwapInterval(1);
	// Enable alpha blending mode(transparency).
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;
}

void Window::SwapBuffer()
{
	SDL_GL_SwapWindow(_window);
}

Window::~Window()
{
}

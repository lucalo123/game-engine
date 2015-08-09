#include "InputHandler.h"

using namespace npe;

InputHandler::InputHandler() : _mouseCoords(0.0f)
{
}

void InputHandler::KeyDown(unsigned int keyID)
{
	_keyMap[keyID] = true;
}

void InputHandler::KeyUp(unsigned int keyID)
{
	_keyMap[keyID] = false;
}

void InputHandler::SetMouseCoords(float x, float y)
{
	_mouseCoords.x = x;
	_mouseCoords.y = y;
}

bool InputHandler::IsKeyDown(unsigned int keyID)
{
	auto it = _keyMap.find(keyID);

	if (it != _keyMap.end())
		return it->second;
	else
		return false;
}

InputHandler::~InputHandler()
{
}

#include "Camera2D.h"

using namespace npe;

Camera2D::Camera2D() : 
	_position(0.0f, 0.0f),
	_cameraMatrix(1.0f),
	_orthoMatrix(1.0f),
	_scale(1.0f),
	_needsMatrixUpdate(true),
	_screenWidth(500),
	_screenHeight(500){}


void Camera2D::Init(int screenWidth, int screenHeight)
{
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;
	_orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);
}

void Camera2D::Update()
{
	if (_needsMatrixUpdate) {
		// Translation, will translate cameramatrix into center of screen.
		glm::vec3 translate(-_position.x + _screenWidth/2, -_position.y + _screenHeight/2, 0.0f);
		_cameraMatrix = glm::translate(_orthoMatrix, translate);
		// Scaling.
		glm::vec3 scale(_scale, _scale, 0.0f);
		_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;

		_needsMatrixUpdate = false;
	}
}

glm::vec2 Camera2D::ToWorldCoords(glm::vec2 screenCoords)
{
	// Invert vertical(y) coordinates.
	screenCoords.y = _screenHeight - screenCoords.y;
	// Move 0.0 coordinate to the center of our screen.
	screenCoords -= glm::vec2(_screenWidth / 2, _screenHeight / 2);
	// Scale coordinates.
	screenCoords /= _scale;
	// Translate with the camera position.
	screenCoords += _position;
	return screenCoords;
}

Camera2D::~Camera2D()
{
}

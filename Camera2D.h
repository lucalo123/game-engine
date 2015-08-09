#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

namespace npe {
	class Camera2D
	{
		bool _needsMatrixUpdate;
		int _screenWidth, _screenHeight;
		glm::vec2 _position;
		glm::mat4 _cameraMatrix;
		glm::mat4 _orthoMatrix;
		float _scale;
	public:
		Camera2D();

		void Init(int screenWidth, int screenHeight);

		void Update();

		glm::vec2 ToWorldCoords(glm::vec2 screenCoords);

		// Setters
		void SetPosition(const glm::vec2& newPosition) { _position = newPosition; _needsMatrixUpdate = true; }
		void SetScale(float newScale) { _scale = newScale; _needsMatrixUpdate = true; }
		// Getters
		glm::vec2 GetPosition() { return _position; }
		float GetScale() { return _scale; }
		glm::mat4 GetCameraMatrix(){ return _cameraMatrix; }

		~Camera2D();
	};

}



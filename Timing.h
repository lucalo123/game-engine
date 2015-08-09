#pragma once
#include <GL\glew.h>

namespace npe {
	
	class FpsLimiter
	{
		// Return current FPS.
		void _calculate();
		int _startTicks, _maxFPS, _frameTime, _fps;
	public:
		FpsLimiter();
		void Init(int maxFPS);
		
		void StartCounter();

		void SetMaxFps(int maxFPS);

		int Result();
	};

}
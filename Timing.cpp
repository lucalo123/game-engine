#include "Timing.h"
#include <SDL.h>

using namespace npe;

FpsLimiter::FpsLimiter() : _maxFPS(60)
{

}

void FpsLimiter::Init(int maxFPS)
{
	SetMaxFps(maxFPS);
}

void FpsLimiter::StartCounter()
{
	_startTicks = SDL_GetTicks();
}

int FpsLimiter::Result()
{
	_calculate();
	GLuint frameTicks = SDL_GetTicks() - _startTicks;
	if ((1000 / _maxFPS) > frameTicks) {
		SDL_Delay(1000 / _maxFPS - frameTicks);
	}

	return _fps;
}

void FpsLimiter::SetMaxFps(int maxFPS)
{
	_maxFPS = maxFPS;
}

void FpsLimiter::_calculate()
{
	static const int NUM_SAMPLES = 10;
	static GLuint frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;

	static GLuint prevTicks = SDL_GetTicks();
	GLuint currentTicks = SDL_GetTicks();

	_frameTime = currentTicks - prevTicks;
	frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

	prevTicks = currentTicks;

	int count;

	currentFrame++;
	if (currentFrame < NUM_SAMPLES) {
		count = currentFrame;
	}
	else {
		count = NUM_SAMPLES;
	}

	GLuint frameTimeAverage = 0;
	for (int i = 0; i < count; i++) {
		frameTimeAverage += frameTimes[i];
	}
	frameTimeAverage /= count;

	if (frameTimeAverage > 0) {
		_fps = 1000 / frameTimeAverage;
	}
	else{
		_fps = 1;
	}
}

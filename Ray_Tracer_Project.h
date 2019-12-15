#pragma once
#include "Core.h"
#include "Particle.h"

#ifndef RAY_TRACER_PROJECT_H

class Project1
{

public:

	Project1();

	~Project1();

	void Init();

	void GameLoop();

	void Render();

	void Update();

	void checkEvent(bool running);

	void updateSystemState(Particle* particles, float& time, float& h);

	void bounce(SDL_Renderer* renderer, float& time, Particle* particles, float& h);

	int GetFrameCount() const
	{
		return frameCount;
	}

	int GetCount() const
	{
		return count;
	}

	int getRunningVal() const
	{
		return isRunning;
	}

private:

	SDL_Renderer* renderer;
	SDL_Window* window;

	int count;
	int frameCount;
	int timerFPS;
	int lastFrame;

	bool isRunning;

};

#endif // !RAY_TRACER_PROJECT_H


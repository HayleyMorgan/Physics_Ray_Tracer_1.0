// Physics Ray Tracer Project 1.0.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include <iostream>

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <vector>

#include "SDL.h"
#include "SDL_image.h"
#include "Ray_Tracer_Project.h"
#include "Core.h"
#include "Spring.h"

static float springConstant = 0.3f;
static float dampingValue = 0.9f;
static Vector2d springForce;
static float restLength = 60.0f;
static float numberOfParticles = 6;
static float numberOfSprings = 5;

static Particle particles[6];
static Spring springs[5];

Particle* p_particles;
Spring* p_springs;

Project1::Project1()
{

	// Initialize SDL
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("Physics Project - Ray Tracer 1.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1000, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	if (!window)
	{
		printf("error creating window: %\n", SDL_GetError());
		SDL_Quit();
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
	{
		printf("error creating renederer: %\n", SDL_GetError);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	isRunning = true;

	//closes the game after a certain amount of seconds
	count = 0;
	frameCount = 0;
}

Project1::~Project1()
{
	// Release any of the allocated resources
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Project1::GameLoop()
{
	while (isRunning)
	{

		lastFrame = SDL_GetTicks();
		
		static int lastTime;
		if (lastFrame >= (lastTime + 100000)) //Over a second
		{
			lastTime = lastFrame;
			frameCount = 0;
			count++;
		}

		checkEvent(isRunning);

		//Input
		//Update();
		Render();

	}

}

void Project1::checkEvent(bool running)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			const char* key = SDL_GetKeyName(event.key.keysym.sym);
			if (strcmp(key, "Q") == 0 || strcmp(key, "Escape") == 0)
			{
				isRunning = false;
			}
		}
		else if (event.type == SDL_QUIT)
		{
			isRunning = false;
		}
	}
}

void Project1::Init()
{
	float mass = 1.0f;
	float inifinit_mass = 1000000000000.0f;

	Vector2d initPosFixedPoint_L = { -200.0f, 20.0f };
	Vector2d initVelFixedPoint_L = { 0.0f, 0.0f };

	Vector2d initPosFixedPoint_R = { 200.0f, 20.0f };
	Vector2d initVelFixedPoint_R = { 0.0f, 0.0f };

	Particle fixedPoint_L = Particle(initPosFixedPoint_L, initVelFixedPoint_L, dampingValue, inifinit_mass);
	Particle fixedPoint_R = Particle(initPosFixedPoint_R, initVelFixedPoint_R, dampingValue, inifinit_mass);

	//--------------------------------------//

	//Change these
	Vector2d initPos1 = { -100.0f, 80.0f };
	Vector2d initVel1 = { 0.0f, 0.0f };

	Particle p1 = Particle(initPos1, initVel1, dampingValue, mass);

	Vector2d initPos2 = { 0.0f, 100.0f };
	Vector2d initVel2 = { 0.0f, 0.0f };

	Particle p2 = Particle(initPos2, initVel2, dampingValue, mass);

	Vector2d initPos3 = { 120.0f, 80.0f };
	Vector2d initVel3 = { 0.0f, 0.0f };

	Particle p3 = Particle(initPos3, initVel3, dampingValue, mass);

	Vector2d initPos4 = { 170.0f, 40.0f };
	Vector2d initVel4 = { 0.0f, 0.0f };

	Particle p4 = Particle(initPos4, initVel4, dampingValue, mass);

	particles[0] = fixedPoint_L;
	particles[1] = p1;
	particles[2] = p2;
	particles[3] = p3;
	particles[4] = p4;
	particles[5] = fixedPoint_R;

	p_particles = particles;

	Spring spring1;
	Spring spring2;
	Spring spring3;
	Spring spring4;
	Spring spring5;

	spring1 = Spring(springConstant, restLength, p_particles, p_particles + 1);
	spring2 = Spring(springConstant, restLength, p_particles + 1, p_particles + 2);
	spring3 = Spring(springConstant, restLength, p_particles + 2, p_particles + 3);
	spring4 = Spring(springConstant, restLength, p_particles + 3, p_particles + 4);
	spring5 = Spring(springConstant, restLength, p_particles + 4, p_particles + 5);

	springs[0] = spring1;
	springs[1] = spring2;
	springs[2] = spring3;
	springs[3] = spring4;
	springs[4] = spring5;

	p_springs = springs;

}

void Project1::Render()
{
	//	frameCount++;
	int timerFPS = SDL_GetTicks() - lastFrame;
	
	if (timerFPS < (1000 / 60))
	{
		SDL_Delay((1000 / 60) - timerFPS); //Makes sure there are 60 frames per second
	}

	float time = 0.0f;
	float timeStep = 0.2;
	
	while (time <= 100.0f)
	{
		SDL_SetRenderDrawColor(renderer, 225, 225, 255, 255);
		bounce(renderer, time, p_particles, timeStep);
		SDL_RenderPresent(renderer);
		time += timeStep;

		checkEvent(isRunning);

		if (isRunning == false)
		{
			SDL_Quit();
		}
	}
	
	// Switch buffers (Double buffering)
	//Push everything from the renderer to the window
	SDL_RenderPresent(renderer);

	isRunning = false;
}

//TODO: Function for taking a vector of particles 
void Project1::bounce(SDL_Renderer* renderer, float& time, Particle* particles, float& h)
{
	updateSystemState(particles, time, h);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 20, 0, 20, 255);

	for (int i = 0; i < numberOfParticles; i++)
	{
		SDL_RenderDrawLine(renderer, particles[i].getPosition().x + 551.0f, particles[i].getPosition().y - 20.0f, particles[i + 1].getPosition().x + 551, particles[i + 1].getPosition().y - 20.0f);

		SDL_SetRenderDrawColor(renderer, 255, 30, 30, 255);
		SDL_RenderDrawPoint(renderer, particles[i].getPosition().x + 550, particles[i].getPosition().y - 20.0f);
		SDL_RenderDrawPoint(renderer, particles[i].getPosition().x + 551, particles[i].getPosition().y - 20.0f);
		SDL_RenderDrawPoint(renderer, particles[i].getPosition().x + 552, particles[i].getPosition().y - 20.0f);
		SDL_RenderDrawPoint(renderer, particles[i].getPosition().x + 551, particles[i].getPosition().y - 21.0f);
		SDL_RenderDrawPoint(renderer, particles[i].getPosition().x + 551, particles[i].getPosition().y - 19.0f);
		SDL_RenderDrawPoint(renderer, particles[i].getPosition().x + 552, particles[i].getPosition().y - 21.0f);
		SDL_RenderDrawPoint(renderer, particles[i].getPosition().x + 552, particles[i].getPosition().y - 19.0f);
		SDL_RenderDrawPoint(renderer, particles[i].getPosition().x + 550, particles[i].getPosition().y - 21.0f);
		SDL_RenderDrawPoint(renderer, particles[i].getPosition().x + 550, particles[i].getPosition().y - 19.0f);

	}
	
	SDL_RenderPresent(renderer);
}
//This needs to take a vector of particles, including the fixed particles
void Project1::updateSystemState(Particle* particles, float& time, float& h)
{

	Vector2d initPos = {};
	Vector2d initVel = {0.0f, 0.0f};
	//Add gravity force
	Vector2d gravityConst = { 0.0f, 9.8f };
	Vector2d gravityForce;

	for (int i = 1; i < numberOfParticles - 1; i++)
	{
		gravityForce = gravityConst * particles[i].getMass();

		particles[i].addForce(gravityForce);
	}

	Spring spring(springConstant, restLength);

	for (int i = 0; i < numberOfSprings; i++)
	{
		//spring.calculateSpringForce(particles, i);
		p_springs[i].calculateSpringForce();
	}

	for(int i = 0; i < numberOfParticles; i++)
	{
		Vector2d accel = particles[i].getAccumForces() / particles[i].getMass();

		initVel = particles[i].getVelocity();

		initPos = particles[i].getPosition();

		//Semi-explicit euler
		Vector2d newVel = initVel + accel * h;
		particles[i].setVelocity(newVel);

		Vector2d newPos = initPos + newVel * h;
		particles[i].setPosition(newPos);

	}

	for (int i = 0; i < numberOfParticles; i++)
	{
		particles[i].clearAccumulatedForces();
	}

}

int main(int argc, char** argv)
{
	Project1* p = new Project1();

	//Initialise Particles and springs.
	p->Init();

	p->GameLoop();

	//Free any resources
	p->~Project1();

	return 0;
}


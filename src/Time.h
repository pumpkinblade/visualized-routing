#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

class Time
{
public:
	static float GetTime();
	static float GetDeltaTime();
	static int GetFPS();
	static void Tick();
private:
	static double lastTime_;
	static double deltaTime_;
};


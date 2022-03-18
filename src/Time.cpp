#include "Time.h"

double Time::lastTime_ = 0.0;
double Time::deltaTime_ = 0.0001;

float Time::GetTime()
{
	return static_cast<float>(lastTime_);
}

float Time::GetDeltaTime()
{
	return static_cast<float>(deltaTime_);
}

int Time::GetFPS()
{
	return static_cast<int>(1.0f / (static_cast<float>(deltaTime_)));
}

void Time::Tick()
{
	double t = glfwGetTime();
	deltaTime_ = t - lastTime_;
	lastTime_ = t;
}
#pragma once

#include <iostream>

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"

class Scene
{
public:
	Scene(GLuint screenWidth = 1000, GLuint screenHeight = 800);
	~Scene();

	void BeginDraw(float r, float g, float b, float a);
	void EndDraw();

	Camera camera_;
	GLuint GetRenderResult();
private:
	// Ö¡»º³å
	GLuint fbo_;
	GLuint tex_;
	GLuint msfbo_;
	GLuint msrbo_;

protected:
	const GLuint screenWidth_;
	const GLuint screenHeight_;
};


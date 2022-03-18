#include <iostream>
#include <cmath>
#include <fstream>
// GLAD
#include <GLAD/glad.h>
// GLFW
#include <GLFW/glfw3.h>

#include "Input.h"
#include "Time.h"
#include "Controller.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mode);
void mouse_movement_callback(GLFWwindow* window, double x, double y);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

const GLuint SCR_WIDTH = 1000, SCR_HEIGHT = 800;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	//glfwWindowHint(GLFW_VISIBLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "MAP", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	//glfwSetCursorPosCallback(window, mouse_movement_callback);
	glfwSetScrollCallback(window, scroll_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	Input::Reset();
	Time::Tick();
	LineRenderer::Init();
	TriangleRenderer::Init();
	SpriteRenderer::Init();
	TextRenderer::Init();
	QuadRenderer::Init();
	InstancedMeshRenderer::Init();
	CharacterLibrary::Init(FontFile, 24);
	// ³õÊ¼»¯ColorMap
	//float p[] = { 0.00f, 0.14f, 0.28f, 0.43f, 0.57f, 0.71f, 0.85f, 1.0f };
	//unsigned int c[] = { 0x440154, 0x46317e, 0x365b8c, 0x277e8e, 0x1fa187, 0x49c16d, 0x9fd938, 0xfde724 };
	//float p[] = { SamplePos0, SamplePos1, SamplePos2, SamplePos3, SamplePos4, SamplePos5, SamplePos6, SamplePos7, SamplePos8, SamplePos9 };
	//unsigned int c[] = { SampleValue0, SampleValue1, SampleValue2, SampleValue3, SampleValue4, SampleValue5, SampleValue6, SampleValue7, SampleValue8, SampleValue9 };
	float p[] = { 0.00f, 1.00f};
	unsigned int c[] = { EdgeDefaultColor, EdgeJamColor };
	ColorMap::Init(2, p, c);

	Controller controller(SCR_WIDTH, SCR_HEIGHT);
	controller.Start();

	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_PROGRAM_POINT_SIZE);

	double mouse_pos_x;
	double mouse_pos_y;

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);

		Input::mouse_last_pos_x_ = Input::mouse_pos_x_;
		Input::mouse_last_pos_y_ = Input::mouse_pos_y_;
		glfwGetCursorPos(window, &mouse_pos_x, &mouse_pos_y);
		Input::mouse_pos_x_ = 2.0f * static_cast<float>(mouse_pos_x) / SCR_WIDTH - 1.0f;
		Input::mouse_pos_y_ = -2.0f * static_cast<float>(mouse_pos_y) / SCR_HEIGHT + 1.0f;

		controller.Update();

		glfwSwapBuffers(window);

		Time::Tick();
	}

	LineRenderer::Terminate();
	TriangleRenderer::Terminate();
	SpriteRenderer::Terminate();
	TextRenderer::Terminate();
	QuadRenderer::Terminate();
	CharacterLibrary::Terminate();
	InstancedMeshRenderer::Terminate();
	ColorMap::Terminate();
	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (0 <= key && key <= 1024)
	{
		if (action == GLFW_PRESS)
			Input::keys_[key] = true;
		else if (action == GLFW_RELEASE)
		{

			Input::keys_[key] = false;
			Input::processed_keys_[key] = false;
		}
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mode)
{
	if (0 <= button && button < 16)
	{
		if (action == GLFW_PRESS)
		{
			Input::buttons_[button] = true;
			Input::free_buttons_[button] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			Input::buttons_[button] = false;
			Input::processed_buttons_[button] = false;
		}
	}
}

void mouse_movement_callback(GLFWwindow* window, double x, double y)
{
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Input::scroll_offset_y_ = yoffset;
}

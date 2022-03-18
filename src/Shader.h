#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>


class Shader
{
public:
	GLuint program_;
	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath=NULL);
	~Shader();

	void Use();
	void Unuse();

	void SetVec2(const GLchar* uniformName, const glm::vec2& vec);
	void SetVec3(const GLchar* uniformName, const glm::vec3& vec);
	void SetVec4(const GLchar* uniformName, const glm::vec4& vec);
	void Set1f(const GLchar* uniformName, GLfloat x);
	void SetMat3(const GLchar* uniformName, const glm::mat3& mat);
	void SetMat4(const GLchar* uniformName, const glm::mat4& mat);
	void Set1i(const GLchar* uniformName, GLint i);

private:
	std::string LoadCode(const char* shaderPath);
};


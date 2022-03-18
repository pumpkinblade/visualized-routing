#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
{
	this->program_ = 0;

	// 编译信息
	GLint success;
	GLchar infoLog[512];

	// 顶点着色器
	GLuint vertex;
	// 加载源码
	std::string vertexCode = LoadCode(vertexPath);
	const GLchar* vShaderCode = vertexCode.c_str();
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	// 检查编译错误
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << vertexPath << std::endl;
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << std::endl;
		std::cout << infoLog << std::endl;
		return;
	}

	// 片段着色器
	GLuint fragment;
	// 加载源码
	std::string fragmentCode = LoadCode(fragmentPath);
	const GLchar* fShaderCode = fragmentCode.c_str();
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	// 检查编译错误
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << fragmentPath << std::endl;
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << std::endl;
		std::cout << infoLog << std::endl;
		return;
	}

	// 几何着色器
	GLuint geometry;
	if (geometryPath != NULL)
	{
		// 加载源码
		std::string geometryCode = LoadCode(geometryPath);
		const GLchar* gShaderCode = geometryCode.c_str();
		geometry = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometry, 1, &gShaderCode, NULL);
		glCompileShader(geometry);
		// 检查编译错误
		glGetShaderiv(geometry, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(geometry, 512, NULL, infoLog);
			std::cout << geometryPath << std::endl;
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << std::endl;
			std::cout << infoLog << std::endl;
			return;
		}
	}

	// 链接着色器程序
	this->program_ = glCreateProgram();
	glAttachShader(this->program_, vertex);
	glAttachShader(this->program_, fragment);
	if(geometryPath != NULL)
		glAttachShader(this->program_, geometry);
	glLinkProgram(this->program_);
	// 检查链接错误
	glGetProgramiv(this->program_, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->program_, 512, NULL, infoLog);
		std::cout << vertexPath << "---" << fragmentPath << "---" << geometryPath << std::endl;
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		return;
	}
	// 删除着色器
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	if(geometryPath != NULL)
		glDeleteShader(geometry);
}

Shader::~Shader()
{
	glDeleteProgram(this->program_);
}

void Shader::Use()
{
	glUseProgram(this->program_);
}

void Shader::Unuse()
{
	glUseProgram(0);
}

void Shader::SetVec2(const GLchar* uniformName, const glm::vec2& vec)
{
	GLint loc = glGetUniformLocation(this->program_, uniformName);
	glUniform2f(loc, vec.x, vec.y);
}

void Shader::SetVec3(const GLchar* uniformName, const glm::vec3& vec)
{
	GLint loc = glGetUniformLocation(this->program_, uniformName);
	glUniform3f(loc, vec.x, vec.y, vec.z);
}

void Shader::SetVec4(const GLchar* uniformName, const glm::vec4& vec)
{
	GLint loc = glGetUniformLocation(this->program_, uniformName);
	glUniform4f(loc, vec.x, vec.y, vec.z, vec.w);
}

void Shader::Set1f(const GLchar* uniformName, GLfloat x)
{
	GLint loc = glGetUniformLocation(this->program_, uniformName);
	glUniform1f(loc, x);
}

void Shader::SetMat3(const GLchar* uniformName, const glm::mat3& mat)
{
	GLint loc = glGetUniformLocation(this->program_, uniformName);
	glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::SetMat4(const GLchar* uniformName, const glm::mat4& mat)
{
	GLint loc = glGetUniformLocation(this->program_, uniformName);
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::Set1i(const GLchar* uniformName, GLint i)
{
	GLint loc = glGetUniformLocation(this->program_, uniformName);
	glUniform1i(loc, i);
}

std::string Shader::LoadCode(const char* shaderPath)
{
	// 从文件路径获得着色器
	std::string shaderCode;
	std::ifstream shaderFile;
	// 保证ifstream对象可以抛出异常
	shaderFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
	try
	{
		// 打开文件
		shaderFile.open(shaderPath);
		std::stringstream shaderStream;
		// 读取
		shaderStream << shaderFile.rdbuf();
		// 关闭文件
		shaderFile.close();
		// 转换流至GLchar数组
		shaderCode = shaderStream.str();
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << shaderPath << std::endl;
		std::cout << "ERROR::SHADER::file can't be successfully read" << std::endl;
		std::cout << e.what() << std::endl;
		if (shaderFile.is_open())
			shaderFile.close();
		return "\0";
	}
	return shaderCode;
}

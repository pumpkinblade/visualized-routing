#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "Shader.h"
#include "Tools.h"
#include "Primitive.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class SpriteRenderer
{
public:
	static void Draw(GLuint tex, const glm::vec2& position, const glm::vec2& size);
	static void SetProjectionMatrix(const glm::mat4& projection);
	static void Init();
	static void Terminate();
private:
	static Shader* shader_;
	static Quad* mesh_;

	SpriteRenderer() = delete;
};

class TriangleRenderer
{
public:
	static void Init();
	static void Terminate();
	static void Draw(const glm::vec2& position, const glm::vec2& scale, const glm::vec3& color);
	static void SetProjectionMatrix(const glm::mat4& projection);
private:
	TriangleRenderer() = delete;

	static Shader* shader_;
	static Triangle* defaultTriangle_;
};

// 画边用的渲染器
class LineRenderer
{
public:
	static void Init();
	static void Terminate();
	// 参数分别是起点和终点坐标（为了方便，用一个四维向量来表示，xy是起点坐标，zw是终点坐标），颜色
	static void Draw(const glm::vec4& start_and_end, const glm::vec3& color);
	static void SetProjectionMatrix(const glm::mat4& projection);
private:
	static Shader* shader_;
	static Line* defaultLine_;

	LineRenderer() = delete;
};

// 文字渲染器
class TextRenderer
{
public:
	enum class Pivot
	{
		LEFT_TOP, // 表示文字对齐左上角
		LEFT_CENTER,
		LEFT_DOWN,
		CENTER_TOP,
		CENTER_CENTER, // 表示文字居中显示
		CENTER_DOWN,
		RIGHT_TOP,
		RIGHT_CENTER,
		RIGHT_DOWN // 表示文字对齐右下角
	};
public:
	static void Init();
	static void Terminate();

	// 渲染文字：参数分别是要渲染的字符串，位置，颜色，以及文字渲染的开始位置
	static void Draw(const std::string& text, const glm::vec2& position, const glm::vec3& color=glm::vec3(1.0f), Pivot pivot = Pivot::LEFT_TOP);
	static void SetProjectionMatrix(const glm::mat4& projection);
private:
	static Shader* shader_;
	static TextMesh* mesh_;

	TextRenderer() = delete;
};

// 纯色背景渲染器
class QuadRenderer
{
public:
	static void Init();
	static void Terminate();

	// 参数分别是位置，大小，颜色
	static void Draw(const glm::vec2& position, const glm::vec2& size, const glm::vec3& color);
	static void SetProjectionMatrix(const glm::mat4& proj_mat);

private:
	static Shader* shader_;
	static Quad* quad_;

	QuadRenderer() = delete;
};

// 实例化网格渲染器
class InstancedMeshRenderer
{
public:
	static void Init();
	static void Terminate();

	static void DrawInstancedTriangle(const InstancedTriangle& tri);
	static void DrawInstancedLine(const InstancedLine& line);
	static void SetProjectionMatrix(const glm::mat4& projection);
private:
	static Shader* shader_;

	InstancedMeshRenderer() = delete;
};
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

// �����õ���Ⱦ��
class LineRenderer
{
public:
	static void Init();
	static void Terminate();
	// �����ֱ��������յ����꣨Ϊ�˷��㣬��һ����ά��������ʾ��xy��������꣬zw���յ����꣩����ɫ
	static void Draw(const glm::vec4& start_and_end, const glm::vec3& color);
	static void SetProjectionMatrix(const glm::mat4& projection);
private:
	static Shader* shader_;
	static Line* defaultLine_;

	LineRenderer() = delete;
};

// ������Ⱦ��
class TextRenderer
{
public:
	enum class Pivot
	{
		LEFT_TOP, // ��ʾ���ֶ������Ͻ�
		LEFT_CENTER,
		LEFT_DOWN,
		CENTER_TOP,
		CENTER_CENTER, // ��ʾ���־�����ʾ
		CENTER_DOWN,
		RIGHT_TOP,
		RIGHT_CENTER,
		RIGHT_DOWN // ��ʾ���ֶ������½�
	};
public:
	static void Init();
	static void Terminate();

	// ��Ⱦ���֣������ֱ���Ҫ��Ⱦ���ַ�����λ�ã���ɫ���Լ�������Ⱦ�Ŀ�ʼλ��
	static void Draw(const std::string& text, const glm::vec2& position, const glm::vec3& color=glm::vec3(1.0f), Pivot pivot = Pivot::LEFT_TOP);
	static void SetProjectionMatrix(const glm::mat4& projection);
private:
	static Shader* shader_;
	static TextMesh* mesh_;

	TextRenderer() = delete;
};

// ��ɫ������Ⱦ��
class QuadRenderer
{
public:
	static void Init();
	static void Terminate();

	// �����ֱ���λ�ã���С����ɫ
	static void Draw(const glm::vec2& position, const glm::vec2& size, const glm::vec3& color);
	static void SetProjectionMatrix(const glm::mat4& proj_mat);

private:
	static Shader* shader_;
	static Quad* quad_;

	QuadRenderer() = delete;
};

// ʵ����������Ⱦ��
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
#pragma once
#include "Primitive.h"
#include <iostream>

Quad::Quad()
{
	float vertices[] = {
		 1.0f,  1.0f, 1.0f, 1.0f,  // 右上角
		 1.0f, -1.0f, 1.0f, 0.0f,  // 右下角
		-1.0f, -1.0f, 0.0f, 0.0f,  // 左下角
		-1.0f,  1.0f, 0.0f, 1.0f   // 左上角
	};

	unsigned int indices[] = {
		0, 1, 3, // 第一个三角形
		1, 2, 3  // 第二个三角形
	};

	glGenBuffers(1, &vbo_);
	glGenBuffers(1, &ebo_);
	glGenVertexArrays(1, &vao_);

	glBindVertexArray(vao_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	tex_ = 0;
}

Quad::~Quad()
{
	glDeleteBuffers(1, &ebo_);
	glDeleteBuffers(1, &vbo_);
	glDeleteVertexArrays(1, &vao_);
}

TextMesh::TextMesh()
{
	glGenBuffers(1, &vbo_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glGenVertexArrays(1, &vao_);
	glBindVertexArray(vao_);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	tex_ = 0;
}

TextMesh::~TextMesh()
{
	glDeleteBuffers(1, &vbo_);
	glDeleteVertexArrays(1, &vao_);
}


Triangle::Triangle()
{
	GLfloat triangle[] = {
		-1.0f, -1.0f,
		 1.0f, -1.0f,
		 0.0f,  1.0f
	};

	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);

	glBindVertexArray(vao_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);

	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Triangle::~Triangle()
{
	glDeleteBuffers(1, &vbo_);
	glDeleteVertexArrays(1, &vao_);
}

Line::Line()
{
	glGenBuffers(1, &vbo_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
	glGenVertexArrays(1, &vao_);
	glBindVertexArray(vao_);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

Line::~Line()
{
	glDeleteBuffers(1, &vbo_);
	glDeleteVertexArrays(1, &vao_);
}

void InstancedMesh::SetupInstanced(int instance_amount)
{
	SetupPrimitive();

	instance_amount_ = instance_amount;

	glBindVertexArray(vao_);

	glGenBuffers(1, &colorVBO_);
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO_);
	glBufferData(GL_ARRAY_BUFFER, instance_amount_ * sizeof(glm::vec3), NULL, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribDivisor(1, 1);

	// 矩阵
	glGenBuffers(1, &modelVBO_);
	glBindBuffer(GL_ARRAY_BUFFER, modelVBO_);
	glBufferData(GL_ARRAY_BUFFER, instance_amount_ * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)0);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)(sizeof(glm::vec4)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)(2 * sizeof(glm::vec4)));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)(3 * sizeof(glm::vec4)));
	glEnableVertexAttribArray(5);
	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

InstancedMesh::InstancedMesh()
	: vao_(0), modelVBO_(0), colorVBO_(0), instance_amount_(0), vertexVBO_(0)
{
}

InstancedMesh::~InstancedMesh()
{
	if (vao_)
		glDeleteVertexArrays(1, &vao_);
	if (vertexVBO_)
		glDeleteBuffers(1, &vertexVBO_);
	if (colorVBO_)
		glDeleteBuffers(1, &colorVBO_);
	if (modelVBO_)
		glDeleteBuffers(1, &modelVBO_);
}

void InstancedTriangle::SetupPrimitive()
{
	glGenVertexArrays(1, &vao_);
	glBindVertexArray(vao_);

	GLfloat triangle[] = {
		-1.0f, -1.0f,
		 1.0f, -1.0f,
		 0.0f,  1.0f
	};

	glGenBuffers(1, &vertexVBO_);
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void InstancedLine::SetupPrimitive()
{
	glGenVertexArrays(1, &vao_);
	glBindVertexArray(vao_);

	float vertices[] = {
		0.0f, 0.0f,
		1.0f, 0.0f
	};
	glGenBuffers(1, &vertexVBO_);
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
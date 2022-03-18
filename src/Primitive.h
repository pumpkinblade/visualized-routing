#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <glm/glm.hpp>

class Quad
{
public:
	Quad();
	~Quad();
	GLuint vao_;
	GLuint vbo_;
	GLuint ebo_;
	GLuint tex_;
private:
	Quad(const Quad&) = delete;
	Quad& operator=(const Quad&) = delete;
};

class TextMesh
{
public:
	TextMesh();
	~TextMesh();
	GLuint vao_;
	GLuint vbo_;
	GLuint tex_;
private:
	TextMesh(const TextMesh&) = delete;
	TextMesh& operator=(const TextMesh&) = delete;
};

class Triangle
{
public:
	Triangle();
	~Triangle();

	GLuint vao_;
	GLuint vbo_;

private:
	Triangle(const Triangle&) = delete;
	Triangle& operator=(const Triangle&) = delete;
};

class Line
{
public:
	Line();
	~Line();

	GLuint vao_;
	GLuint vbo_;
private:
	Line(const Line&) = delete;
	Line& operator=(const Line&) = delete;
};

class InstancedMesh
{
public:
	InstancedMesh();
	~InstancedMesh();

	GLuint vao_;
	GLuint vertexVBO_;
	GLuint modelVBO_;
	GLuint colorVBO_;
	int instance_amount_;

	virtual void SetupPrimitive() = 0;
	void SetupInstanced(int instance_amount);
private:
	InstancedMesh(const InstancedMesh&) = delete;
	InstancedMesh& operator=(const InstancedMesh&) = delete;
};

class InstancedTriangle : public InstancedMesh
{
public:
	virtual void SetupPrimitive() override;

};


class InstancedLine : public InstancedMesh
{
public:
	virtual void SetupPrimitive() override;
};
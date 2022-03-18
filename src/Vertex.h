#pragma once

#pragma once
#include <glm/glm.hpp>

#include <iostream>
#include <vector>

#include "Edge.h"
#include "Primitive.h"

// 顶点实体
class VertexEntity
{
public:
	VertexEntity(glm::vec2 position = glm::vec2(0.0f), glm::vec2 scale=glm::vec2(1.0f));

	// 顶点坐标
	glm::vec2 position_;
	// 顶点大小（即显示的三角形的大小）
	glm::vec2 scale_;
	// 颜色
	glm::vec3 color_;
};

// 抽象意义上的顶点
// 更新：继承EdgeList类
class Vertex : public EdgeList
{
public:
	Vertex(int id = -1, VertexEntity* entity = NULL);

	// 增加一条边
	void AddEdge(int u, float weight, EdgeEntity* entity);

	// 顶点ID
	int id_;
	int parent_;

	//// 边的链表
	//EdgeList edges_;

	VertexEntity* entity_;

	float operator-(const Vertex& another);//欧式距离
	float operator+(const Vertex& another);//哈密顿距离
};


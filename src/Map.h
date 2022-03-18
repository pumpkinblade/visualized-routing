#pragma once

#include <vector>
#include <iostream>

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Renderers.h"
#include "Scene.h"
#include "LinkGraph.h"
#include "Input.h"
#include "Primitive.h"
#include "Time.h"
#include "Constants.h"

class Map : public Scene, public LinkGraph
{
public:
	Map(GLuint screenWidth = 1000, GLuint screenHeight = 800);
	virtual ~Map();

	// 画图
	void Draw();

	// 聚焦在某一个点
	void FoucsOn(int id);

	// 从文件中读取地图
	void LoadFromFile(const char* vertex_file, const char* edge_file);

	// 清除所有的点和边
	void Clear();

	// 检查是否有鼠标点击顶点
	void ClickVertex();

	// 
	void ProcessInput();
	// 更新，每一帧都调用
	void Update();

	// 
	void ShowAroundPoint(int id, int num);
	//
	void ShowShortestPath(int start_id, int end_id);
	float theDistance_;
	// 所有顶点实体的集合
	VertexEntity* vertex_entities_;
	// 所有边实体的集合
	EdgeEntity* edge_entities_;
	// 当前被点击的点
	int clicked_vertex_;
	glm::vec3 clicked_vertex_color;
	// 是否拖拽地图
	bool translated_;
	// 
	bool control_enabled_;
	// 设置是否模拟车流
	void SetSimulate(bool simulate);
	// 当前是否正在模拟车流
	bool IsSimulating()const;
	// 设置暂停
	void SetPause(bool pause);
	// 是否暂停模拟
	bool IsPaused()const;
private:
	// 改变单个顶点颜色，并传送到实例化数组里
	void ChangeTriangleColor(int id, const glm::vec3& color);
	// 对一条路径进行染色
	void ColoringPath(const Path& path);
	// 重置所有的颜色
	void ResetColor();
	// 根据交通堵塞情况计算边的颜色
	void SetTrafficColor();
	// 更新一次路况
	void Simulate();

	// 把数据传送到实例化数组里
	void BlitTriangleModelInstanced();
	void BlitTrianlgeColorInstanced();
	void BlitLineModelInstanced();
	void BlitLineColorInstanced();

	// 一堆三角形的网格
	InstancedTriangle trimesh_;
	// 一堆线的网格
	InstancedLine linemesh_;
	// 是否正在模拟
	bool simulating_;
	// 模拟暂停
	bool paused_;
	float timer_;

	bool showingAroundPoint_;
	int centerVertex_;
	int aroundAmount_;
	bool showingShortestPoint_;
	int startVertex_;
	int endVertex_;
};
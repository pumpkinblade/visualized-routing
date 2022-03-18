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

	// ��ͼ
	void Draw();

	// �۽���ĳһ����
	void FoucsOn(int id);

	// ���ļ��ж�ȡ��ͼ
	void LoadFromFile(const char* vertex_file, const char* edge_file);

	// ������еĵ�ͱ�
	void Clear();

	// ����Ƿ������������
	void ClickVertex();

	// 
	void ProcessInput();
	// ���£�ÿһ֡������
	void Update();

	// 
	void ShowAroundPoint(int id, int num);
	//
	void ShowShortestPath(int start_id, int end_id);
	float theDistance_;
	// ���ж���ʵ��ļ���
	VertexEntity* vertex_entities_;
	// ���б�ʵ��ļ���
	EdgeEntity* edge_entities_;
	// ��ǰ������ĵ�
	int clicked_vertex_;
	glm::vec3 clicked_vertex_color;
	// �Ƿ���ק��ͼ
	bool translated_;
	// 
	bool control_enabled_;
	// �����Ƿ�ģ�⳵��
	void SetSimulate(bool simulate);
	// ��ǰ�Ƿ�����ģ�⳵��
	bool IsSimulating()const;
	// ������ͣ
	void SetPause(bool pause);
	// �Ƿ���ͣģ��
	bool IsPaused()const;
private:
	// �ı䵥��������ɫ�������͵�ʵ����������
	void ChangeTriangleColor(int id, const glm::vec3& color);
	// ��һ��·������Ⱦɫ
	void ColoringPath(const Path& path);
	// �������е���ɫ
	void ResetColor();
	// ���ݽ�ͨ�����������ߵ���ɫ
	void SetTrafficColor();
	// ����һ��·��
	void Simulate();

	// �����ݴ��͵�ʵ����������
	void BlitTriangleModelInstanced();
	void BlitTrianlgeColorInstanced();
	void BlitLineModelInstanced();
	void BlitLineColorInstanced();

	// һ�������ε�����
	InstancedTriangle trimesh_;
	// һ���ߵ�����
	InstancedLine linemesh_;
	// �Ƿ�����ģ��
	bool simulating_;
	// ģ����ͣ
	bool paused_;
	float timer_;

	bool showingAroundPoint_;
	int centerVertex_;
	int aroundAmount_;
	bool showingShortestPoint_;
	int startVertex_;
	int endVertex_;
};
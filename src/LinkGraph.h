#pragma once
#include <iostream>
#include <fstream>
#include "Vertex.h"
#include "Edge.h"
#include <string>
#include <sstream>
#include "Heap.h"
#include "Path.h"

class LinkGraph
{
public:
	LinkGraph();
	~LinkGraph();
	void Init();
	// ������еĵ�ͱ�
	void Clear();
	//��ʼ��ˢ�±�
	//���ţ���Ϊ�����·����һ����Ҫ��sPoint��ʼ��Ϊ0���������Ĭ��ֵ��ͬʱ��markset��ʼ��ȫΪfalse
	void InitPointSet(int sPoint=-1);
    //��ȡ����v�ĵ�һ���ھ�
	int First(int v);
	//��ȡ����v��w�������һ���ھ�
	int Next(int v, int w);
    //����pointName���Ϸ��ʱ��
	void SetMark(int pointName);
	//��ȡ��pointName�Ƿ��б��
	int GetMark(int pointName);
	//��ȡ��v�͵�w�ı�Ȩ
	float GetWeight(int v, int w);
	//���������num�����Լ�����·�����޸ģ����traffic�������ǽ�ͨ��
	void AroundPoint(int pointName, int num, bool traffic=false);
	// ���еĶ��㣨���������Լ��ı��б�
	Vertex* vertices_;
	//·���洢����
	Path p[128];
	// ��������
	int num_vertices_;
	//(��)���·��
	Path shortestPath_;
	// ������
	int num_edges_;
	//���³��������ݣ����趨Ϊÿ��һ��ʱ���Զ����£������ֶ�����
	void UpdateTraffic();
	//ע�����������Ĭ�ϲ����ǣ������ǳ�����������Dijkstra�㷨������ŷ�Ͼ���
	// ����·���ĳ���
	float FindPath(int start_id, int end_id, bool traffic=false, bool dijkstra=false, bool distanceMode=false, float MUL=0.7);
private:
	// С����
	Heap heap_;
	//���ĳһ�����Ƿ񱻷��ʵ�����
	int* markSet_;   
	//���ڴ��A*�еľ��루F=G+H����Dijkstra�еľ��루�ţ�
	//�������ÿһ�θ���һ�������̾������ݣ��ˣ�
	float* pointSet_;//���ţ���int*��Ϊ��float*,���ܻ�Ե˵ĳ������Ӱ��
};


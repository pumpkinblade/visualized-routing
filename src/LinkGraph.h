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
	// 清除所有的点和边
	void Clear();
	//初始化刷新表
	//（张）因为求最短路径不一定需要将sPoint初始化为0，因此增加默认值；同时将markset初始化全为false
	void InitPointSet(int sPoint=-1);
    //获取顶点v的第一个邻居
	int First(int v);
	//获取顶点v中w顶点的下一个邻居
	int Next(int v, int w);
    //给点pointName打上访问标记
	void SetMark(int pointName);
	//获取点pointName是否有标记
	int GetMark(int pointName);
	//获取点v和点w的边权
	float GetWeight(int v, int w);
	//搜索最近的num个点以及返回路径（修改：添加traffic参数考虑交通）
	void AroundPoint(int pointName, int num, bool traffic=false);
	// 所有的顶点（顶点类有自己的边列表）
	Vertex* vertices_;
	//路径存储数组
	Path p[128];
	// 顶点数量
	int num_vertices_;
	//(张)最短路径
	Path shortestPath_;
	// 边数量
	int num_edges_;
	//更新车流量数据，可设定为每隔一定时间自动更新，或者手动调用
	void UpdateTraffic();
	//注意这个函数的默认参数是：不考虑车流量，不用Dijkstra算法，采用欧氏距离
	// 返回路径的长度
	float FindPath(int start_id, int end_id, bool traffic=false, bool dijkstra=false, bool distanceMode=false, float MUL=0.7);
private:
	// 小顶堆
	Heap heap_;
	//标记某一顶点是否被访问的数组
	int* markSet_;   
	//用于存放A*中的距离（F=G+H）或Dijkstra中的距离（张）
	//用来存放每一次更新一个点后最短距离数据（邓）
	float* pointSet_;//（张）从int*改为了float*,可能会对邓的程序产生影响
};


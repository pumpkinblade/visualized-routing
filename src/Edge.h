#pragma once
#include <glm/glm.hpp>

// 边实体
class EdgeEntity
{
public:
	EdgeEntity(const glm::vec2& start_pos = glm::vec2(0.0f), const glm::vec2& end_pos = glm::vec2(0.0f));

	// xy分量表示起点坐标，zw分量表示终点坐标
	glm::vec2 start_;
	glm::vec2 end_;
	glm::vec3 color_;
};

// 抽象边
class Edge
{
public:
	Edge(int vertex = -1, float weight = INFINITY, EdgeEntity* entity = NULL);
	~Edge();
	bool IsOverload() { return CurrentNumber_ > VolumeMax_; }
	int Imitate();//用于即时随机产生车流量
	float Congestion() const;
	// 顶点ID
	int vertex_;
	// 边长（因为我们算的是两点之间的物理距离，使用float类型）
	float weight_;
	int VolumeMax_;//车容量
	int CurrentNumber_;//道路当前车流量
	bool OverLoad_;//过载标记
	static const int a;//常数用于构造当前车流量，可以修改
	static const int c;
	static const float x0;
	// 对应的实体
	EdgeEntity* entity_;
	// 更新，还是把Edge类作为链表结点来使用
	Edge* next_;
};

/*
	考虑到下面的这个类会引发很多的BUG，目前考虑直接把这个类合并到Vertex类
	或者采用其他方法（梁）
*/
// 边的链表
class EdgeList
{
public:
	EdgeList();
	~EdgeList();

	// 清除所有数据，并重置
	void Clear();
	// 添加一条边 // 注意这个函数会复制一份Edge
	void Append(const Edge& edge);
	//获取id=w的边
	Edge* FindEdge(int w);
	// 获取当前边
	const Edge* GetConstValue();
	//因为更新车流量的时候，需要访问并修改，因此之前  Edge GetConstValue();的无法满足要求
	//下面这个使用有风险，除了更新车流量尽量别用
	Edge* GetValue();
	// 移到起点
	void SetStart();
	// 移到终点
	void SetEnd();
	// 移到下一个点
	void Next();
	// 是否移到了链表的终点
	bool IsTail();
private:
	// 为了不必要的错误，禁止这个类的直接复制
	EdgeList(const EdgeList&) = delete;
	EdgeList& operator=(const EdgeList&) = delete;

	// 链表头结点
	Edge* head_;
	// 链表尾结点
	Edge* tail_;
	// 游标当前位置
	Edge* curr_;
};
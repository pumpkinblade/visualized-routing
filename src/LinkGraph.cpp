#include "LinkGraph.h"

LinkGraph::LinkGraph()
	:vertices_(NULL), num_edges_(0), num_vertices_(0), markSet_(NULL), pointSet_(NULL)
{
}

void LinkGraph::Init()
{
	int i, j;
	markSet_ = new int[num_vertices_];
	pointSet_ = new float[num_vertices_];
	for (i = 0; i < num_vertices_; i++)// 初始化标记数组
	{
		markSet_[i] = 0;
	}
}


LinkGraph::~LinkGraph()
{
	Clear();
}

void LinkGraph::Clear()
{
	if (vertices_ != NULL)
		delete[] vertices_;
	vertices_ = NULL;
	if (pointSet_ != NULL)
		delete[] pointSet_;
	pointSet_ = NULL;
	if (markSet_ != NULL)
		delete[] markSet_;
	markSet_ = NULL;
	num_vertices_ = 0;
	num_edges_ = 0;
}

int LinkGraph::First(int v)
{
	const Edge* it;
	vertices_[v].SetStart();
	it = vertices_[v].GetConstValue();
	if (it != NULL)
	{
		return it->vertex_;
	}
	else return -1;// 如果V没有邻居，返回-1，出现非连通图
}

int LinkGraph::Next(int v1, int v2)
{
	// 返回v1的v2的邻居
	const Edge* it = vertices_[v1].GetConstValue();
	// 定位到v2
	if (it == NULL || it->vertex_ != v2)
	{
		vertices_[v1].SetStart();// 从头开始找
		it = vertices_[v1].GetConstValue();
		while (it != NULL && it->vertex_ != v2)
		{
			vertices_[v1].Next();
			it = vertices_[v1].GetConstValue();
		}
		if (it == NULL)
			return -1;
	}
	vertices_[v1].Next();
	it = vertices_[v1].GetConstValue();
	if (it == NULL)
		return -1;
	else
		return it->vertex_;
}

void LinkGraph::SetMark(int pointName)
{
	markSet_[pointName] = 1;
}

int LinkGraph::GetMark(int pointName)
{
	return markSet_[pointName];
}

float LinkGraph::GetWeight(int v, int w)
{
	const Edge* e = vertices_[v].FindEdge(w);
	if (e == NULL)
		return INFINITY;
	return e->weight_;
}

void LinkGraph::InitPointSet(int sPoint)
{

	for (int i = 0; i < num_vertices_; i++)
	{
		pointSet_[i] = INFINITY;//将所有距离初始化为无穷大（float最大表示范围）
	}
	if (sPoint != -1)
		pointSet_[sPoint] = 0.0f;
	memset(markSet_, 0, num_vertices_ * sizeof(int));
}

void LinkGraph::AroundPoint(int pointName, int num, bool traffic)//计算最近的num个点，并且记录到达途径
{
	int i, v, w;
	float weight;
	const Edge* tempEdge;
	//初始化路径起点
	for (int i = 0; i < num; i++)
	{
		p[i].Clear();
	}

	// 更新：使用最新的Heap
	heap_.Clear();
	Heap::Leaf tempLeaf;
	tempLeaf.distance_ = 0.0f;
	tempLeaf.vertex_ = pointName;
	heap_.Insert(tempLeaf);

	InitPointSet(pointName);

	for (i = 0; i < num + 1; i++) // 因为包含了自己，所以多循环一次
	{
		// 下面的循环每次不会执行超过一次，否则原因是出现了BUG
		//do {
		//	if (!heap_.RemoveMin(temp)) return;
		//	v = temp.vertex_;
		//} while (GetMark(v) == 1);
		if (!heap_.RemoveMin(tempLeaf))
			return;
		v = tempLeaf.vertex_;
		SetMark(v);


		// 把与v相邻的顶点更新
		for (vertices_[v].SetStart(); !vertices_[v].IsTail(); vertices_[v].Next())
		{
			tempEdge = vertices_[v].GetConstValue();
			if (traffic)
				weight = tempEdge->Congestion();
			else
				weight = tempEdge->weight_;
			w = tempEdge->vertex_;
			if (pointSet_[w] > pointSet_[v] + weight)
			{
				pointSet_[w] = pointSet_[v] + weight;
				tempLeaf.distance_ = pointSet_[w];
				tempLeaf.vertex_ = w;
				heap_.Insert(tempLeaf);
				vertices_[w].parent_ = v;//记录父对象
			}
		}
		//忽略自己到自己的路径
		if (i == 0)
			continue;
		// 第i个最近的顶点已经找到了
		// 路径通过寻找父对象构造逆序路径  
		for (int j = v; j != pointName; j = vertices_[j].parent_)//从有记录的点出发，从尾到头寻找生成路径
		{
			p[i - 1].Add(j);//添加路径
		}
		p[i - 1].Add(pointName);//添加起始点
	}
}

//（张）这个函数求得的最短路径（Path类）保存在LinkGraph的属性ShortPath_中，每次调用该函数都会清空之前的Path
//除了Path，本函数还计算出了最短路径的距离distance和(在考虑车流情况下的）时间time，如果需要可以通过增加引用类型参数返回，默认会将结果打印到屏幕
//dijkstra决定是否采用Dijkstra算法；traffic决定是否考虑车流量；distancMode决定是用哈密顿距离还是欧氏距离
//true 表示哈密顿距离，10^5数量级的节点仍建议用false（在大量运算中，哈密顿距离快得多，但是采用欧氏距离相对于采用哈密顿距离可以减少一半左右循环次数）
float LinkGraph::FindPath(int start_id, int end_id, bool traffic, bool dijkstra, bool distanceMode, float MUL) {
	InitPointSet();//将所有距离设置为∞，将访问数组设置为false

	heap_.Clear();
	if (dijkstra)
		pointSet_[start_id] = 0;//Dijkstra算法
	else if (distanceMode)
		pointSet_[start_id] = MUL * (vertices_[start_id] + vertices_[end_id]);//F=G+H=0+H=H
	else
		pointSet_[start_id] = vertices_[start_id] - vertices_[end_id];

	heap_.Insert(Heap::Leaf{ start_id, pointSet_[start_id] });

	Heap::Leaf current;//current是从heap里取出来的最小元素
	int id;//id是从heap里取出来的最小元素的节点号
	float G;//距start_id节点的欧式距离
	float H;//距end_id节点的哈密顿距离
	float F;//F=G+H;
	float F1;//parent的G
	int count = 0;//估计循环次数
	int child_id;
	float distance = INFINITY;
	while (heap_.Size() != 0) {
		// 每次取出最近的点
		// 循环次数不会超过一次，如果程序没有BUG的话，RemoveMin永远是成功的（如果不成功说明不连通）
		//do {
		//	heap_.RemoveMin(current);
		//} while (markSet_[current.vertex_] && heap_.Size() != 0);
		//count++;

		if(!heap_.RemoveMin(current))
			return INFINITY;
		id = current.vertex_;
		markSet_[id] = 1;
		if (id == end_id) {
			distance = current.distance_;
			//std::cout << "Path Found!" << std::endl;
			break;
		}
		// 把这次的最近点的所有邻居放进入堆里
		for (vertices_[id].SetStart(); !vertices_[id].IsTail(); vertices_[id].Next()) {//遍历所有邻居
			const Edge* edge = vertices_[id].GetConstValue();
			child_id = edge->vertex_;
			// 带标记的点不会再次进入堆
			if (markSet_[child_id])
				continue;
			G = edge->weight_;
			//if (traffic) { if (v / n > x0)G *= (exp(v / n) + 1); }
			if (traffic)
				G *= edge->Congestion();
			if (dijkstra) {//如果是Dijkstra算法
				F = G;
				F1 = pointSet_[id];
			}
			else if (distanceMode) {
				H = MUL * (vertices_[child_id] + vertices_[end_id]);
				F = G + H;
				F1 = pointSet_[id] - MUL * (vertices_[id] + vertices_[end_id]);
			}
			else {
				H = vertices_[child_id] - vertices_[end_id];
				F = G + H;
				F1 = pointSet_[id] - (vertices_[id] - vertices_[end_id]);
			}
			if (F + F1 < pointSet_[child_id]) {
				pointSet_[child_id] = F + F1;
				//parent_[i.vertex_] = id;
				vertices_[child_id].parent_ = id;
				heap_.Insert(Heap::Leaf{ child_id, pointSet_[child_id] });
			}
		}
	}

	//清空路径所有数据
	shortestPath_.Clear();
	// 路径通过寻找父对象构造逆序路径  
	for (int j = end_id; j != start_id; j = vertices_[j].parent_)//从有记录的点出发，从尾到头寻找生成路径
	{
		shortestPath_.Add(j);//添加路径
	}
	shortestPath_.Add(start_id);//添加起始点

	return distance;
}

void LinkGraph::UpdateTraffic()
{
	// 注意，由于是无向图，一条边被存了两次（梁）
	// 比如v1->v2存一次, v2->v1也存一次
	// 所以这里一条边被更新了两次
	for (int i = 0; i < num_vertices_; i++)
		for (vertices_[i].SetStart(); !vertices_[i].IsTail(); vertices_[i].Next())
			vertices_[i].GetValue()->Imitate();
}

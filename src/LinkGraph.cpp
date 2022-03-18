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
	for (i = 0; i < num_vertices_; i++)// ��ʼ���������
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
	else return -1;// ���Vû���ھӣ�����-1�����ַ���ͨͼ
}

int LinkGraph::Next(int v1, int v2)
{
	// ����v1��v2���ھ�
	const Edge* it = vertices_[v1].GetConstValue();
	// ��λ��v2
	if (it == NULL || it->vertex_ != v2)
	{
		vertices_[v1].SetStart();// ��ͷ��ʼ��
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
		pointSet_[i] = INFINITY;//�����о����ʼ��Ϊ�����float����ʾ��Χ��
	}
	if (sPoint != -1)
		pointSet_[sPoint] = 0.0f;
	memset(markSet_, 0, num_vertices_ * sizeof(int));
}

void LinkGraph::AroundPoint(int pointName, int num, bool traffic)//���������num���㣬���Ҽ�¼����;��
{
	int i, v, w;
	float weight;
	const Edge* tempEdge;
	//��ʼ��·�����
	for (int i = 0; i < num; i++)
	{
		p[i].Clear();
	}

	// ���£�ʹ�����µ�Heap
	heap_.Clear();
	Heap::Leaf tempLeaf;
	tempLeaf.distance_ = 0.0f;
	tempLeaf.vertex_ = pointName;
	heap_.Insert(tempLeaf);

	InitPointSet(pointName);

	for (i = 0; i < num + 1; i++) // ��Ϊ�������Լ������Զ�ѭ��һ��
	{
		// �����ѭ��ÿ�β���ִ�г���һ�Σ�����ԭ���ǳ�����BUG
		//do {
		//	if (!heap_.RemoveMin(temp)) return;
		//	v = temp.vertex_;
		//} while (GetMark(v) == 1);
		if (!heap_.RemoveMin(tempLeaf))
			return;
		v = tempLeaf.vertex_;
		SetMark(v);


		// ����v���ڵĶ������
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
				vertices_[w].parent_ = v;//��¼������
			}
		}
		//�����Լ����Լ���·��
		if (i == 0)
			continue;
		// ��i������Ķ����Ѿ��ҵ���
		// ·��ͨ��Ѱ�Ҹ�����������·��  
		for (int j = v; j != pointName; j = vertices_[j].parent_)//���м�¼�ĵ��������β��ͷѰ������·��
		{
			p[i - 1].Add(j);//���·��
		}
		p[i - 1].Add(pointName);//�����ʼ��
	}
}

//���ţ����������õ����·����Path�ࣩ������LinkGraph������ShortPath_�У�ÿ�ε��øú����������֮ǰ��Path
//����Path��������������������·���ľ���distance��(�ڿ��ǳ�������µģ�ʱ��time�������Ҫ����ͨ�������������Ͳ������أ�Ĭ�ϻὫ�����ӡ����Ļ
//dijkstra�����Ƿ����Dijkstra�㷨��traffic�����Ƿ��ǳ�������distancMode�������ù��ܶپ��뻹��ŷ�Ͼ���
//true ��ʾ���ܶپ��룬10^5�������Ľڵ��Խ�����false���ڴ��������У����ܶپ����ö࣬���ǲ���ŷ�Ͼ�������ڲ��ù��ܶپ�����Լ���һ������ѭ��������
float LinkGraph::FindPath(int start_id, int end_id, bool traffic, bool dijkstra, bool distanceMode, float MUL) {
	InitPointSet();//�����о�������Ϊ�ޣ���������������Ϊfalse

	heap_.Clear();
	if (dijkstra)
		pointSet_[start_id] = 0;//Dijkstra�㷨
	else if (distanceMode)
		pointSet_[start_id] = MUL * (vertices_[start_id] + vertices_[end_id]);//F=G+H=0+H=H
	else
		pointSet_[start_id] = vertices_[start_id] - vertices_[end_id];

	heap_.Insert(Heap::Leaf{ start_id, pointSet_[start_id] });

	Heap::Leaf current;//current�Ǵ�heap��ȡ��������СԪ��
	int id;//id�Ǵ�heap��ȡ��������СԪ�صĽڵ��
	float G;//��start_id�ڵ��ŷʽ����
	float H;//��end_id�ڵ�Ĺ��ܶپ���
	float F;//F=G+H;
	float F1;//parent��G
	int count = 0;//����ѭ������
	int child_id;
	float distance = INFINITY;
	while (heap_.Size() != 0) {
		// ÿ��ȡ������ĵ�
		// ѭ���������ᳬ��һ�Σ��������û��BUG�Ļ���RemoveMin��Զ�ǳɹ��ģ�������ɹ�˵������ͨ��
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
		// ����ε������������ھӷŽ������
		for (vertices_[id].SetStart(); !vertices_[id].IsTail(); vertices_[id].Next()) {//���������ھ�
			const Edge* edge = vertices_[id].GetConstValue();
			child_id = edge->vertex_;
			// ����ǵĵ㲻���ٴν����
			if (markSet_[child_id])
				continue;
			G = edge->weight_;
			//if (traffic) { if (v / n > x0)G *= (exp(v / n) + 1); }
			if (traffic)
				G *= edge->Congestion();
			if (dijkstra) {//�����Dijkstra�㷨
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

	//���·����������
	shortestPath_.Clear();
	// ·��ͨ��Ѱ�Ҹ�����������·��  
	for (int j = end_id; j != start_id; j = vertices_[j].parent_)//���м�¼�ĵ��������β��ͷѰ������·��
	{
		shortestPath_.Add(j);//���·��
	}
	shortestPath_.Add(start_id);//�����ʼ��

	return distance;
}

void LinkGraph::UpdateTraffic()
{
	// ע�⣬����������ͼ��һ���߱��������Σ�����
	// ����v1->v2��һ��, v2->v1Ҳ��һ��
	// ��������һ���߱�����������
	for (int i = 0; i < num_vertices_; i++)
		for (vertices_[i].SetStart(); !vertices_[i].IsTail(); vertices_[i].Next())
			vertices_[i].GetValue()->Imitate();
}

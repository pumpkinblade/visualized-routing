#pragma once
#include <glm/glm.hpp>

// ��ʵ��
class EdgeEntity
{
public:
	EdgeEntity(const glm::vec2& start_pos = glm::vec2(0.0f), const glm::vec2& end_pos = glm::vec2(0.0f));

	// xy������ʾ������꣬zw������ʾ�յ�����
	glm::vec2 start_;
	glm::vec2 end_;
	glm::vec3 color_;
};

// �����
class Edge
{
public:
	Edge(int vertex = -1, float weight = INFINITY, EdgeEntity* entity = NULL);
	~Edge();
	bool IsOverload() { return CurrentNumber_ > VolumeMax_; }
	int Imitate();//���ڼ�ʱ�������������
	float Congestion() const;
	// ����ID
	int vertex_;
	// �߳�����Ϊ�������������֮���������룬ʹ��float���ͣ�
	float weight_;
	int VolumeMax_;//������
	int CurrentNumber_;//��·��ǰ������
	bool OverLoad_;//���ر��
	static const int a;//�������ڹ��쵱ǰ�������������޸�
	static const int c;
	static const float x0;
	// ��Ӧ��ʵ��
	EdgeEntity* entity_;
	// ���£����ǰ�Edge����Ϊ��������ʹ��
	Edge* next_;
};

/*
	���ǵ�����������������ܶ��BUG��Ŀǰ����ֱ�Ӱ������ϲ���Vertex��
	���߲�����������������
*/
// �ߵ�����
class EdgeList
{
public:
	EdgeList();
	~EdgeList();

	// ����������ݣ�������
	void Clear();
	// ���һ���� // ע����������Ḵ��һ��Edge
	void Append(const Edge& edge);
	//��ȡid=w�ı�
	Edge* FindEdge(int w);
	// ��ȡ��ǰ��
	const Edge* GetConstValue();
	//��Ϊ���³�������ʱ����Ҫ���ʲ��޸ģ����֮ǰ  Edge GetConstValue();���޷�����Ҫ��
	//�������ʹ���з��գ����˸��³�������������
	Edge* GetValue();
	// �Ƶ����
	void SetStart();
	// �Ƶ��յ�
	void SetEnd();
	// �Ƶ���һ����
	void Next();
	// �Ƿ��Ƶ���������յ�
	bool IsTail();
private:
	// Ϊ�˲���Ҫ�Ĵ��󣬽�ֹ������ֱ�Ӹ���
	EdgeList(const EdgeList&) = delete;
	EdgeList& operator=(const EdgeList&) = delete;

	// ����ͷ���
	Edge* head_;
	// ����β���
	Edge* tail_;
	// �α굱ǰλ��
	Edge* curr_;
};
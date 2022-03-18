#include "Edge.h"

EdgeEntity::EdgeEntity(const glm::vec2& start_pos, const glm::vec2& end_pos)
	: start_(start_pos), end_(end_pos), color_(1.0f)
{
}

const int Edge::a = 27;
const int Edge::c = 1;
const float Edge::x0 = 0.8;

Edge::Edge(int vertex, float weight, EdgeEntity* entity)
	: vertex_(vertex), entity_(entity), weight_(weight), next_(NULL)
{
	VolumeMax_ = (rand() % 20) + 80;//�������趨��80-100�м�
}

Edge::~Edge()
{
}

int Edge::Imitate()
{
	//aԽ�󣬵�·Խ���׳����ɣ��ڳ������趨Ϊ80-100��ǰ���£�������aֵ����30
	//�����趨a Ϊ10,��x0����0.8���趨�£�x>x0�ĸ���Ϊ0.31��
	//���뽫x>x0�ĸ���������0.5����x0����0.8���趨�£���a���趨Ϊ27
	CurrentNumber_ = (rand() % VolumeMax_) + a;
	return CurrentNumber_;
}

//ԭPassTime��ΪCongestion()����Ϊ��Ҫ�ķ���ֵֻ��ϵ��,ͨ��ʱ������
float Edge::Congestion() const
{
	float x = (float)CurrentNumber_ / VolumeMax_;
	if (x < x0)
		return  1;
	//if (x >= x0)return  exp(x);
	else
		return exp(x);
}

EdgeList::EdgeList()
{
	head_ = tail_ = curr_ = NULL;
}

EdgeList::~EdgeList()
{
	Clear();
}

void EdgeList::Clear()
{
	while (head_ != NULL)
	{
		curr_ = head_;
		head_ = head_->next_;
		delete curr_;
	}
	head_ = tail_ = curr_ = NULL;
}

void EdgeList::Append(const Edge& edge)
{
	if (tail_ == NULL)
	{
		head_ = curr_ = tail_ = new Edge(edge);
	}
	else
	{
		tail_ = tail_->next_ = new Edge(edge);
	}
}

Edge* EdgeList::FindEdge(int w)
{
	Edge* n = head_;
	while (n != NULL)
	{
		if (n->vertex_ == w)
			return n;
		n = n->next_;
	}
	// ���������wû��ֱ�����ߣ�����NULL
	return NULL;
}

const Edge* EdgeList::GetConstValue()
{
	return curr_;
}

Edge* EdgeList::GetValue()
{
	return curr_;
}

void EdgeList::SetStart()
{
	curr_ = head_;
}

void EdgeList::SetEnd()
{
	curr_ = tail_;
}

void EdgeList::Next()
{
	if (curr_ != NULL)
		curr_ = curr_->next_;
}

bool EdgeList::IsTail()
{
	return curr_ == NULL;
}
#include "Vertex.h"

 VertexEntity::VertexEntity(glm::vec2 position, glm::vec2 scale)
     :position_(position), scale_(scale), color_(1.0f)
 {
 }

Vertex::Vertex(int id, VertexEntity* entity)
	: EdgeList(), id_(id), entity_(entity), parent_(-1)
{
}

void Vertex::AddEdge(int u, float weight, EdgeEntity* entity)
{
	Append(Edge(u, weight, entity));
}

float Vertex::operator-(const Vertex& another) {//¼ÆËãÅ·ÊÏ¾àÀë
    return sqrt(pow((this->entity_->position_.x - another.entity_->position_.x), 2) + pow((this->entity_->position_.y - another.entity_->position_.y), 2));
}
float Vertex::operator+(const Vertex& another) {//¼ÆËã¹þÃÜ¶Ù¾àÀë
    return abs((this->entity_->position_.x - another.entity_->position_.x)) + abs((this->entity_->position_.y - another.entity_->position_.y));
}
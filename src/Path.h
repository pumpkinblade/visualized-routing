#pragma once

#include "Edge.h"
#include "Vertex.h"

class Path
{
public:
	Path();
	~Path();
	// 清除所有数据
	void Clear();
	// 添加一个路径结点
	void Add(int vertex);
	// 返回数组的长度
	int Length() const;
	// 重载操作符以获取路径结点
	int operator[](int i) const;
	// 返回形如v0->v1->v2....->vn的字符串
	std::string ToString();
private:
	// 为了避免运行时错误，不要直接复制这个类
	Path(const Path&) = delete;
	Path& operator=(const Path&) = delete;
	//Vertex** path_;
	int* path_;

	// 当前数组path_的长度
	int length_;
	// 最大长度
	int max_length_;
};
#pragma once
#include <iostream>
#include <memory>

class Heap
{
public:
	struct Leaf
	{
		int vertex_;
		float distance_;
	};
public:
	Heap();
	~Heap();
	int Size() const;
	void Clear();
	void Insert(const Leaf& e);
	bool RemoveMin(Leaf& out);

private:
	Heap(const Heap&) = delete;
	Heap& operator=(const Heap&) = delete;

	bool IsLeaf(int pos) const;
	int LeftChild(int pos) const;
	int RightChild(int pos) const;
	int Parent(int pos) const;
	void Swap(int i, int j);
	void SiftDown(int pos);
	void SiftUp(int pos);

	Leaf* heap_;
	int size_;
	int max_size_;
};

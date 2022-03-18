#include"Heap.h"


Heap::Heap()
{
	size_ = 0;
	max_size_ = 1024;
	heap_ = new Leaf[max_size_];
}

Heap::~Heap()
{
	delete heap_;
}

int Heap::Size() const
{
	return size_;
}

void Heap::Clear()
{
	size_ = 0;
}

void Heap::Insert(const Leaf& e)
{
	if (size_ >= max_size_)
	{
		Leaf* temp = new Leaf[max_size_ * 2];
		memcpy(temp, heap_, max_size_*sizeof(Leaf));
		delete[] heap_;
		heap_ = temp;
		max_size_ *= 2;
	}
	heap_[size_] = e;
	SiftUp(size_);
	size_++;
}

bool Heap::RemoveMin(Leaf& out)
{
	if (size_ == 0)
		return false;
	out = heap_[0];
	heap_[0] = heap_[--size_];
	if (size_ != 0)
		SiftDown(0);
	return true;
}

int Heap::LeftChild(int pos)const
{
	return 2 * pos + 1;
}

int Heap::RightChild(int pos)const
{
	return 2 * pos + 2;
}

int Heap::Parent(int pos)const
{
	return (pos - 1) / 2;
}

bool Heap::IsLeaf(int pos)const
{
	return size_ / 2 <= pos && pos < size_;
}

void Heap::Swap(int i, int j)
{
	Leaf temp = heap_[i];
	heap_[i] = heap_[j];
	heap_[j] = temp;
}

void Heap::SiftDown(int pos)
{
	while (!IsLeaf(pos))
	{
		int l = LeftChild(pos);
		int r = RightChild(pos);
		if (r < size_ && heap_[r].distance_ < heap_[l].distance_)
			l = r;
		if (heap_[pos].distance_ < heap_[l].distance_)
			break;
		else
		{
			Swap(pos, l);
			pos = l;
		}
	}
}

void Heap::SiftUp(int pos)
{
	int parent = Parent(pos);
	while (pos > 0 && heap_[pos].distance_ < heap_[parent].distance_)
	{
		Swap(parent, pos);
		pos = parent;
		parent = Parent(pos);
	}
}

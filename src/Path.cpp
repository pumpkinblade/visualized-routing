#include "Path.h"
#include <sstream>


Path::Path()
	:length_(0), max_length_(4)
{
	path_ = new int[max_length_];
}

Path::~Path()
{
	delete[] path_;
}

void Path::Clear()
{
	length_ = 0;
}

void Path::Add(int vertex)
{
	if (length_ >= max_length_)
	{
		// 扩展数组长度
		int* tmp = new int[max_length_ * 2];
		std::memcpy(tmp, path_, max_length_*sizeof(int));
		delete[] path_;
		path_ = tmp;
		max_length_ *= 2;
	}
	path_[length_++] = vertex;
}

int Path::Length()const
{
	return length_;
}

int Path::operator[](int i)const
{
	return path_[i];
}

std::string Path::ToString()
{
	if (length_ <= 0)
		return "";
	std::stringstream ss;
	ss << path_[0];
	for (int i = 1; i < length_; i++)
		ss << "->" << path_[i];
	return ss.str();
}

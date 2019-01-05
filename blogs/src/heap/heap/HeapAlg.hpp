#pragma once
#include <vector>

template<typename T>
void push_heap(std::vector<T> &vec, T value)
{
	vec.push_back(value);
	int i = vec.size()-1;
	while (i > 1 && vec[i] > vec[i / 2]) {
		std::swap(vec[i], vec[i / 2]);
		i = i / 2;
	}
}

template<typename T>
T pop_heap(std::vector<T> &vec)
{
	int i = 1;
	//将最后元素与第一个元素(根元素)交换, 然后删除最后一个元素
	std::swap(vec[1], vec[vec.size() - 1]);
	T v = vec[vec.size() - 1];
	vec.pop_back();

	//将现在的第一个元素/根元素下沉到一个合适的位置
	while (2 * i < vec.size()) {
		int j = 2 * i;	//左子节点
		if (j < vec.size() - 1 && vec[j] < vec[j + 1]) j++;
		if (vec[j] < vec[i]) break;
		std::swap(vec[i], vec[j]);
		i = j;
	}
	return v;
}

template<typename T>
void sort_heap(std::vector<T> &vec)
{
	std::vector<T> temvec;
	int size = vec.size()-1;
	while (size != 0) {
		temvec.push_back(pop_heap(vec));
		size--;
	}
	for (T value : temvec) {
		vec.push_back(value);
	}
}
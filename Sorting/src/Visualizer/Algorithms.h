#pragma once

#include <string>
#include <vector>
#include <queue>

typedef void(*AlgoFunc)(std::vector<int>*);

struct PARAMETERS {
	int bar_w;
	int bar_h_scale;
	int vector_size;
	int max_num;
	int delay;
	int delay_final;

	PARAMETERS() {
		bar_w = 0;
		bar_h_scale = 0;
		vector_size = 0;
		max_num = 0;
		delay = 0;
		delay_final = 0;
	}
	PARAMETERS(const PARAMETERS& p) {
		bar_w = p.bar_w;
		bar_h_scale = p.bar_h_scale;
		vector_size = p.vector_size;
		max_num = p.max_num;
		delay = p.delay;
		delay_final = p.delay_final;
	}
	PARAMETERS(int bar_width, int bar_height_scale, int array_size, int max, int del, int del_2) {
		bar_w = bar_width;
		bar_h_scale = bar_height_scale;
		vector_size = array_size;
		max_num = max;
		delay = del;
		delay_final = del_2;
	}
};

struct Algorithm {
	AlgoFunc func;
	std::string name;
	PARAMETERS params;

	Algorithm() : func(nullptr), name("") {}
	Algorithm(AlgoFunc f, std::string n, PARAMETERS p) : func(f), name(n), params(p) {}
};

typedef std::queue<Algorithm> Collection;

class Algorithms
{
public:
	Collection collection;
};


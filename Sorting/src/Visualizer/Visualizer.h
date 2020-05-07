#pragma once

#include "Window.h"
#include "Algorithms.h"
#include <thread>

const char PROGRAM_NAME[] = "Sorting Visualizer by Daniel Fernandez";




class Visualizer
{
public:
	static void Init();
	static void AddAlgorithm(AlgoFunc, std::string, PARAMETERS);

	static PARAMETERS& GetParameters();
	static int& getItr() { return Get().iterations; }
	static int& getGreen() { return Get().green; }
	static int& getRed() { return Get().red; }
	static bool& getSorted() { return Get().sorted; }

	static void sleep() { std::this_thread::sleep_for(std::chrono::milliseconds(Get().parameters.delay)); }
	static void sleep_final() { std::this_thread::sleep_for(std::chrono::milliseconds(Get().parameters.delay_final)); }

	PARAMETERS parameters;
	int iterations;
	int green;
	int red;
	bool sorted;

private:
	Visualizer();
	static Visualizer& Get();
	
	void DrawBars();
	void ResetParams();
	void RandomVector();

	std::vector<int> _arr;
	Window _window;
	Algorithms _algorithms;

	
};


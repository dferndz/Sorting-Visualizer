#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <stack>
#include <thread>
#include <chrono>
#include <cmath>
#include <time.h>
#include <string>

const int W = 800;
const int H = 600;

int BAR_W = 10;
const int BAR_H_SCALE = 10;

const int VECTOR_SIZE = 80;
const int MAX_NUM = 50;

const int DELAY = 3;
const int DELAY_2 = 2000;

struct SORT {
	void(*func)(std::vector<int>*);
	std::string name;

	SORT() : func(nullptr), name("") {}
	SORT(void(*s)(std::vector<int>*), std::string n) : func(s), name(n) {}
};

bool sorted = false;
int iterations = 0;
int green = 0;
int red = 0;

void DrawBars(SDL_Renderer*, std::vector<int>&);
void SelectionSort(std::vector<int>*);
void BubbleSort(std::vector<int>*);
void RandomVector(std::vector<int>&, int);

void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}


int partition(std::vector<int>* arr, int low, int high)
{
	int pivot = (*arr)[high];    // pivot 
	int i = (low - 1);  // Index of smaller element 
	static int itr = 0;
	iterations = itr;

	for (int j = low; j <= high - 1; j++)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
		itr++;
		green = j;
		// If current element is smaller than or 
		// equal to pivot 
		if ((*arr)[j] <= pivot)
		{
			i++;    // increment index of smaller element 
			swap(&(*arr)[i], &(*arr)[j]);
		}
	}
	swap(&(*arr)[i + 1], &(*arr)[high]);
	return (i + 1);
}
void quickSort(std::vector<int>* arr, int low, int high)
{
	if (low < high)
	{
		
		int pi = partition(arr, low, high);
		// Separately sort elements before 
		// partition and after partition 
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}
void quickSort(std::vector<int>* arr)
{
	RandomVector(*arr, 160);
	int temp = BAR_W;
	BAR_W = 5;
	quickSort(arr, 0, (*arr).size() - 1);
	std::this_thread::sleep_for(std::chrono::milliseconds(DELAY_2));
	sorted = true;
	BAR_W = temp;
}


int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	std::vector<int> nums;
	std::stack<SORT> algorithms;
	algorithms.push(SORT(SelectionSort, "Selection sort"));
	algorithms.push(SORT(BubbleSort, "Bubble sort"));
	algorithms.push(SORT(quickSort, "Quick sort"));

	SDL_Window* window = SDL_CreateWindow("Sorting Algorithms By Daniel Fernandez", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H, SDL_WINDOW_SHOWN);
	SDL_Event event;
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24);

	SDL_Color White = { 255, 255, 255 };

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, algorithms.top().name.c_str(), White);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect Message_rect; //create a rect
	Message_rect.x = 0;  //controls the rect's x coordinate 
	Message_rect.y = 0; // controls the rect's y coordinte
	Message_rect.w = 100; // controls the width of the rect
	Message_rect.h = 100; // controls the height of the rect
	TTF_SizeText(Sans, algorithms.top().name.c_str(), &Message_rect.w, &Message_rect.h);



	RandomVector(nums, VECTOR_SIZE);

	
	auto t1 = std::thread(&*(algorithms.top().func), &nums);

	bool isRunning = true;

	while (isRunning) {

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
		SDL_RenderClear(renderer);

		if (!algorithms.empty()) {
			std::string text = algorithms.top().name;
			text += "  Vector size: ";
			text += std::to_string(nums.size());
			text +=  "   Comparisons: ";
			text += std::to_string(iterations);
			surfaceMessage = TTF_RenderText_Solid(Sans, text.c_str(), White);
			Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
			TTF_SizeText(Sans, text.c_str(), &Message_rect.w, &Message_rect.h);
		}
		else {
			surfaceMessage = TTF_RenderText_Solid(Sans, "THE END", White);
			Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
			TTF_SizeText(Sans, "THE END", &Message_rect.w, &Message_rect.h);
		}

		SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
		DrawBars(renderer, nums);

		

		
		SDL_RenderPresent(renderer);

		while (SDL_PollEvent(&event)) {
			switch (event.type)
			{
			case SDL_QUIT:
				isRunning = false;
				break;
			}
		}

		if (sorted) {
			t1.join();
			sorted = false;
			
			algorithms.pop();

			if (!algorithms.empty()) {
				RandomVector(nums, VECTOR_SIZE);
				t1 = std::thread(&*(algorithms.top().func), &nums);
			}
				
		}
	}

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
	TTF_Quit();

	if (t1.joinable())
		t1.detach();



	return 0;
}

void DrawBars(SDL_Renderer* renderer, std::vector<int>& nums) {
	SDL_Rect rect;
	rect.w = BAR_W;
	

	for (int i = 0; i < nums.size(); i++) {
		rect.x = i * BAR_W;
		rect.y = H - (nums[i] * BAR_H_SCALE);
		rect.h = nums[i] * BAR_H_SCALE;

		if(i == green)
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 1);
		else if (i == red)
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 1);
		else
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
		SDL_RenderFillRect(renderer, &rect);
	}
}

void SelectionSort(std::vector<int>* nums) {
	int selected = 0;
	iterations = 0;
	for (int i = 0; i < nums->size() - 1; i++) {
		selected = i;
		for (int k = i + 1; k < nums->size(); k++) {
			green = k;
			iterations++;
			if ((*nums)[k] < (*nums)[selected])
				selected = k;
			std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
			red = selected;
		}
		
		red = selected;
		int temp = (*nums)[i];
		(*nums)[i] = (*nums)[selected];
		(*nums)[selected] = temp;
		
		

		std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
	
	}

	sorted = true;
	std::this_thread::sleep_for(std::chrono::milliseconds(DELAY_2));
}

void BubbleSort(std::vector<int>* nums) {
	iterations = 0;

	bool swap = true;

	while (swap) {
		swap = false;
		for (int i = 0; i < nums->size() - 1; i++) {
			iterations++;
			green = i;
			red = i + 1;
			if ((*nums)[i] > (*nums)[i+1]) {
				swap = true;
				int temp = (*nums)[i];
				(*nums)[i] = (*nums)[i + 1];
				(*nums)[i + 1] = temp;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
		}
	}

	sorted = true;
	std::this_thread::sleep_for(std::chrono::milliseconds(DELAY_2));
}

void RandomVector(std::vector<int>& nums, int n) {

	nums.clear();

	std::srand(time(NULL));
	for (int i = 0; i < n; i++) {
		nums.push_back(std::rand() % MAX_NUM + 1);
	}
}
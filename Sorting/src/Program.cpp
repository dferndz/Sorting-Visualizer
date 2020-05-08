#include "Visualizer/Visualizer.h"


void SelectionSort(std::vector<int>* nums) {
	int selected = 0;
	for (int i = 0; i < nums->size() - 1; i++) {
		selected = i;
		for (int k = i + 1; k < nums->size(); k++) {
			Visualizer::getGreen() = k;
			Visualizer::getItr()++;
			if ((*nums)[k] < (*nums)[selected])
				selected = k;
			Visualizer::sleep();
			Visualizer::getRed() = selected;
		}

		Visualizer::getRed() = selected;
		int temp = (*nums)[i];
		(*nums)[i] = (*nums)[selected];
		(*nums)[selected] = temp;

		Visualizer::sleep();

	}

	Visualizer::getSorted() = true;
	Visualizer::sleep_final();
}
void BubbleSort(std::vector<int>* nums) {

	bool swap = true;
	int c = 0;

	while (swap) {
		swap = false;
		for (int i = 0; i < nums->size() - c - 1; i++) {
			Visualizer::getItr()++;
			Visualizer::getGreen() = i;
			Visualizer::getRed() = i + 1;
			if ((*nums)[i] > (*nums)[i + 1]) {
				swap = true;
				int temp = (*nums)[i];
				(*nums)[i] = (*nums)[i + 1];
				(*nums)[i + 1] = temp;
			}
			Visualizer::sleep();
		}
		c++;
	}

	Visualizer::getSorted() = true;
	Visualizer::sleep_final();
}
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
	Visualizer::getItr() = itr;

	for (int j = low; j <= high - 1; j++)
	{
		Visualizer::sleep();
		itr++;
		Visualizer::getGreen() = j;
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
	quickSort(arr, 0, (*arr).size() - 1);
	Visualizer::sleep_final();
	Visualizer::getSorted() = true;
}


int main(int argc, char* argv[]) {

	Visualizer::AddAlgorithm(BubbleSort, "Bubble Sort", PARAMETERS(
		5,		//bar width
		1,		//bar height scale
		160,	//number of elements in array
		500,		//max number generated for the array
		1,		//delay
		2000	//final delay
	));

	Visualizer::AddAlgorithm(SelectionSort, "Selection Sort", PARAMETERS(
		4,		//bar width
		1,		//bar height scale
		200,	//number of elements in array
		500,		//max number generated for the array
		1,		//delay
		2000	//final delay
	));

	

	Visualizer::AddAlgorithm(quickSort, "Quick Sort", PARAMETERS(
		2,		//bar width
		1,		//bar height scale
		400,	//number of elements in array
		500,		//max number generated for the array
		3,		//delay
		2000	//final delay
	));
	Visualizer::Init();

	return 0;
}





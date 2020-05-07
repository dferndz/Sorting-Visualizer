#include "Visualizer.h"
#include <SDL_ttf.h>
#include "contrib.h"
#include <cmath>

SDL_Color White = { 255, 255, 255 };

Visualizer& Visualizer::Get() {
	static Visualizer v;
	return v;
}

Visualizer::Visualizer():_window(PROGRAM_NAME, 800, 600) {
	ResetParams();
}

void Visualizer::ResetParams() {
	parameters.bar_w = 10;
	parameters.bar_h_scale = 10;
	parameters.vector_size = 80;
	parameters.max_num = 50;
	parameters.delay = 3;
	parameters.delay_final = 2000;
}

void Visualizer::AddAlgorithm(AlgoFunc f, std::string name, PARAMETERS params) {
	Visualizer& v = Get();

	v._algorithms.collection.push(Algorithm(f, name, params));
}

void Visualizer::Init() {
	Visualizer& v = Get();
	TTF_Init();
	std::thread t1;
	TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 16);

	SDL_Color White = { 255, 255, 255 };

	SDL_Surface* surfaceMessage;
	SDL_Texture* Message;

	SDL_Rect Message_rect; //create a rect
	Message_rect.x = 0;  //controls the rect's x coordinate 
	Message_rect.y = 0; // controls the rect's y coordinte

	surfaceMessage = TTF_RenderText_Solid(Sans, "THE END", White);
	Message = SDL_CreateTextureFromSurface(v._window.getRenderer(), surfaceMessage);
	TTF_SizeText(Sans, "THE END", &Message_rect.w, &Message_rect.h);

	if (!v._algorithms.collection.empty()) {
		v.parameters = v._algorithms.collection.front().params;
		v.RandomVector();
		t1 = std::thread(&*(v._algorithms.collection.front().func), &v._arr);
		
	}

	while (v._window.isRunning()) {
		v._window.update();

		//visualizer content...

		if (!v._algorithms.collection.empty()) {
			std::string text = v._algorithms.collection.front().name;
			text += "  Vector size: ";
			text += std::to_string(v._arr.size());
			text += "   Comparisons: ";
			text += std::to_string(v.iterations);
			text += "   Delay: ";
			text += std::to_string(v.parameters.delay);
			text += " ms";
			surfaceMessage = TTF_RenderText_Solid(Sans, text.c_str(), White);
			Message = SDL_CreateTextureFromSurface(v._window.getRenderer(), surfaceMessage);
			TTF_SizeText(Sans, text.c_str(), &Message_rect.w, &Message_rect.h);

			
		}
		else {
			surfaceMessage = TTF_RenderText_Solid(Sans, "THE END", White);
			Message = SDL_CreateTextureFromSurface(v._window.getRenderer(), surfaceMessage);
			TTF_SizeText(Sans, "THE END", &Message_rect.w, &Message_rect.h);
		}

		SDL_RenderCopy(v._window.getRenderer(), Message, NULL, &Message_rect);
		SDL_FreeSurface(surfaceMessage);
		SDL_DestroyTexture(Message);
		v.DrawBars();

		if (v.sorted) {
			t1.join();
			v.sorted = false;

			v._algorithms.collection.pop();

			if (!v._algorithms.collection.empty()) {
				v.parameters = v._algorithms.collection.front().params;
				v.RandomVector();
				v.iterations = 0;
				v.green = 0;
				v.red = 0;
				t1 = std::thread(&*(v._algorithms.collection.front().func), &v._arr);
				
			}

		}
		//end visualizer content...

		v._window.draw();

		v._window.pollEvents();
	}


	TTF_Quit();

	if (t1.joinable())
		t1.detach();

}

void Visualizer::DrawBars() {

	_rect.w = parameters.bar_w;


	for (int i = 0; i < _arr.size(); i++) {
		_rect.x = i * parameters.bar_w;
		_rect.y = _window.getH() - (_arr[i] * parameters.bar_h_scale);
		_rect.h = _arr[i] * parameters.bar_h_scale;

		if (i == green)
			SDL_SetRenderDrawColor(_window.getRenderer(), 0, 255, 0, 1);
		else if (i == red)
			SDL_SetRenderDrawColor(_window.getRenderer(), 255, 0, 0, 1);
		else
			SDL_SetRenderDrawColor(_window.getRenderer(), 255, 255, 255, 1);
		SDL_RenderFillRect(_window.getRenderer(), &_rect);
	}
}

void Visualizer::RandomVector() {
	_arr.clear();
	std::srand(time(NULL));
	for (int i = 0; i <parameters.vector_size; i++)
		_arr.push_back(std::rand() % parameters.max_num + 1);
}

PARAMETERS& Visualizer::GetParameters() {
	Visualizer& v = Get();
	return v.parameters;
}
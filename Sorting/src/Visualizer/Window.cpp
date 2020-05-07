#include "Window.h"
#include "contrib.h"

Window::Window(std::string title, int w, int h) {
	SDL_Init(SDL_INIT_EVERYTHING);
	_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
	_renderer = SDL_CreateRenderer(_window, -1, 0);
	_is_running = true;
	_w = w; _h = h;
}

void Window::pollEvents() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)
			_is_running = false;
		else {
			handlers(event);
		}
	}
}

void Window::update() {
	contrib::SetDrawingColor(*this, Color::BLACK);
	SDL_RenderClear(_renderer);

}

void Window::draw() {
	SDL_RenderPresent(_renderer);
}

coord Window::getCenter() const {
	coord center;
	center.x = _w / 2;
	center.y = _h / 2;

	return center;
}

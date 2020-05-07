#pragma once


#include <SDL.h>
#include <string>
#include "Eventhandler.h"

typedef SDL_Event Event;
typedef SDL_Renderer Renderer;
typedef SDL_Rect Rect;


struct coord {
	int x, y;
};

class Window
{
public:
	Window(std::string title, int w, int h);

	inline bool isRunning() { return _is_running; }
	void pollEvents();
	void update();
	void draw();
	inline Renderer* getRenderer() { return _renderer; }

	coord getCenter() const;
	inline int getW() { return _w; }
	inline int getH() { return _h; }

	inline void Close() { _is_running = false; }

	EventHandler<SDL_Event> handlers;
private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	bool _is_running;

	int _w, _h;
};

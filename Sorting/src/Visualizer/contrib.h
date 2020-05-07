#pragma once

#include <SDL.h>
#include "Window.h"

struct _color {
	int r, g, b, a;

	_color(int red, int green, int blue, int alpha) : r(red), g(green), b(blue), a(alpha) {}
	_color(): r(0), b(0), g(0), a(0) {}
};


enum Color { BLUE, RED, YELLOW, WHITE, BLACK, GREEN };

class contrib
{
public:
	//rect
	static void CenterRect(SDL_Rect& rect, Window& window);
	static void SetDrawingColor(Window& window, Color color);
	static SDL_Rect CreateRect(int w, int h);
	static void DrawRect(Rect& rect, Window& window);
	//end rect
};


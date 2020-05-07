#include "contrib.h"



_color colors[] = {
		_color(52, 86, 223, 1), //blue
		_color(223, 52, 54, 1), //red
		_color(233, 227, 62, 1), //yellow
		_color(255, 255, 255, 1), //white
		_color(0, 0, 0, 1), //black
		_color(89, 222, 37, 1), //green
};

void contrib::CenterRect(SDL_Rect& rect, Window& window) {
	rect.x = window.getCenter().x - rect.w / 2;
	rect.y = window.getCenter().y - rect.h / 2;
}

void contrib::SetDrawingColor(Window& window, Color color) {
	SDL_SetRenderDrawColor(window.getRenderer(), colors[color].r, colors[color].g, colors[color].b, colors[color].a);
}

SDL_Rect contrib::CreateRect(int w, int h) {
	SDL_Rect rect;
	rect.w = w; rect.h = h;
	return rect;
}

void contrib::DrawRect(Rect& rect, Window& window) {
	SDL_RenderFillRect(window.getRenderer(), &rect);
}
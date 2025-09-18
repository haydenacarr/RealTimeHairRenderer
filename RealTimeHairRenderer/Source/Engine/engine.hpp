#pragma once

#include "../common.hpp"
#include "Renderer/renderer.hpp"

#include <SDL.h>


class Engine {
public:
	Engine() = default;

	bool init();
	void update();
	bool cleanup();

private:
	Renderer renderer;
	SDL_Window* window;
};
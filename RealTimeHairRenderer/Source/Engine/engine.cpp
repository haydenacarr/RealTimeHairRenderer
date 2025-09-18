#include "engine.hpp"
#include "../window.hpp"

bool Engine::init() {
	this->window = createSDLWindow();
	HWND hwnd = getHWND(this->window);
    this->renderer.createDevice();
	return true;
}

void Engine::update() {
    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
        }
    }
}

bool Engine::cleanup() {
    SDL_DestroyWindow(this->window);
    SDL_Quit();
    return true;
}
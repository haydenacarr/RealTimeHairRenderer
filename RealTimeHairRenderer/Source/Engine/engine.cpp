#include "engine.hpp"
#include "../window.hpp"

bool Engine::init() {
	this->m_window = createSDLWindow(this->m_width, this->m_height);
	this->hwnd = getHWND(this->m_window);
    if (!this->m_renderer.createDevice()) return false;
    if (!this->m_renderer.createFactory()) return false;
    if (!this->m_renderer.createCommandQueue()) return false;
    if (!this->m_renderer.createSwapChain(this->hwnd)) return false;
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
    SDL_DestroyWindow(this->m_window);
    SDL_Quit();
    return true;
}
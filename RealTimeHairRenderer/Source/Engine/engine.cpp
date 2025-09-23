#include "engine.hpp"
#include "../window.hpp"

bool Engine::init() {
	m_window = createSDLWindow(m_width, m_height);
	m_hwnd = getHWND(m_window);
    if (!m_renderer.createDevice()) return false;
    if (!m_renderer.createFactory()) return false;
    if (!m_renderer.createCommandQueue()) return false;
    if (!m_renderer.createSwapChain(m_hwnd, m_width, m_height)) return false;
    if (!m_renderer.createRenderTargets()) return false;
    if (!m_renderer.createCommandList()) return false;
    if (!m_renderer.createRootSignature()) return false;
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
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    return true;
}
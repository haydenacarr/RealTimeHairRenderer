#include "engine.hpp"
#include "../window.hpp"

// Initialises the renderer
bool Engine::init() {
	m_window = createSDLWindow(m_width, m_height);
	m_hwnd = getHWND(m_window);
    if (!m_renderer.createFactory()) return false;
    if (!m_renderer.createDevice()) return false;
    if (!m_renderer.createVertexBuffer()) return false;
    if (!m_renderer.createCommandQueue()) return false;
    if (!m_renderer.createSwapChain(m_hwnd, m_width, m_height)) return false;
    if (!m_renderer.createRenderTargets()) return false;
    if (!m_renderer.createCommandList()) return false;
    if (!m_renderer.createRootSignature()) return false;
    if (!m_renderer.createPipelineStateObject()) return false;
    if (!m_renderer.createFence()) return false;
	return true;
}

// Main render loop
void Engine::update() {
    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            // Checks if the window has been closed
            if (event.type == SDL_QUIT) {
                running = false;
            }

            // Checks if window has been resized
            if (event.type == SDL_WINDOWEVENT_RESIZED) {
                // TODO
            }

            // Checks for any keyboard inputs
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                }
            }
        }

        m_renderer.recordCommands(m_width, m_height);
        m_renderer.drawImage();
    }
}

// Cleans up any allocated resources
bool Engine::cleanup() {
    SDL_DestroyWindow(m_window);
    SDL_Quit();

    return true;
}
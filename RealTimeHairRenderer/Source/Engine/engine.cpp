#include "engine.hpp"
#include "../window.hpp"

// Initialises the renderer
bool Engine::init() {
	m_window = createSDLWindow(m_width, m_height);
	m_hwnd = getHWND(m_window);
    m_renderer.hair = m_renderer.loadHair("C:/Dev/RealTimeHairRenderer/RealTimeHairRenderer/wCurly.hair");
    m_renderer.headVertices = m_renderer.loadHead("C:/Dev/RealTimeHairRenderer/RealTimeHairRenderer/head/woman.obj");

    if (!m_renderer.createFactory()) return false;
    if (!m_renderer.createDevice()) return false;
    if (!m_renderer.createRootSignature()) return false;
    if (!m_renderer.createPipelineStateObject()) return false;
    if (!m_renderer.createVertexBuffer()) return false;
    if (!m_renderer.createIndexBuffer()) return false;
    if (!m_renderer.createDepthStencilBuffer(m_width, m_height)) return false;
    if (!m_renderer.createConstantBuffer(m_width, m_height)) return false;
    if (!m_renderer.createCommandQueue()) return false;
    if (!m_renderer.createSwapChain(m_hwnd, m_width, m_height)) return false;
    if (!m_renderer.createRenderTargets()) return false;
    if (!m_renderer.createMSAA(m_width, m_height)) return false;
    if (!m_renderer.createCommandList()) return false;
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

            const float moveSpeed = 5.0f;     
            const float rotateSpeed = 2.0f;   
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE: running = false; break;
                case SDLK_w: m_renderer.cameraMove(moveSpeed, 0.0f, 0.0f); break;
                case SDLK_s: m_renderer.cameraMove(-moveSpeed, 0.0f, 0.0f); break;
                case SDLK_a: m_renderer.cameraMove(0.0f, moveSpeed, 0.0f); break;
                case SDLK_d: m_renderer.cameraMove(0.0f, -moveSpeed, 0.0f); break;
                case SDLK_SPACE: m_renderer.cameraMove(0.0f, 0.0f, moveSpeed); break;
                case SDLK_LCTRL: m_renderer.cameraMove(0.0f, 0.0f, -moveSpeed);break;
                case SDLK_UP: m_renderer.cameraRotate(rotateSpeed, 0.0f, 0.0f); break;
                case SDLK_DOWN: m_renderer.cameraRotate(-rotateSpeed, 0.0f, 0.0f); break;
                case SDLK_LEFT: m_renderer.cameraRotate(0.0f, -rotateSpeed, 0.0f); break;
                case SDLK_RIGHT: m_renderer.cameraRotate(0.0f, rotateSpeed, 0.0f); break;
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
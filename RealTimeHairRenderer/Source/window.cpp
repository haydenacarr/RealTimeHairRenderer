#include "window.hpp"

SDL_Window* createSDLWindow() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
    }

    SDL_Window* window = SDL_CreateWindow("DX12 + SDL2", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }

    // Get HWND from SDL_Window
    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    if (!SDL_GetWindowWMInfo(window, &wmInfo)) {
        std::cerr << "SDL_GetWindowWMInfo failed: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    HWND hwnd = wmInfo.info.win.window;

    return window;
}

HWND getHWND(SDL_Window* window) {
    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    if (!SDL_GetWindowWMInfo(window, &wmInfo)) {
        std::cerr << "SDL_GetWindowWMInfo failed: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    HWND hwnd = wmInfo.info.win.window;

    return hwnd;
}
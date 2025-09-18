#include "window.hpp"
#include <windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <iostream>


int main(int argc, char* argv[]) {
    SDL_Window* window = createSDLWindow();
    HWND hwnd = getHWND(window);

    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

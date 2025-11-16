#pragma once
#include <SDL.h>
#include <windows.h>
#include <iostream>
#include <SDL_syswm.h>

SDL_Window* createSDLWindow(UINT width, UINT height);

HWND getHWND(SDL_Window* window);
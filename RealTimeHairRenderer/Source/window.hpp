#include <SDL.h>
#include <windows.h>
#pragma once
#include <SDL.h>
#include <iostream>
#include <SDL_syswm.h>

SDL_Window* createSDLWindow();

HWND getHWND(SDL_Window* window);
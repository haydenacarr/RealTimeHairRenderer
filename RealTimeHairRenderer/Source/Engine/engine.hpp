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
	Renderer m_renderer;
	SDL_Window* m_window = nullptr;
	HWND m_hwnd = nullptr;
	UINT m_width = 800;
	UINT m_height = 600;
};
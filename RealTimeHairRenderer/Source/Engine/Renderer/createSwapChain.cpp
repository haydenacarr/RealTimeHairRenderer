#include "renderer.hpp"

// The Swap Chain are buffers used to present rendered frames to the display
// When rendering is finished the Swap Chain swaps the front buffer for the back buffer
// Rendering is finished when all pixels are drawn to prevent screen tearing
bool Renderer::createSwapChain(HWND hwnd, UINT width, UINT height) {
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
	swapChainDesc.Width = width;
	swapChainDesc.Height = height; 
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.Stereo = FALSE;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // Was reading docs and think you can change this somewhere else if needed
	swapChainDesc.BufferCount = m_bufferCount; // Double buffering
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
	swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
	swapChainDesc.Flags = 0;

	if (FAILED(m_factory->CreateSwapChainForHwnd(m_commandQueue.Get(), hwnd, &swapChainDesc, nullptr, nullptr, &m_swapChain))) {
		std::cerr << "Failed to Create Swap Chain" << "\n";
		return false;
	}

	std::cout << "Swap Chain Created Successfully" << "\n";
	return true;
}
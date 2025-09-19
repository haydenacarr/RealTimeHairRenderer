#pragma once

#include "../../common.hpp"

// My renderer class carries most objects needed for rendering learned my lesson from Vulkan lol
class Renderer {
public:
    Renderer() = default;
    ~Renderer();

    bool createDevice();
    bool createFactory();
    bool createCommandQueue();
    bool createSwapChain(HWND hwnd);

private:
    const uint32_t m_bufferCount = 2;

    Microsoft::WRL::ComPtr<IDXGIFactory5> m_factory = nullptr;
    Microsoft::WRL::ComPtr<ID3D12Device> m_device = nullptr;
    Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_commandQueue = nullptr;
    Microsoft::WRL::ComPtr<IDXGISwapChain1> m_swapChain = nullptr;
};
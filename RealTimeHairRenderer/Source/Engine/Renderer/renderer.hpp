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
    bool createSwapChain(HWND hwnd, UINT width, UINT height);
    bool createRenderTargets();
    bool createCommandList();
    bool createRootSignature();

private:
    static constexpr uint32_t m_bufferCount = 2;
    uint32_t m_rtvDescriptorSize = 0;

    Microsoft::WRL::ComPtr<IDXGIFactory5> m_factory = nullptr;
    Microsoft::WRL::ComPtr<ID3D12Device> m_device = nullptr;
    Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_commandQueue = nullptr;
    Microsoft::WRL::ComPtr<IDXGISwapChain1> m_swapChain = nullptr;
    Microsoft::WRL::ComPtr<ID3D12Resource> m_renderTargets[m_bufferCount] = {};
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_rtvHeap = nullptr;
    Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_commandAllocators[m_bufferCount] = {};
    Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_commandList = nullptr;
    Microsoft::WRL::ComPtr<ID3D12RootSignature> m_rootSignature = nullptr;
};
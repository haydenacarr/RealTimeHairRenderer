#pragma once

#include "../../common.hpp"

struct Triangle {
    float position[3];
    float color[4];
};

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
    bool createPipelineStateObject();

private:
    static constexpr uint32_t m_bufferCount = 2;
    uint32_t m_rtvDescriptorSize = 0;
    Triangle m_triangle[3] = { // This is the triangle from: https://github.com/microsoft/DirectX-Graphics-Samples/blob/master/Samples/Desktop/D3D12HelloWorld/src/HelloTriangle/D3D12HelloTriangle.cpp
    { {  0.0f,  0.25f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
    { {  0.25f, -0.25f, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
    { { -0.25f, -0.25f, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } }
    };

    Microsoft::WRL::ComPtr<IDXGIFactory5> m_factory = nullptr;
    Microsoft::WRL::ComPtr<ID3D12Device> m_device = nullptr;
    Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_commandQueue = nullptr;
    Microsoft::WRL::ComPtr<IDXGISwapChain1> m_swapChain = nullptr;
    Microsoft::WRL::ComPtr<ID3D12Resource> m_renderTargets[m_bufferCount] = {};
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_rtvHeap = nullptr;
    Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_commandAllocators[m_bufferCount] = {};
    Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_commandList = nullptr;
    Microsoft::WRL::ComPtr<ID3D12RootSignature> m_rootSignature = nullptr;
    Microsoft::WRL::ComPtr<ID3D12PipelineState> m_pipelineState = nullptr;
    Microsoft::WRL::ComPtr<ID3DBlob> m_vertexShader = nullptr;
    Microsoft::WRL::ComPtr<ID3DBlob> m_pixelShader = nullptr; // Pixel Shader is Frag Shader in Vulkan
    Microsoft::WRL::ComPtr<ID3DBlob> m_signature = nullptr;
    Microsoft::WRL::ComPtr<ID3DBlob> m_error = nullptr; // I tried making these blobs class members so I could release them thinkling they were the memory leak but guess not?
};
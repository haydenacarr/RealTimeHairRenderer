#pragma once
#include "../../common.hpp"
#include <vector>
#include <fstream>

// Struct to represent the camera in a 3D space
struct Mvp {
    DirectX::XMMATRIX model;
    DirectX::XMMATRIX view;
    DirectX::XMMATRIX projection;
    DirectX::XMFLOAT4 lightDir;
    DirectX::XMFLOAT4 cameraPos;
};

struct Rot {
    float pitch;
    float yaw;
    float roll;
};

struct HairVertex {
    DirectX::XMFLOAT3 position;
    DirectX::XMFLOAT4 colour;
    DirectX::XMFLOAT3 tangent;
};

struct HeadVertex {
    DirectX::XMFLOAT3 position;
    DirectX::XMFLOAT3 normal;
    DirectX::XMFLOAT2 uv;
};

struct HairData {
    std::vector<HairVertex> vertices;
    std::vector<uint32_t> indices;
    DirectX::XMFLOAT3 tangent;
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
    bool createVertexBuffer();
    bool createIndexBuffer();
    bool createDepthStencilBuffer(UINT width, UINT height);
    bool createConstantBuffer(UINT width, UINT height);
    void recordCommands(UINT width, UINT height);
    bool createFence();
    void drawImage();

    void cameraRotate(float x, float y, float z);
    std::vector<HeadVertex> loadHead(std::string path);
    HairData loadHair(const std::string& filename);

    HairData hair;
    std::vector<HeadVertex> headVertices;
private:
    // D3D12 pipeline object necessary vars
    static constexpr uint32_t m_bufferCount = 2;
    uint32_t m_rtvDescriptorSize = 0;
    uint32_t m_currentBackBufferIndex = 0;
    uint32_t m_fenceCounter = 0;
    UINT64 m_fenceValues[m_bufferCount] = {};
    HANDLE m_fenceEvent = nullptr;

    // D3D12 pipeline objects
    Microsoft::WRL::ComPtr<IDXGIFactory5> m_factory = nullptr;
    Microsoft::WRL::ComPtr<ID3D12Device> m_device = nullptr;
    Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_commandQueue = nullptr;
    Microsoft::WRL::ComPtr<IDXGISwapChain3> m_swapChain = nullptr;
    Microsoft::WRL::ComPtr<ID3D12Resource> m_renderTargets[m_bufferCount] = {};
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_rtvHeap = nullptr;
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_dsvHeap = nullptr;
    Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_commandAllocators[m_bufferCount] = {};
    Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_commandList = nullptr;
    Microsoft::WRL::ComPtr<ID3D12RootSignature> m_rootSignature = nullptr;
    Microsoft::WRL::ComPtr<ID3D12PipelineState> m_pipelineState = nullptr;
    Microsoft::WRL::ComPtr<ID3DBlob> m_vertexShader = nullptr;
    Microsoft::WRL::ComPtr<ID3DBlob> m_pixelShader = nullptr; // Pixel Shader is Frag Shader in Vulkan
    Microsoft::WRL::ComPtr<ID3D12PipelineState> m_headPipelineState = nullptr;
    Microsoft::WRL::ComPtr<ID3DBlob> m_headVertexShader = nullptr;
    Microsoft::WRL::ComPtr<ID3DBlob> m_headPixelShader = nullptr; // Pixel Shader is Frag Shader in Vulkan
    Microsoft::WRL::ComPtr<ID3DBlob> m_signature = nullptr;
    Microsoft::WRL::ComPtr<ID3DBlob> m_error = nullptr; // I tried making these blobs class members so I could release them thinkling they were the memory leak but guess not?
    Microsoft::WRL::ComPtr<ID3D12Resource> m_vertexBuffer = nullptr;
    Microsoft::WRL::ComPtr<ID3D12Resource> m_headVertexBuffer = nullptr;
    Microsoft::WRL::ComPtr<ID3D12Resource> m_indexBuffer = nullptr;
    Microsoft::WRL::ComPtr<ID3D12Resource> m_depthStencil = nullptr;
    Microsoft::WRL::ComPtr<ID3D12Resource> m_mvpBuffer = nullptr;
    Microsoft::WRL::ComPtr<ID3D12Fence> m_fence = nullptr; // Used to synchronise the GPU, ensures rendering is done in order

    // Viewport and scissor
    D3D12_VIEWPORT m_viewport = {}; // Transforms normalised device coordinates to render target pixels
    D3D12_RECT m_scissorRect = {}; // Limits the drawing area by discarding unused pixels

    // Buffer Objects
    D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView = {}; // Holds the vertex data location
    D3D12_VERTEX_BUFFER_VIEW m_headVertexBufferView = {}; // Holds the vertex data location
    D3D12_INDEX_BUFFER_VIEW m_indexBufferView = {}; // Holds the index data location

    // Camera vars
    Mvp m_mvp = {};
    DirectX::XMVECTOR m_eyePos = {};
    DirectX::XMVECTOR m_focusPoint = {};
    DirectX::XMVECTOR m_upDir = {};
    DirectX::XMMATRIX m_model = {};
    DirectX::XMMATRIX m_view = {};
    DirectX::XMMATRIX m_projection = {};
    float m_fovAngleY = 0.0f;
    float m_aspectRatio = 0.0f;
    float m_nearZ = 0.0f;
    float m_farZ = 0.0f;
    Rot m_cameraRot = { 0.0f, 0.0f, 0.0f };
};

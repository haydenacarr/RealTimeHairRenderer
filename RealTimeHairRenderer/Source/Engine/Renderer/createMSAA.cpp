#include "renderer.hpp"

bool Renderer::createMSAA(UINT width, UINT height) {
    D3D12_HEAP_PROPERTIES heapProps = {};
    heapProps.Type = D3D12_HEAP_TYPE_DEFAULT;

    D3D12_RESOURCE_DESC heapDesc = {};
    heapDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    heapDesc.Alignment = 0;
    heapDesc.Width = width;
    heapDesc.Height = height;
    heapDesc.DepthOrArraySize = 1;
    heapDesc.MipLevels = 1;
    heapDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    heapDesc.SampleDesc.Count = 4;
    heapDesc.SampleDesc.Quality = 0;
    heapDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
    heapDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
    D3D12_CLEAR_VALUE clearValue = { DXGI_FORMAT_R8G8B8A8_UNORM,0.0f, 0.0f, 0.0f, 1.0f };

    if (FAILED(m_device->CreateCommittedResource(&heapProps, D3D12_HEAP_FLAG_NONE, &heapDesc, D3D12_RESOURCE_STATE_RESOLVE_SOURCE, &clearValue, IID_PPV_ARGS(&m_msaaRenderTarget)))) {
        std::cout << "Failed to create MSAA Render Target\n";
        return false;
    }

    m_msaaRtvHandle = m_rtvHeap->GetCPUDescriptorHandleForHeapStart();
    m_msaaRtvHandle.ptr += m_bufferCount * m_rtvDescriptorSize;

    m_device->CreateRenderTargetView(m_msaaRenderTarget.Get(), nullptr, m_msaaRtvHandle);

    std::cout << "MSAA Render Target Created Successfully\n";
    return true;
}
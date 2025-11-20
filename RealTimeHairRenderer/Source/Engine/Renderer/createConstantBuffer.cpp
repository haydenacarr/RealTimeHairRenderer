#include "renderer.hpp"

// Stores uniform data that remains constant for many draw calls.
bool Renderer::createConstantBuffer(UINT width, UINT height) {
    D3D12_HEAP_PROPERTIES heapProps = {};
    heapProps.Type = D3D12_HEAP_TYPE_UPLOAD;
    heapProps.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    heapProps.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    heapProps.CreationNodeMask = 1;
    heapProps.VisibleNodeMask = 1;

    D3D12_RESOURCE_DESC desc = {};
    desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    desc.Alignment = 0;
    desc.Width = (sizeof(Mvp) + 255) & ~255; // This aligns it to the next 255 bytes
    desc.Height = 1;
    desc.DepthOrArraySize = 1;
    desc.MipLevels = 1;
    desc.Format = DXGI_FORMAT_UNKNOWN;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    desc.Flags = D3D12_RESOURCE_FLAG_NONE;

    if (FAILED(m_device->CreateCommittedResource(&heapProps, D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&m_mvpBuffer)))) {
        return false;
    }

    // Camera setup
    m_model = DirectX::XMMatrixIdentity();
    m_eyePos = DirectX::XMVectorSet(2.0f, 0.0f, -1.0f, 1.0f);
    m_focusPoint = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
    m_upDir = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    m_view = DirectX::XMMatrixLookAtLH(m_eyePos, m_focusPoint, m_upDir);

    m_fovAngleY = DirectX::XMConvertToRadians(90.0f);
    m_aspectRatio = static_cast<float>(width) / static_cast<float>(height);

    // Clipping plane
    m_nearZ = 0.1f;
    m_farZ = 100.0f;

    m_projection = DirectX::XMMatrixPerspectiveFovLH(m_fovAngleY, m_aspectRatio, m_nearZ, m_farZ);

    // Align the memory layout for HLSL
    m_mvp.model = DirectX::XMMatrixTranspose(m_model);
    m_mvp.view = DirectX::XMMatrixTranspose(m_view);
    m_mvp.projection = DirectX::XMMatrixTranspose(m_projection);

    UINT8* mappedData = nullptr;
    D3D12_RANGE readRange = {};
    if (FAILED(m_mvpBuffer->Map(0, &readRange, reinterpret_cast<void**>(&mappedData)))) {
        return false;
    }
    memcpy(mappedData, &m_mvp, sizeof(Mvp));
    m_mvpBuffer->Unmap(0, nullptr);

    std::cout << "Constant Buffer Created Successfully" << "\n";
    return true;
}
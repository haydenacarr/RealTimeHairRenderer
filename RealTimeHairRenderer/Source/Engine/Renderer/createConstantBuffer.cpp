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

    // Camera /*TODO seperate*/
    DirectX::XMMATRIX model = DirectX::XMMatrixIdentity();
    DirectX::XMVECTOR eyePos = DirectX::XMVectorSet(2.0f, 0.0f, -1.0f, 1.0f);
    DirectX::XMVECTOR focusPoint = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
    DirectX::XMVECTOR upDir = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(eyePos, focusPoint, upDir);

    float fovAngleY = DirectX::XMConvertToRadians(90.0f);
    float aspectRatio = static_cast<float>(width) / static_cast<float>(height);

    // Clipping plane
    float nearZ = 0.1f;
    float farZ = 100.0f;

    DirectX::XMMATRIX projection = DirectX::XMMatrixPerspectiveFovLH(fovAngleY, aspectRatio, nearZ, farZ);

    // Align the memory layout for HLSL
    mvp.model = DirectX::XMMatrixTranspose(model);
    mvp.view = DirectX::XMMatrixTranspose(view);
    mvp.projection = DirectX::XMMatrixTranspose(projection);

    UINT8* mappedData = nullptr;
    D3D12_RANGE readRange = {};
    if (FAILED(m_mvpBuffer->Map(0, &readRange, reinterpret_cast<void**>(&mappedData)))) {
        return false;
    }
    memcpy(mappedData, &mvp, sizeof(Mvp));
    m_mvpBuffer->Unmap(0, nullptr);

    std::cout << "Constant Buffer Created Successfully" << "\n";
    return true;
}
#include "renderer.hpp"

// Stores the indices of an objects vertices allowing the pipeline to reuse vertices 
// reducing memory usage and improving  performance
bool Renderer::createIndexBuffer() {
    D3D12_HEAP_PROPERTIES heapProps = {};
    heapProps.Type = D3D12_HEAP_TYPE_UPLOAD;
    heapProps.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    heapProps.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    heapProps.CreationNodeMask = 1;
    heapProps.VisibleNodeMask = 1;

    D3D12_RESOURCE_DESC bufferDesc = {};
    bufferDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    bufferDesc.Alignment = 0;
    bufferDesc.Width = sizeof(m_cubeIndices);
    bufferDesc.Height = 1;
    bufferDesc.DepthOrArraySize = 1;
    bufferDesc.MipLevels = 1;
    bufferDesc.Format = DXGI_FORMAT_UNKNOWN;
    bufferDesc.SampleDesc.Count = 1;
    bufferDesc.SampleDesc.Quality = 0;
    bufferDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    bufferDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

    // Create the index buffer resource
    if (FAILED(m_device->CreateCommittedResource(&heapProps, D3D12_HEAP_FLAG_NONE, &bufferDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&m_indexBuffer)))) {
        return false;
    }

    // Copy index data
    UINT8* pIndexDataBegin = nullptr;
    D3D12_RANGE readRange = {};
    if (FAILED(m_indexBuffer->Map(0, &readRange, reinterpret_cast<void**>(&pIndexDataBegin)))) {
        return false;
    }
    memcpy(pIndexDataBegin, m_cubeIndices, CUBE_INDICES * sizeof(uint16_t));
    m_indexBuffer->Unmap(0, nullptr);

    // Describe the index buffer view
    m_indexBufferView.BufferLocation = m_indexBuffer->GetGPUVirtualAddress();
    m_indexBufferView.SizeInBytes = CUBE_INDICES * sizeof(uint16_t);
    m_indexBufferView.Format = DXGI_FORMAT_R16_UINT; 

    std::cout << "Index Buffer Created Successfully" << "\n";

    return true;
}
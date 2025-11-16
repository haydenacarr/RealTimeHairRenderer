#include "renderer.hpp"

bool Renderer::createFence() {
    if (FAILED(m_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence)))) {
        return false;
    }

    m_fenceCounter = 1;

    for (uint32_t i = 0; i < m_bufferCount; i++) {
        m_fenceValues[i] = 0;
    }

    m_fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);

    std::cout << "Fence Created Successfully" << "\n";
    return true;
}
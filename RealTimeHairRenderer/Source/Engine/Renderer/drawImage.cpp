#include "renderer.hpp"

// This function tells the CPU to wait for the GPU to finish executing all previously submitted commands.
void Renderer::drawImage() {
    m_swapChain->Present(0, 0);
    const UINT64 fence = m_fenceCounter;
    m_commandQueue->Signal(m_fence.Get(), fence);

    m_fenceValues[m_currentBackBufferIndex] = fence;
    m_fenceCounter++;
    m_currentBackBufferIndex = m_swapChain->GetCurrentBackBufferIndex();

    UINT64 fenceValueForNextFrame = m_fenceValues[m_currentBackBufferIndex];
    if (m_fence->GetCompletedValue() < fenceValueForNextFrame) {
        m_fence->SetEventOnCompletion(fenceValueForNextFrame, m_fenceEvent);
        WaitForSingleObject(m_fenceEvent, INFINITE);
    }
}
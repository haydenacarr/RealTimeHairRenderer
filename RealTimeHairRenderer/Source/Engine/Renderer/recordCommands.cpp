#include "renderer.hpp"

void Renderer::recordCommands(UINT width, UINT height) {
    m_commandAllocators[m_currentBackBufferIndex]->Reset();
    m_commandList->Reset(m_commandAllocators[m_currentBackBufferIndex].Get(), m_pipelineState.Get());

    D3D12_RESOURCE_BARRIER preDrawBarriers[2] = {};
    preDrawBarriers[0].Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    preDrawBarriers[0].Transition.pResource = m_msaaRenderTarget.Get();
    preDrawBarriers[0].Transition.StateBefore = D3D12_RESOURCE_STATE_RESOLVE_SOURCE;
    preDrawBarriers[0].Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
    preDrawBarriers[0].Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    preDrawBarriers[0].Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;

    preDrawBarriers[1].Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    preDrawBarriers[1].Transition.pResource = m_renderTargets[m_currentBackBufferIndex].Get();
    preDrawBarriers[1].Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
    preDrawBarriers[1].Transition.StateAfter = D3D12_RESOURCE_STATE_RESOLVE_DEST;
    preDrawBarriers[1].Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    preDrawBarriers[1].Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;

    m_commandList->ResourceBarrier(2, preDrawBarriers);

    m_viewport = { 0.0f, 0.0f, (float)width, (float)height, 0.0f, 1.0f }; 
    m_scissorRect = { 0, 0, (LONG)width, (LONG)height };

    D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = m_dsvHeap->GetCPUDescriptorHandleForHeapStart();
    m_commandList->OMSetRenderTargets(1, &m_msaaRtvHandle, FALSE, &dsvHandle);

    const float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    m_commandList->ClearRenderTargetView(m_msaaRtvHandle, clearColor, 0, nullptr);
    m_commandList->ClearDepthStencilView(m_dsvHeap->GetCPUDescriptorHandleForHeapStart(), D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
    m_commandList->RSSetViewports(1, &m_viewport);
    m_commandList->RSSetScissorRects(1, &m_scissorRect);
    m_commandList->SetGraphicsRootSignature(m_rootSignature.Get());
    m_commandList->SetGraphicsRootConstantBufferView(0, m_mvpBuffer->GetGPUVirtualAddress());
    m_commandList->SetPipelineState(m_headPipelineState.Get());
    m_commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_commandList->IASetVertexBuffers(0, 1, &m_headVertexBufferView);
    m_commandList->DrawInstanced(static_cast<UINT>(headVertices.size()), 1, 0, 0);
    m_commandList->SetPipelineState(m_pipelineState.Get());
    m_commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
    m_commandList->IASetVertexBuffers(0, 1, &m_vertexBufferView);
    m_commandList->IASetIndexBuffer(&m_indexBufferView);
    m_commandList->DrawIndexedInstanced(static_cast<UINT>(hair.indices.size()), 1, 0, 0, 0);

    D3D12_RESOURCE_BARRIER resolveBarrier = {};
    resolveBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    resolveBarrier.Transition.pResource = m_msaaRenderTarget.Get();
    resolveBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
    resolveBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RESOLVE_SOURCE;
    resolveBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    m_commandList->ResourceBarrier(1, &resolveBarrier);

    m_commandList->ResolveSubresource(m_renderTargets[m_currentBackBufferIndex].Get(), 0, m_msaaRenderTarget.Get(), 0, DXGI_FORMAT_R8G8B8A8_UNORM);

    D3D12_RESOURCE_BARRIER presentBarrier = {};
    presentBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    presentBarrier.Transition.pResource = m_renderTargets[m_currentBackBufferIndex].Get();
    presentBarrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RESOLVE_DEST;
    presentBarrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
    presentBarrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    m_commandList->ResourceBarrier(1, &presentBarrier);

    m_commandList->Close();
    ID3D12CommandList* lists[] = { m_commandList.Get()};
    m_commandQueue->ExecuteCommandLists(1, lists);
}
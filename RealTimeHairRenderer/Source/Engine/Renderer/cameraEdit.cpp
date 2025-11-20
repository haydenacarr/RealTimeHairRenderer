/*
#include "renderer.hpp"


turn eyePos,
void Renderer::cameraEdit(x,y,z) {
    DirectX::XMVECTOR eyePos = DirectX::XMVectorSet(2.0f, 0.0f, -1.0f, 1.0f);
    DirectX::XMVECTOR focusPoint = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
    DirectX::XMVECTOR upDir = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(eyePos, focusPoint, upDir);

    mvp.view = DirectX::XMMatrixTranspose(view);

    UINT8* mappedData = nullptr;
    D3D12_RANGE readRange = {};
    m_mvpBuffer->Map(0, &readRange, reinterpret_cast<void**>(&mappedData));
    memcpy(mappedData, &mvp, sizeof(Mvp));
    m_mvpBuffer->Unmap(0, nullptr);
}
*/
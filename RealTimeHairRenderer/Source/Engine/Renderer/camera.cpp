#include "renderer.hpp"
#include <algorithm>

void Renderer::cameraRotate(float pitch, float yaw, float roll) {
    m_cameraRot.pitch += DirectX::XMConvertToRadians(pitch);
    m_cameraRot.yaw += DirectX::XMConvertToRadians(yaw);
    m_cameraRot.roll += DirectX::XMConvertToRadians(roll);

    DirectX::XMFLOAT3 forward;
    forward.x = cosf(m_cameraRot.pitch) * sinf(m_cameraRot.yaw);
    forward.y = sinf(m_cameraRot.pitch);
    forward.z = cosf(m_cameraRot.pitch) * cosf(m_cameraRot.yaw);
    DirectX::XMVECTOR forwardVec = DirectX::XMVectorSet(forward.x, forward.y, forward.z, 0.0f);

    m_eyePos = DirectX::XMVectorSet(m_cameraMove.x, m_cameraMove.y, m_cameraMove.z, 1.0f);
    m_focusPoint = DirectX::XMVectorAdd(m_eyePos, forwardVec);
    m_upDir = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    m_view = DirectX::XMMatrixLookAtLH(m_eyePos, m_focusPoint, m_upDir);

    m_mvp.model = DirectX::XMMatrixTranspose(m_model);
    m_mvp.view = DirectX::XMMatrixTranspose(m_view);
    m_mvp.projection = DirectX::XMMatrixTranspose(m_projection);
    m_mvp.lightDir = { 0.5f, 0.5f, -0.5f, 0.0f };
    DirectX::XMStoreFloat4(&m_mvp.cameraPos, m_eyePos);

    UINT8* mappedData = nullptr;
    D3D12_RANGE readRange = {};
    if (SUCCEEDED(m_mvpBuffer->Map(0, &readRange, reinterpret_cast<void**>(&mappedData)))) {
        memcpy(mappedData, &m_mvp, sizeof(Mvp));
        m_mvpBuffer->Unmap(0, nullptr);
    }
}

void Renderer::cameraMove(float x, float y, float z) {
    DirectX::XMFLOAT3 forward;
    forward.x = cosf(m_cameraRot.pitch) * sinf(m_cameraRot.yaw);
    forward.y = sinf(m_cameraRot.pitch);
    forward.z = cosf(m_cameraRot.pitch) * cosf(m_cameraRot.yaw);

    DirectX::XMFLOAT3 right;
    right.x = sinf(m_cameraRot.yaw - DirectX::XM_PIDIV2);
    right.y = 0.0f;
    right.z = cosf(m_cameraRot.yaw - DirectX::XM_PIDIV2);

    m_cameraMove.x += forward.x * x + right.x * y;
    m_cameraMove.y += forward.y * x + z;
    m_cameraMove.z += forward.z * x + right.z * y;

    m_eyePos = DirectX::XMVectorSet(m_cameraMove.x, m_cameraMove.y, m_cameraMove.z, 1.0f);
    DirectX::XMVECTOR forwardVec = DirectX::XMVectorSet(forward.x, forward.y, forward.z, 0.0f);
    m_focusPoint = DirectX::XMVectorAdd(m_eyePos, forwardVec);
    m_upDir = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    m_view = DirectX::XMMatrixLookAtLH(m_eyePos, m_focusPoint, m_upDir);

    m_mvp.model = DirectX::XMMatrixTranspose(m_model);
    m_mvp.view = DirectX::XMMatrixTranspose(m_view);
    m_mvp.projection = DirectX::XMMatrixTranspose(m_projection);
    m_mvp.lightDir = { 0.5f, 0.5f, -0.5f, 0.0f };
    DirectX::XMStoreFloat4(&m_mvp.cameraPos, m_eyePos);

    UINT8* mappedData = nullptr;
    D3D12_RANGE readRange = {};
    if (SUCCEEDED(m_mvpBuffer->Map(0, &readRange, reinterpret_cast<void**>(&mappedData)))) {
        memcpy(mappedData, &m_mvp, sizeof(Mvp));
        m_mvpBuffer->Unmap(0, nullptr);
    }
}
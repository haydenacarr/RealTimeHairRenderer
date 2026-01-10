#include "renderer.hpp"
#include <algorithm>

// TODO REWRITING BECAUSE WAS A MESS
void Renderer::cameraRotate(float x, float y, float z) {
    m_cameraRot.pitch += DirectX::XMConvertToRadians(x);
    m_cameraRot.yaw -= DirectX::XMConvertToRadians(y);
    m_cameraRot.roll += DirectX::XMConvertToRadians(z);
}

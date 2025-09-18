#pragma once

#include "../../common.hpp"

// My renderer class carries most objects needed for rendering learned my lesson from Vulkan lol
class Renderer {
public:
    Renderer() = default;
    ~Renderer();

    bool createDevice();
    bool createFactory();
private:
    Microsoft::WRL::ComPtr<IDXGIFactory5> m_Factory = nullptr;
    Microsoft::WRL::ComPtr<ID3D12Device> m_Device = nullptr;
};
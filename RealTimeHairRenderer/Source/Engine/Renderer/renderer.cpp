#include "renderer.hpp"

Renderer::~Renderer() {
	Microsoft::WRL::ComPtr<ID3D12DebugDevice> debugDevice;
	if (SUCCEEDED(m_device->QueryInterface(IID_PPV_ARGS(&debugDevice)))) {
		debugDevice->ReportLiveDeviceObjects(D3D12_RLDO_DETAIL);
	}
}
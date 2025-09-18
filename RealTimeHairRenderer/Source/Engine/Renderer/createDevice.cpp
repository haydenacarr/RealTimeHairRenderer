#include "renderer.hpp"

// A software object representing and managing actual GPU resources and commands
bool Renderer::createDevice() {
	if (FAILED(D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_Device)))) {
		std::cerr << "Failed to Create Device" << "\n";
		return false;
	}

	std::cout << "Device Created Successfully" << "\n";
	return true;
}
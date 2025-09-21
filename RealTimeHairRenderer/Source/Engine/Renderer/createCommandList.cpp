#include "renderer.hpp"

// Command lists contain GPU commands like draw calls, resource transitions, and compute dispatches
bool Renderer::createCommandList() {
	for (uint32_t i = 0; i < m_bufferCount; ++i) {
		if (FAILED(m_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_commandAllocators[i])))) {
			std::cerr << "Failed to Create Command Allocator" << "\n";
			return false;
		}
	}

	if (FAILED(m_device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_commandAllocators[0].Get(), nullptr, IID_PPV_ARGS(&m_commandList)))) {
		std::cerr << "Failed to Create Command List" << "\n";
		return false;
	}
	m_commandList->Close(); // Close until open and pipeline state is nullptr till use

	std::cout << "Command List Created Successfully" << "\n";
	return true;
}
#include "renderer.hpp"

// The Command Queue accepts command lists and sends them to the GPU to be executed
bool Renderer::createCommandQueue() {
	D3D12_COMMAND_QUEUE_DESC commandQueueDesc = {};
	commandQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	commandQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	commandQueueDesc.NodeMask = 0;
	commandQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;

	if (FAILED(this->m_device->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&this->m_commandQueue)))) {
		std::cerr << "Failed to Command Queue" << "\n";
		return false;
	}

	std::cout << "Command Queue Created Successfully" << "\n";
	return true;
}
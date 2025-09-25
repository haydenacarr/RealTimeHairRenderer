#include "renderer.hpp"

// A Root Signature defines the layout of resources like constant buffers, textures, and samplers
// Its main job is to tell the GPU where to find the shader data efficiently
bool Renderer::createRootSignature() {
	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc = {};
	rootSignatureDesc.NumParameters = 0;
	rootSignatureDesc.pParameters = nullptr;
	rootSignatureDesc.NumStaticSamplers = 0;
	rootSignatureDesc.pStaticSamplers = nullptr;
	rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	if (FAILED(D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &m_signature, &m_error))) {
		std::cerr << "Failed to Serialize Root Signature" << "\n";
		return false;
	}

	if (FAILED(m_device->CreateRootSignature(0, m_signature->GetBufferPointer(), m_signature->GetBufferSize(), IID_PPV_ARGS(&m_rootSignature)))) {
		std::cerr << "Failed to Create Root Signature" << "\n";
		return false;
	}

	std::cout << "Root Signature Created Successfully" << "\n";
	return true;
}
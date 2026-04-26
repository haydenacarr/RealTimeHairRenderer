#include "renderer.hpp"

bool Renderer::createComputePSO() {
    D3DCompileFromFile(L"Source/Engine/Shaders/compute.hlsl", nullptr, nullptr, "CSMain", "cs_5_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &m_computeShaderBlob, &m_error);

    D3D12_COMPUTE_PIPELINE_STATE_DESC computePsoDesc = {};
    computePsoDesc.pRootSignature = m_rootSignature.Get();
    computePsoDesc.CS = {
        m_computeShaderBlob->GetBufferPointer(),
        m_computeShaderBlob->GetBufferSize()
    };

    if (FAILED(m_device->CreateComputePipelineState(&computePsoDesc, IID_PPV_ARGS(&m_computePSO)))) {
        std::cerr << "Failed to create Compute PSO" << std::endl;
        return false;
    }

    std::cout << "Compute PSO Created Successfully" << std::endl;
    return true;
}
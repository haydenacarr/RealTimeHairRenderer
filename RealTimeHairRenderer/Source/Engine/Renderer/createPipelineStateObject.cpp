#include "renderer.hpp"

// A Pipeline State Object is a configuration of the GPU pipeline which is bound to a command list
// like shaders, input layout, blend state, rasterizer state, depth-stencil settings, etc
bool Renderer::createPipelineStateObject() {
    D3DCompileFromFile(L"Source/Engine/Shaders/vertex.hlsl", nullptr, nullptr, "VSMain", "vs_5_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &m_vertexShader, &m_error);
    D3DCompileFromFile(L"Source/Engine/Shaders/pixel.hlsl", nullptr, nullptr, "PSMain", "ps_5_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &m_pixelShader, &m_error);
    
    D3D12_INPUT_ELEMENT_DESC inputElementDescs[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(Triangle, position), D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offsetof(Triangle, color), D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
    };

    D3D12_RASTERIZER_DESC rasterizerDesc = {};
    rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
    rasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
    rasterizerDesc.FrontCounterClockwise = FALSE;
    rasterizerDesc.DepthBias = 0;
    rasterizerDesc.DepthBiasClamp = 0.0f;
    rasterizerDesc.SlopeScaledDepthBias = 0.0f;
    rasterizerDesc.DepthClipEnable = TRUE;
    rasterizerDesc.MultisampleEnable = FALSE;
    rasterizerDesc.AntialiasedLineEnable = FALSE;
    rasterizerDesc.ForcedSampleCount = 0;
    rasterizerDesc.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;

    D3D12_BLEND_DESC blendDesc = {};
    blendDesc.AlphaToCoverageEnable = FALSE;
    blendDesc.IndependentBlendEnable = FALSE;
    blendDesc.RenderTarget[0].BlendEnable = FALSE;
    blendDesc.RenderTarget[0].LogicOpEnable = FALSE;
    blendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_ONE;
    blendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_ZERO;
    blendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
    blendDesc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
    blendDesc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
    blendDesc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
    blendDesc.RenderTarget[0].LogicOp = D3D12_LOGIC_OP_NOOP;
    blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

    D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineStateObjectDesc = {};
    pipelineStateObjectDesc.InputLayout = { inputElementDescs, _countof(inputElementDescs) };
    pipelineStateObjectDesc.pRootSignature = m_rootSignature.Get();
    pipelineStateObjectDesc.VS = { m_vertexShader->GetBufferPointer(), m_vertexShader->GetBufferSize() };
    pipelineStateObjectDesc.PS = { m_pixelShader->GetBufferPointer(), m_pixelShader->GetBufferSize() };
    pipelineStateObjectDesc.RasterizerState = rasterizerDesc;
    pipelineStateObjectDesc.BlendState = blendDesc;
    pipelineStateObjectDesc.DepthStencilState.DepthEnable = FALSE;
    pipelineStateObjectDesc.DepthStencilState.StencilEnable = FALSE;
    pipelineStateObjectDesc.SampleMask = UINT_MAX;
    pipelineStateObjectDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    pipelineStateObjectDesc.NumRenderTargets = 1;
    pipelineStateObjectDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
    pipelineStateObjectDesc.SampleDesc.Count = 1;

    if (FAILED(m_device->CreateGraphicsPipelineState(&pipelineStateObjectDesc, IID_PPV_ARGS(&m_pipelineState)))) {
        std::cerr << "Failed to Create Pipeline State Object" << "\n";
        return false;
    }

    std::cout << "Pipeline State Object Created Successfully" << "\n";
    return true;
}
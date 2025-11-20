#include "common.hpp"
#include "Engine/engine.hpp"
#include <d3d12sdklayers.h>

// Have to pass arguments for SDL to use in window creation
int main(int argc, char* argv[]) {
    // Enable debug layers for GPU side debugging
    Microsoft::WRL::ComPtr<ID3D12Debug> debugController;
    if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
        debugController->EnableDebugLayer();
        Microsoft::WRL::ComPtr<ID3D12Debug1> debugController1;
        if (SUCCEEDED(debugController.As(&debugController1))) {
            debugController1->SetEnableGPUBasedValidation(true);
        } else {
            std::cout << "Failed to Enable GPU Based Validation" << "\n";
            return -1;
        }
    } else {
        std::cout << "Failed to Enable Debug Layer" << "\n";
        return -1;
    }

    Engine engine;
    if (!engine.init()) { 
        std::cout << "Failed to Initialise Engine" << "\n";
        return -1; 
    }

    engine.update();

    if (!engine.cleanup()) { 
        std::cout << "Failed to Cleanup Engine" << "\n";
        return -1; 
    }
    
    return 0;
}

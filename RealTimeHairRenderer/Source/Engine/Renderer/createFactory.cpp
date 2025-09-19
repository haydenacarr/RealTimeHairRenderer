#include "renderer.hpp"

// A Factory is an interface for creating Swap Chains and enumerating GPU's
bool Renderer::createFactory() {
	if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&m_factory)))) {
		std::cerr << "Failed to Create Factory" << "\n";
		return false;
	}

	std::cout << "Factory Created Successfully" << "\n";
	return true;
}
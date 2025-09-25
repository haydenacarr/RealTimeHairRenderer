#include "renderer.hpp"

Renderer::~Renderer() {
	m_signature->Release();
	m_error->Release();
}
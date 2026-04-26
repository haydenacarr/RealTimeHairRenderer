#include "renderer.hpp"

HairData Renderer::loadHair(const std::string& filename) {
    // Since the file is binary have to set ifstream setitng
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open hair file" << std::endl;
        return {};
    }

    // According ti data layout in file here: https://www.cemyuksel.com/research/hairmodels/
    struct Header {
        char pad[4];
        uint32_t numStrands;
        uint32_t numPoints;
        uint32_t flags;
        uint32_t defaultSegments;
        float defaultThickness;
        float defaultTransparency;
        float defaultColour[3];
        char info[88];
    } header;

    file.read(reinterpret_cast<char*>(&header), sizeof(Header));
    std::vector<unsigned short> segments(header.numStrands, (unsigned short)header.defaultSegments);
    if (header.flags & 0x1) {
        file.read(reinterpret_cast<char*>(segments.data()), header.numStrands * sizeof(unsigned short));
    }

    std::vector<DirectX::XMFLOAT3> positions(header.numPoints);
    if (header.flags & 0x2) {
        file.read(reinterpret_cast<char*>(positions.data()), header.numPoints * sizeof(DirectX::XMFLOAT3));
    }

    // Colour
    std::vector<DirectX::XMFLOAT3> colours(header.numPoints, { header.defaultColour[0], header.defaultColour[1], header.defaultColour[2] });
    if (header.flags & 0x10) {
        if (header.flags & 0x4) file.seekg(header.numPoints * sizeof(float), std::ios::cur);
        if (header.flags & 0x8) file.seekg(header.numPoints * sizeof(float), std::ios::cur);
        file.read(reinterpret_cast<char*>(colours.data()), header.numPoints * sizeof(DirectX::XMFLOAT3));
    }

    // Build Vertex & Index Buffers
    HairData data;
    for (uint32_t i = 0; i < header.numPoints; i++) {
        HairVertex v;
        v.position = positions[i];
        v.colour.x = colours[i].x;
        v.colour.y = colours[i].y;
        v.colour.z = colours[i].z;
        v.colour.w = 1.0f;
        v.tangent = { 0.0f, 0.0f, 0.0f };
        data.vertices.push_back(v);
    }

    uint32_t pointOffset = 0;
    for (uint32_t s = 0; s < header.numStrands; s++) {
        uint32_t numSegments = segments[s];

        for (uint32_t seg = 0; seg < numSegments; seg++) {
            uint32_t segStart = pointOffset + seg;
            uint32_t segEnd = pointOffset + seg + 1;

            // Calculate Tangent
            DirectX::XMVECTOR a = DirectX::XMLoadFloat3(&data.vertices[segStart].position);
            DirectX::XMVECTOR b = DirectX::XMLoadFloat3(&data.vertices[segEnd].position);
            DirectX::XMVECTOR T = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(a, b));

            // Store the tangent in the vertex
            DirectX::XMStoreFloat3(&data.vertices[segStart].tangent, T);

            // If the file finishes it still makes a line by using previous segment
            if (seg == numSegments - 1) {
                DirectX::XMStoreFloat3(&data.vertices[segEnd].tangent, T);
            }

            data.indices.push_back(segStart);
            data.indices.push_back(segEnd);
        }
        pointOffset += (numSegments + 1);
    }

    return data;
}
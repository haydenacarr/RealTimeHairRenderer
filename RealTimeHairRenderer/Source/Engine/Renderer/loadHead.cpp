#define TINYOBJLOADER_IMPLEMENTATION
#include "C:\Dev\RealTimeHairRenderer\RealTimeHairRenderer\Include\tiny_obj_loader.h"
#include "renderer.hpp"

std::vector<HeadVertex> Renderer::loadHead(std::string path) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn;
    std::string err;
    std::vector<HeadVertex> vertices;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str())) {
        std::cout << "Failed to load Hair file from path" << "\n";
        return vertices;
    }

    for(size_t i = 0; i < shapes.size(); i++) {
        for (size_t j = 0; j < shapes[i].mesh.indices.size(); j++) {
            tinyobj::index_t index = shapes[i].mesh.indices[j];
            HeadVertex vertex{};
            vertex.position = {
                attrib.vertices[3 * index.vertex_index + 0],
                attrib.vertices[3 * index.vertex_index + 1],
                attrib.vertices[3 * index.vertex_index + 2]
            };
            if (index.normal_index >= 0) {
                vertex.normal = {
                    attrib.normals[3 * index.normal_index + 0],
                    attrib.normals[3 * index.normal_index + 1],
                    attrib.normals[3 * index.normal_index + 2]
                };
            }
            vertices.push_back(vertex);
        }
    }

    return vertices;
}
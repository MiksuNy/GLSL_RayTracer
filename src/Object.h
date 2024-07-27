#pragma once

#include <vector>
#include <glm.hpp>

#include "Utility.h"

#include "Shader.h"

struct Material
{
public:
    glm::vec4 baseColor;
    glm::vec4 specularColor;
    glm::vec4 emissionColor;
    float roughness;
    float emissionStrength;
    float ior;
    float refractionAmount;
    float specularChance;
private:
    float pad[3];
};

struct Sphere
{
public:
    glm::vec3 position;
    float radius;

    Sphere(struct Program& program, const char* name, glm::vec3 pos, float rad, struct Material& material);
};

struct Triangle
{
public:
    glm::vec4 p1, p2, p3;
    Material material;

    Triangle();
    Triangle(struct Program& program, const char* name, glm::vec3 _p1, glm::vec3 _p2, glm::vec3 _p3, struct Material& material);
    glm::vec3 Center();
};

struct Node
{
    float boundsMin[4] = { 1e30f }, boundsMax[4] = { -1e30f };
};

struct Mesh
{
public:
    std::vector<glm::vec4> vertices;
    std::vector<glm::ivec4> indices;
    std::vector<Triangle> tris;
    Material material;

    std::vector<Node> nodes;
    
    Mesh(const char* filePath, Material material);

private:
    void Load(const char* filePath);
    void GenBoundingBox();
    void SplitNode(Node parent);
};
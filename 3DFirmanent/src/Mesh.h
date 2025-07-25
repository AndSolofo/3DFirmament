#pragma once
#include<glm/glm.hpp>
#include<vector>
#include<string>
#include "Shader.h"
#include <glad\glad.h>
#include<glfw3.h>



struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texture;
}; 

struct Texture {
	unsigned int ID;
	std::string type;
	std::string path;
};


class Mesh {
public:
	Mesh(std::vector<Vertex> vertice, std::vector<unsigned int> indice, std::vector<Texture> texture);
	void Draw(Shader& shader);
	void setupMesh();

private:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	unsigned int MeshVAO, MeshVBO, MeshEBO;


};

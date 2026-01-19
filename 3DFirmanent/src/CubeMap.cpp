#include "CubeMap.h"

CubeMap::CubeMap() :m_Faces(6),skyBoxVAO(0),skyBoxVBO(0),m_textureID(0)
{
}

CubeMap::~CubeMap()
{
	if (skyBoxVAO != 0) {
		glDeleteVertexArrays(1, &skyBoxVAO);
	}
	if (skyBoxVBO != 0) {
		glDeleteBuffers(1, &skyBoxVBO);
	}
}

unsigned int CubeMap::loadCubeMap(std::vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	int width, height, nbrChannels;
	for (unsigned int i = 0; i < faces.size();i++) {
		//TODO::make sure the filestream is correct here
		std::ifstream file(faces[i], std::ios::ate | std::ios::binary);
		if (!file.is_open()) {
			std::cerr << "ERROR: Failed to open texture file: " << faces[i] << "\n";
			return -1;
		}

		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nbrChannels, 0);
		if (data) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else {
			std::cerr << "CubeMap failed to load side" << faces[i].c_str() << "\n";
			stbi_image_free(data);
		}
		
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}

void CubeMap::setUp(const char* right, const char* left, const char* top, const char* bottom, const char* front, const char* back)
{
	m_Faces[0] = right;
	m_Faces[1] = left;
	m_Faces[2] = top;
	m_Faces[3] = bottom;
	m_Faces[4] = front;
	m_Faces[5] = back;

	glGenVertexArrays(1, &skyBoxVAO);
	glGenBuffers(1, &skyBoxVBO);
	glBindVertexArray(skyBoxVAO);

	glBindBuffer(GL_ARRAY_BUFFER, skyBoxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);

	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	m_textureID=loadCubeMap(m_Faces);

}

void CubeMap::Draw(Shader& shader)
{
	shader.use();
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_FALSE);
	glBindVertexArray(skyBoxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
}

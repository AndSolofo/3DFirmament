#include "SceneManager.h"

SceneManager::SceneManager() 
{
	m_AllEntities.reserve(MAX_ENTITY);
	m_AllEffects.reserve(MAX_EFFECTS);

}


SceneManager::~SceneManager()
{
	m_AllEntities.clear();
	m_AllEffects.clear();
	m_AllEntities.shrink_to_fit();
	m_AllEffects.shrink_to_fit();
}

void SceneManager::initAllEffects(int width,int height)
{
	unsigned int depthMapFBO;
	glGenFramebuffers(1, &depthMapFBO);

	unsigned int shadowTextureID;
	glGenTextures(1, &shadowTextureID);
	glBindTexture(GL_TEXTURE_2D, shadowTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowTextureID, 0);
}

void SceneManager::addEffect()
{
}

void SceneManager::removeEffect()
{
}

void SceneManager::update()
{
}

void SceneManager::addCamera(Camera& camera)
{
}

void SceneManager::popCamera()
{
}

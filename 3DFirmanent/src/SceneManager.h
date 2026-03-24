#pragma once
#include<vector>
#include<concepts>
#include<glm/glm.hpp>
#include<glad/glad.h>
#include"Shader.h"
#include<Camera.h>
#include<vector>
#include"Entity/Entity.h"
#include "Effects/Effect.h"

#define MAX_EFFECTS 20
#define MAX_ENTITY 300


class SceneManager {
public:
	SceneManager();
	~SceneManager();

	void initAllEffects(int width,int height);
	void addEffect();
	void removeEffect();
	void update();
	void addCamera(Camera& camera);
	void popCamera();

private:
	std::vector<std::unique_ptr<Entity>> m_AllEntities;
	std::vector<std::unique_ptr<Effect>> m_AllEffects;

	
};



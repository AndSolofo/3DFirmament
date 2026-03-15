#pragma once
#include<vector>
#include<concepts>
#include<glm/glm.hpp>
#include<glad/glad.h>
//


class SceneManager {
public:
	SceneManager() = default;
	~SceneManager();


	void initAllEffects(int width,int height);


private:
	//std::array<Entity,N> allEffects;
};



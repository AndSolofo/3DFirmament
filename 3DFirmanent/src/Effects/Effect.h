#pragma once

class Effect {
	virtual void update()=0;
	virtual void linkShader()=0;
	virtual void loadEffect()=0;
	virtual void Draw()=0;

};

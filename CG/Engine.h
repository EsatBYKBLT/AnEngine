#pragma once
class Engine
{
	float currentFrame, lastFrame, deltaTime;

	unsigned int renderMode;
public:
	void t(double tt) {
		float currentFrame = static_cast<float>(tt);
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
	}
	float time() {
		return deltaTime;
	}


};


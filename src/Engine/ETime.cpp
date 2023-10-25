#include "ETime.h"

namespace MyEngine {
	double ETime::previousFrameTime = 0.0;
	double ETime::currentFrameTime = 0.0;

	double ETime::fpsUpdateTime = 0.0;
	int ETime::frameCount = 0;
	double ETime::fps = 0.0;

	int ETime::getFPS() {
		return static_cast<int>(fps);
	}

	double ETime::getDeltaTime() {
		return currentFrameTime - previousFrameTime;
	}

	double ETime::getElapsedTime() {
		return glfwGetTime();
	}

	void ETime::updateFrameTime() {
		previousFrameTime = currentFrameTime;
		currentFrameTime = getElapsedTime();

		// Calculating FPS
		frameCount++;
		if (currentFrameTime - fpsUpdateTime >= 1.0) {
			fps = static_cast<double>(frameCount);
			frameCount = 0;
			fpsUpdateTime = currentFrameTime;
		}
	}
}
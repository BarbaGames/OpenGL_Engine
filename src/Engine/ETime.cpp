#include "ETime.h"

namespace MyEngine {
	double ETime::previousFrameTime = 0.0;
	double ETime::currentFrameTime = 0.0;

	double ETime::getDeltaTime() {
		return currentFrameTime - previousFrameTime;
	}

	double ETime::getElapsedTime() {
		return glfwGetTime();
	}

	void ETime::updateFrameTime() {
		previousFrameTime = currentFrameTime;
		currentFrameTime = getElapsedTime();
	}
}
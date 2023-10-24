#pragma once

#include "Engine.h"

namespace MyEngine {

	class DLLExport ETime {
	private:
		static double previousFrameTime;
		static double currentFrameTime;
	public:
		static double getDeltaTime();
		static double getElapsedTime();

		static void updateFrameTime();
	};

}
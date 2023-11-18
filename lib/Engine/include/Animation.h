#pragma once

#include "Shape.h"
#include "Frame.h"

#include <vector>

namespace MyEngine {

	class DLLExport Animation : public Shape {
	private:
		vector<Frame> frames;
		int currentFrameIndex;

		double durationInSecs;
		double elapsedTime;

		bool mirrorX;
		bool mirrorY;

		void setVertex();
	public:
		Animation(Vector3 position, Vector3 scale, Color color);
		virtual ~Animation() override;

		void update();

		void addFrame(unsigned int textureID, float offsetX, float offsetY, float width, float height);

		void setSpriteSheet(unsigned int spriteSheetID, int amountColumns, int amountRows, double durationInSecs);
		void setDurationInSecs(double durationInSecs);
		void setCurrentFrame(int frame);
		void setMirrorX(bool mirrorX);
		void setMirrorY(bool mirrorY);

		void draw();
	};

}
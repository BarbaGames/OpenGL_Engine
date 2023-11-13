#pragma once

#include "Shape.h"

namespace MyEngine {

	class DLLExport Animation : public Shape {
	private:
		unsigned int spriteSheetID;
		int currentFrame;
		int amountFrames;

		float frameWidth;
		float frameHeight;

		double durationInSecs;
		double elapsedTime;

		int mirrorX;
		int mirrorY;

		void setVertex();
	public:
		Animation(Vector3 position, Vector3 scale, Color color);
		virtual ~Animation() override;

		void update();

		void setSpriteSheet(unsigned int spriteSheetID, int amountColumns, int amountRows, double durationInSecs);
		void setFrame(int frame);
		void setMirrorX(bool mirrorX);
		void setMirrorY(bool mirrorY);

		void draw();
	};

}
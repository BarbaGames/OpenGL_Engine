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

		void setVertex();
	public:
		Animation(Vector3 position, Vector3 scale, Color color);
		virtual ~Animation() override;

		void setSpriteSheet(unsigned int spriteSheetID, int amountColumns, int amountRows);
		void setFrame(int frame);

		void draw();
	};

}
#pragma once

#include "Shape.h"

namespace MyEngine {

	class DLLExport Sprite : public Shape {
	private:
		unsigned int textureID;
		int mirrorX;
		int mirrorY;
		void setVertex();
	public:
		Sprite(Vector3 position, Vector3 scale, Color color);
		virtual ~Sprite() override;

		void setImage(unsigned int textureID);
		void setMirrorX(bool mirrorX);
		void setMirrorY(bool mirrorY);

		void draw() override;
	};

}
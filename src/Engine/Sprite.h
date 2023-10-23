#pragma once

#include "Shape.h"

namespace MyEngine {

	class DLLExport Sprite : public Shape {
	private:
		unsigned int textureID;
		void setVertex();
	public:
		Sprite(Vector3 position, Vector3 scale, Color color);
		virtual ~Sprite() override;

		void setImage(unsigned int textureID);

		void draw() override;
	};

}
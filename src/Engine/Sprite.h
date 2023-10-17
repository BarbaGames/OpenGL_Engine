#pragma once

#include "Shape.h"

namespace MyEngine {

	class DLLExport Sprite : public Shape {
	private:
		unsigned int textureID;
		void setVertex();
	public:
		Sprite(string path, Vector3 position, Vector3 scale, Color color);
		~Sprite() override;

		void draw() override;
	};

}
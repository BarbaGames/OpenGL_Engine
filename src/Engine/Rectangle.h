#pragma once

#include "Shape.h"

namespace MyEngine {

	class DLLExport Rectangle : public Shape {
	private:
		void setVertex();
	public:
		Rectangle(Vector3 position, Vector3 scale, Color color);
		Rectangle(Transform transform);
		virtual ~Rectangle() override;


		void draw() override;
	};

}
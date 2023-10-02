#pragma once

#include "Entity.h"
#include <vector>

namespace MyEngine {

	class DLLExport Shape : public Entity {
	protected:
		vector<Vector3> vertex;
		
		void alignVertex();
	public:
		Shape(Vector3 position, Vector3 scale, Color color);
		Shape(Transform transform);
		virtual ~Shape() override;

		virtual void draw() = 0;
	};

}
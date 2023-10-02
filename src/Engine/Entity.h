#pragma once

#include "Transform.h"

namespace MyEngine {

	class DLLExport Entity {
	protected:
		Transform transform;

	public:
		Entity(Transform transform);
		virtual ~Entity();

		Transform getTransform();

		void setTransform(Transform transform);
		void setPosition(Vector3 position);
		void setScale(Vector3 scale);
		void setRotation(Quaternion rotation);
		void setColor(Color color);

		// --

		void move(Vector3 position);
		void rotate(Quaternion rotation);
	};

}
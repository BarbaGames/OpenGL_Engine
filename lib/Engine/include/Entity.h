#pragma once

#include "Transform.h"

namespace MyEngine {

	class DLLExport Entity {
	protected:
		Transform transform;

	public:
		Entity(Transform transform);
		virtual ~Entity();
		
		Transform getTransform() const;

		Vector3 getPosition() const;
		Vector3 getScale() const;
		Vector3 getRotationEuler() const;
		
		Quaternion getRotationQuat() const;

		Vector3 upward() const;
		Vector3 forward() const;
		Vector3 right() const;

		void updateTransform();
		
		void setTransform(Transform transform);
		void setPosition(Vector3 position);
		void setScale(Vector3 scale);
		void setRotationQuat(Quaternion rotation);
		void setRotationEuler(Vector3 rotation);
		void setColor(Color color);

		// --

		void move(Vector3 position);
		void rotate(Quaternion rotation);
	};

}
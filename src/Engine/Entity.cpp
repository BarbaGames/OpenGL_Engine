#include "Entity.h"

#include <iostream>

using namespace std;

namespace MyEngine {

	Entity::Entity(Transform transform) {
		this->transform = transform;
	}

	Entity::~Entity() {
	}

	Transform Entity::getTransform() {
		return transform;
	}

	void Entity::setTransform(Transform transform) {
		this->transform = transform;
	}

	void Entity::setPosition(Vector3 position) {
		transform.position = position;
	}

	void Entity::setScale(Vector3 scale) {
		transform.scale = scale;
	}

	void Entity::setRotation(Quaternion rotation) {
		transform.rotation = rotation;
	}

	void Entity::setColor(Color color) {
		transform.color = color;
	}

	void Entity::move(Vector3 position) {
		transform.position.x += position.x;
		transform.position.y += position.y;
		transform.position.z += position.z;
	}

	void Entity::rotate(Quaternion rotation) {
		transform.rotation.x += rotation.x;
		transform.rotation.y += rotation.y;
		transform.rotation.z += rotation.z;
	}
}
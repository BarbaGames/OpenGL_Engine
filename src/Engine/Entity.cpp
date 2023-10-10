#include "Entity.h"

#include <iostream>
#include "Maths.h"
using namespace std;

namespace MyEngine {

	Entity::Entity(Transform transform) {
		this->transform = transform;
	}

	Entity::~Entity() {
		if(textureLoaded) {
			delete texture;
		}
	}

	void Entity::LoadTexture(std::string path) {
		if(!texture) {
			texture = new Texture();
		}
		if(texture) {
			textureLoaded = texture->LoadTexture(path);
		}
	}

	Transform Entity::getTransform() const {
		return transform;
	}

	Vector3 Entity::getPosition() const	{
		return transform.position;
	}

	Vector3 Entity::getScale() const {
		return transform.scale;
	}

	Vector3 Entity::getRotationEuler() const {
		return transform.rotation;
	}

	Quaternion Entity::getRotationQuat() const {
		return transform.rotationQuat;
	}

	Vector3 Entity::upward() const {
		return transform.upward;
	}

	Vector3 Entity::forward() const {
		return transform.forward;
	}

	Vector3 Entity::right() const {
		return transform.right;
	}

	void Entity::updateTransform() {
		transform.rotationQuat = Maths::Euler(transform.rotation);
		transform.forward = Maths::Quat2Vec3(transform.rotationQuat, Vector3(0, 0, 1));
		transform.upward = Maths::Quat2Vec3(transform.rotationQuat, Vector3(0, 1, 0));
		transform.right = Maths::Quat2Vec3(transform.rotationQuat, Vector3(1, 0, 0));
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

	void Entity::setRotationQuat(Quaternion rotation) {
		transform.rotationQuat = rotation;
	}

	void Entity::setRotationEuler(Vector3 rotation)	{
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
		transform.rotationQuat.x += rotation.x;
		transform.rotationQuat.y += rotation.y;
		transform.rotationQuat.z += rotation.z;
	}
}
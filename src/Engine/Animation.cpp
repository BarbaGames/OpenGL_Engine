#include "Animation.h"

#include "AssetLoader.h"
#include "ETime.h"

namespace MyEngine {

	Animation::Animation(Vector3 position, Vector3 scale, Color color) :
		Shape({ position, scale, {0,0,0}, {0, 0, 0, 0}, {1,0,0}, {0,1,0}, {0,0,1}, color }) {
		currentAnimation = "default";
		currentFrameIndex = 0;

		elapsedTime = 0.00;
		durationInSecs = 0.00;

		mirrorX = false;
		mirrorY = false;
		
		setVertex();
	}

	Animation::~Animation() {

	}

	bool Animation::isAnimationValid(string animationID) {
		return animations.find(animationID) != animations.end();
	}

	void Animation::setVertex() {
		transform.color.normalize();
		vertex.push_back({ 1, 1, 0 });
		vertex.push_back({ 1, 0, 0 });
		vertex.push_back({ 0, 0, 0 });
		vertex.push_back({ 0, 1, 0 });
		alignVertex();
	}

	void Animation::update() {
		elapsedTime += ETime::getDeltaTime();

		double normalizedTime = fmod(elapsedTime, durationInSecs);
		int totalFrames = static_cast<int>(animations[currentAnimation].size());

		if (totalFrames < 1)
			return;

		int framesPerSecond = static_cast<int>(totalFrames / durationInSecs);
		int currentFrame = static_cast<int>(normalizedTime * framesPerSecond) % totalFrames;

		if (mirrorX) {
			currentFrameIndex = totalFrames - 1 - currentFrame;
		}
		else {
			currentFrameIndex = currentFrame;
		}
	}

	void Animation::addFrame(unsigned int textureID, float offsetX, float offsetY, float width, float height) {
		Frame frame;
		frame.textureID = textureID;

		frame.uvCoords[0] = { offsetX + width, offsetY + height };
		frame.uvCoords[1] = { offsetX + width, offsetY };
		frame.uvCoords[2] = { offsetX, offsetY };
		frame.uvCoords[3] = { offsetX, offsetY + height };

		animations["default"].push_back(frame);
	}

	void Animation::addFrame(string animationID, unsigned int textureID, float offsetX, float offsetY, float width, float height) {
		Frame frame;
		frame.textureID = textureID;

		frame.uvCoords[0] = { offsetX + width, offsetY + height };
		frame.uvCoords[1] = { offsetX + width, offsetY };
		frame.uvCoords[2] = { offsetX, offsetY };
		frame.uvCoords[3] = { offsetX, offsetY + height };

		animations[animationID].push_back(frame);
	}

	void Animation::setSpriteSheet(unsigned int spriteSheetID, int amountColumns, int amountRows, double durationInSecs) {
		if(isAnimationValid("default"))
			animations["default"].clear();

		float frameWidth = 1.0f / amountColumns;
		float frameHeight = 1.0f / amountRows;
		int amountFrames = amountColumns * amountRows;
		this->durationInSecs = durationInSecs;

		for (int row = 0; row < amountRows; ++row) {
			for (int col = 0; col < amountColumns; ++col) {
				float offsetX = col * frameWidth;
				float offsetY = row * frameHeight;
				addFrame(spriteSheetID, offsetX, offsetY, frameWidth, frameHeight);
			}
		}
	}

	void Animation::setSpriteSheet(string animationID, unsigned int spriteSheetID, int amountColumns, int amountRows, double durationInSecs) {
		if (isAnimationValid(animationID))
			animations[animationID].clear();

		float frameWidth = 1.0f / amountColumns;
		float frameHeight = 1.0f / amountRows;
		int amountFrames = amountColumns * amountRows;
		this->durationInSecs = durationInSecs;

		for (int row = 0; row < amountRows; ++row) {
			for (int col = 0; col < amountColumns; ++col) {
				float offsetX = col * frameWidth;
				float offsetY = row * frameHeight;
				addFrame(animationID, spriteSheetID, offsetX, offsetY, frameWidth, frameHeight);
			}
		}
	}

	void Animation::setDurationInSecs(double durationInSecs) {
		this->durationInSecs = durationInSecs;
	}

	void Animation::setCurrentFrame(int frame) {
		if (frame > 0 && frame < animations[currentAnimation].size()) {
			currentFrameIndex = frame;
		}
		else {
			cout << "Frame out of bounds!\n";
		}
	}

	void Animation::setCurrentAnimation(string animationID) {
		if (!isAnimationValid(animationID)) return;
		if (currentAnimation == animationID) return;
		currentAnimation = animationID;
		currentFrameIndex = 0;

		elapsedTime = 0.00;

		mirrorX = false;
		mirrorY = false;
	}

	void Animation::setMirrorX(bool mirrorX) {
		if (this->mirrorX == mirrorX) return;
		this->mirrorX = mirrorX;
		for (auto& frame : animations[currentAnimation]) {
			for (int i = 0; i < 4; ++i) {
				frame.uvCoords[i].u = 1.0f - frame.uvCoords[i].u;
			}
		}
	}

	void Animation::setMirrorY(bool mirrorY) {
		if (this->mirrorY == mirrorY) return;
		this->mirrorY = mirrorY;
		for (auto& frame : animations[currentAnimation]) {
			for (int i = 0; i < 4; ++i) {
				frame.uvCoords[i].v = 1.0f - frame.uvCoords[i].v;
			}
		}
	}

	string Animation::getCurrentAnimation() {
		return currentAnimation;
	}

	void Animation::draw() {
		if (animations[currentAnimation].size() < 1)
			return;

		Frame& currentFrame = animations[currentAnimation][currentFrameIndex];

		float vertexData[] = {
			vertex[0].x, vertex[0].y, vertex[0].z, transform.color.r, transform.color.g, transform.color.b, currentFrame.uvCoords[0].u, currentFrame.uvCoords[0].v,
			vertex[1].x, vertex[1].y, vertex[1].z, transform.color.r, transform.color.g, transform.color.b, currentFrame.uvCoords[1].u, currentFrame.uvCoords[1].v,
			vertex[2].x, vertex[2].y, vertex[2].z, transform.color.r, transform.color.g, transform.color.b, currentFrame.uvCoords[2].u, currentFrame.uvCoords[2].v,
			vertex[3].x, vertex[3].y, vertex[3].z, transform.color.r, transform.color.g, transform.color.b, currentFrame.uvCoords[3].u, currentFrame.uvCoords[3].v
		};
		unsigned int indices[] = {
			0, 1, 3,  // First Triangle
			1, 2, 3   // Second Triangle
		};
		glm::mat4 modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(transform.position.x, transform.position.y, transform.position.z));

		if (transform.scale.x != 0 || transform.scale.y != 0 || transform.scale.z != 0)
			modelMatrix = glm::scale(modelMatrix, glm::vec3(transform.scale.x, transform.scale.y, 0.0f));

		if (transform.rotationQuat.x != 0 || transform.rotationQuat.y != 0 || transform.rotationQuat.z != 0) {
			modelMatrix = glm::rotate(modelMatrix, glm::radians(transform.rotationQuat.x), glm::vec3(1.0, 0.0f, 0.0f));
			modelMatrix = glm::rotate(modelMatrix, glm::radians(transform.rotationQuat.y), glm::vec3(0.0f, 1.0f, 0.0f));
			modelMatrix = glm::rotate(modelMatrix, glm::radians(transform.rotationQuat.z), glm::vec3(0.0f, 0.0f, 1.0f));
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		Renderer::setModelMatrix(modelMatrix);
		Renderer::drawTexture(vertexData, indices, currentFrame.textureID);

		glDisable(GL_BLEND);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}
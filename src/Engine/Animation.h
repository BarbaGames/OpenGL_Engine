#pragma once

#include "Shape.h"
#include "Frame.h"

#include <vector>
#include <map>

namespace MyEngine {

	class DLLExport Animation : public Shape {
	private:
		map<string, vector<Frame>> animations;
		string currentAnimation;
		int currentFrameIndex;

		double durationInSecs;
		double elapsedTime;

		bool mirrorX;
		bool mirrorY;

		bool isAnimationValid(string animationID);
		void setVertex();
	public:
		Animation(Vector3 position, Vector3 scale, Color color);
		virtual ~Animation() override;

		void update();

		void addFrame(unsigned int textureID, float offsetX, float offsetY, float width, float height);
		void addFrame(string animationID, unsigned int textureID, float offsetX, float offsetY, float width, float height); // Usar esta si se quiere añadir varios indices a la animacion.

		void setSpriteSheet(unsigned int spriteSheetID, int amountColumns, int amountRows, double durationInSecs);
		void setSpriteSheet(string animationID, unsigned int spriteSheetID, int amountColumns, int amountRows, double durationInSecs); // Usar esta si se quiere añadir varios indices a la animacion.

		void setDurationInSecs(double durationInSecs);
		void setCurrentAnimation(string animationID); // Para cambiar entre animaciones guardadas en el diccionario.
		void setCurrentFrame(int frame);
		void setMirrorX(bool mirrorX);
		void setMirrorY(bool mirrorY);

		string getCurrentAnimation();

		void draw();
	};

}
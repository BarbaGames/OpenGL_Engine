#pragma once

#include "Engine.h"

namespace MyEngine {

	struct DLLExport Vector3 {
		float x; // width | pitch
		float y; // height | yaw
		float z; // depth | roll
		
		Vector3 operator*(float scalar) const {
			return {x * scalar, y * scalar, z * scalar};
		}

		Vector3(float iX, float iY, float iZ)
		{
			x = iX;
			y = iY;
			z = iZ;
		}

		Vector3()
		{
			x = 0;
			y = 0;
			z = 0;
		}
	};

	struct DLLExport Quaternion {
		float w;
		float x;
		float y;
		float z;
	};

	struct DLLExport Color {
		float r;
		float g;
		float b;

		void normalize() {
			if (r < 0 || g < 0 || b < 0) {
				r = 0.0f;
				g = 0.0f;
				b = 0.0f;
			}

			if (r > 1.0f || g > 1.0f || b > 1.0f) {
				r = r / 255.0f;
				g = g / 255.0f;
				b = b / 255.0f;
			}
		}
	};

	struct DLLExport Transform {
		Vector3 position;
		Vector3 scale;
		Vector3 rotation;
		
		Quaternion rotationQuat;
		
		Vector3 forward;
		Vector3 upward;
		Vector3 right;
		
		Color color;
	};
	
	struct DLLExport ModelMatrix {
            
		glm::mat4 model;
		glm::mat4 translate;
		glm::mat4 rotationX;
		glm::mat4 rotationY;
		glm::mat4 rotationZ;
		glm::mat4 scale;
	};
}
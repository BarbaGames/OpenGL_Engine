#pragma once

#include "Engine.h"

namespace MyEngine {

	struct DLLExport Vector3 {
		float x; // width | pitch
		float y; // height | yaw
		float z; // depth | roll
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
		Quaternion rotation;
		Color color;
	};
}
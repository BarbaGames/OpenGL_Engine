#pragma once

namespace MyEngine {

	struct UVCoords {
		float u;
		float v;
	};

	struct Frame{
		unsigned int textureID;
		UVCoords uvCoords[4];
	};

}
#pragma once

#include <iostream>
#include "Engine.h"

using namespace std;

namespace MyEngine {

	class DLLExport AssetLoader {
	public:


		static unsigned int loadImage(string path);
		static void unloadImage(unsigned int id);

	};

}
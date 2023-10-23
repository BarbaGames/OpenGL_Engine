#pragma once

#include <iostream>
#include "Engine.h"

using namespace std;

namespace MyEngine {

	class DLLExport AssetLoader {
	private:
		static bool fileExists(const std::string& filePath);

	public:

		static unsigned int loadImage(string path);
		static void unloadImage(unsigned int id);

	};

}
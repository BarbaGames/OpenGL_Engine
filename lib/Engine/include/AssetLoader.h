#pragma once

#include <iostream>
#include <map>
#include "Engine.h"

using namespace std;

namespace MyEngine {

	class DLLExport AssetLoader {
	private:
		static map<string, unsigned int> loadedTextures;
		static bool fileExists(const std::string& filePath);

	public:

		static unsigned int loadImage(string path, string identifier);
		static void unloadImage(unsigned int id);
		static void unloadImage(string identifier);
		static void unloadAllImages();

		static unsigned int getTexture(string identifier);

	};

}
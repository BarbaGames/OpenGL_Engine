#include "AssetLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <fstream>

namespace MyEngine {

    map<string, unsigned int> AssetLoader::loadedTextures;

    bool AssetLoader::fileExists(const std::string& filePath) {
        std::ifstream file(filePath);
        return file.good();
    }

    unsigned int AssetLoader::loadImage(string filePath, string identifier) {
        cout << "Loading texture at " << filePath << " ...\n";
        if (!fileExists(filePath)) {
            cout << "No texture was found at the specified path!\n";
            return 0;
        }

        unsigned int texture = 0;

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        int width, height, nrChannels;
        unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);

        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            loadedTextures[identifier] = texture;
            cout << "The texture (" << texture << ")" << identifier << " was loaded!\n";
        }
        else {
            cout << "Failed to load texture!!\n";
            cout << "Reason: " << stbi_failure_reason() << "\n";
            glDeleteTextures(1, &texture);
            return 0;
        }

        stbi_image_free(data);
        return texture;
    }

    void AssetLoader::unloadImage(unsigned int id) {
        for (std::map<string, unsigned int>::iterator it = loadedTextures.begin(); it != loadedTextures.end(); ++it) {
            if (it->second == id) {
                loadedTextures.erase(it);
                break;
            }
        }

        glDeleteTextures(1, &id);
        cout << "Texture (" << id << ") was unloaded!\n";
    }

    void AssetLoader::unloadImage(string identifier) {
        std::map<string, unsigned int>::iterator it = loadedTextures.find(identifier);
        if (it != loadedTextures.end()) {
            glDeleteTextures(1, &it->second);
            loadedTextures.erase(it);
            cout << "Texture with identifier " << identifier << " was unloaded!\n";
        }
        else {
            cout << "Texture with identifier " << identifier << " not found!\n";
        }
    }

    void AssetLoader::unloadAllImages() {
        for (std::map<string, unsigned int>::iterator it = loadedTextures.begin(); it != loadedTextures.end(); ++it) {
            glDeleteTextures(1, &it->second);
            cout << "Texture with identifier " << it->first << " was unloaded!\n";
        }

        loadedTextures.clear();
    }

    unsigned int AssetLoader::getTexture(string identifier) {
        std::map<string, unsigned int>::iterator it = loadedTextures.find(identifier);
        if (it != loadedTextures.end()) {
            return it->second;
        }
        else {
            cout << "Texture with identifier " << identifier << " not found!\n";
            return 0;
        }
    }
}
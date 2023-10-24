#include "AssetLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <fstream>

namespace MyEngine {

    bool AssetLoader::fileExists(const std::string& filePath) {
        std::ifstream file(filePath);
        return file.good();
    }

    unsigned int AssetLoader::loadImage(string filePath) {
        cout << "Loading image at " << filePath << "\n...\n";
        if (!fileExists(filePath)) {
            cout << "File not found: " << filePath << "\n";
            return 0; // Return 0 to indicate failure
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
            //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            cout << "Texture was loaded!\n";
        }
        else {
            std::cout << "Failed to load texture: " << filePath << std::endl;
            std::cout << "Reason: " << stbi_failure_reason() << std::endl;
            glDeleteTextures(1, &texture);
            return 0;
        }

        stbi_image_free(data);
        return texture;
    }

    void AssetLoader::unloadImage(unsigned int id) {
        glDeleteTextures(1, &id);
        cout << "Texture was unloaded!\n";
    }

}
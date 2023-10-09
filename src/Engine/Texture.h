#pragma once
#include <string>
#include "Engine.h"

namespace MyEngine {
    class DLLExport Texture {
        
    private:
        unsigned int TextureID;
        unsigned char* TextureData;

    public:
        int TextureWidth;
        int TextureHeight;
        int TextureBitDepth;
        int TextureChannels;

        std::string TexturePath;
        bool Transparent;

        Texture();
        ~Texture();

        bool LoadTexture(const std::string filePath);
        void UnloadTexture();

        void StartUsingTexture();
        void StopUsingTexture();
    };
};

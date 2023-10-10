#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace MyEngine
{
    Texture::Texture()
    = default;

    Texture::~Texture() {
        UnloadTexture();
    }

    bool Texture::LoadTexture(const std::string filePath) {
        stbi_set_flip_vertically_on_load(true);
        TextureData = stbi_load(filePath.c_str(), &TextureWidth, &TextureHeight, &TextureChannels, 0);

        if (!TextureData) {
            std::cout << "Cant Load Texture: " << filePath << std::endl;
            return false;
        }

        glGenTextures(1, &TextureID);
        glBindTexture(GL_TEXTURE_2D, TextureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, TextureWidth, TextureHeight, 0, (TextureChannels == 4) ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, TextureData);
        glGenerateMipmap(GL_TEXTURE_2D);
        Transparent = (TextureChannels == 4) ? true : false;

        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(TextureData);
        Renderer::bindTexture(TextureID);
        std::cout << "Texture loaded correctly: " << filePath << std::endl;
        return true;
    }

    void Texture::UnloadTexture() {
        glDeleteTextures(1, & TextureID);
    }

    void Texture::StartUsingTexture() {
        
        if(Transparent){
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }

        glEnable(GL_TEXTURE_2D);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, TextureID);  
    }

    void Texture::StopUsingTexture() {
        
        if (Transparent) {
            glDisable(GL_BLEND);
        }

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
    }
}

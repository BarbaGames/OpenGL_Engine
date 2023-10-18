#include "Texture.h"

namespace MyEngine
{
    Texture::Texture()
    = default;

    Texture::~Texture() {
        UnloadTexture();
    }

    bool Texture::LoadTexture(const std::string filePath) {
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

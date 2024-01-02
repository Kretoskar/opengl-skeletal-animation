#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "Texture.h"
#include "Logger.h"

bool Texture::LoadTexture(std::string textureFilename)
{
    textureName = textureFilename;
    
    stbi_set_flip_vertically_on_load(true);

    unsigned char *textureData =
      stbi_load(textureFilename.c_str(), &texWidth,
      &texHeight, &nChannels, 0);

    if (!textureData)
    {
        LOG_ERROR("Can't load texture %s", textureFilename)
        stbi_image_free(textureData);
        return false;
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

   // glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);

    glGenerateMipmap(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(textureData);
    return true;
}

void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Cleanup()
{
    glDeleteTextures(1, &texture);
}

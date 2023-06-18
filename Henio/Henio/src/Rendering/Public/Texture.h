#pragma once
#include <cstdint>
#include <glad/glad.h>

class Texture
{
public:
    Texture();
    Texture(const char* path, const char* name, bool defaultParams = true);

    void Generate();
    void Load(bool flip = true);

    void SetFilters(GLenum all);
    void SetFilters(GLenum mag, GLenum min);

    void SetWrap(GLenum all);
    void SetWrap(GLenum s, GLenum t);

    void Bind();

    int32_t id;
    uint32_t tex;
    const char* name;

private:
    static int32_t currentId;

    const char* path;
    int32_t width;
    int32_t height;
    int32_t nChannels;
};

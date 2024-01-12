#include "Framebuffer.h"

#include "Logger.h"

bool Framebuffer::Init(unsigned width, unsigned height)
{
    bufferWidth = width;
    bufferHeight = height;
    glGenFramebuffers(1, &buffer);
    glBindFramebuffer(GL_FRAMEBUFFER, buffer);

    // create texture with the same width and height as the window for framebuffer
    glGenTextures(1, &colorTex);
    glBindTexture(GL_TEXTURE_2D, colorTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,  0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    // downscalling GL_Nearest - no filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // edge clamp - clamp to 01
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // bind the texture
    glBindTexture(GL_TEXTURE_2D, 0);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, colorTex, 0);

    // depth buffer
    glGenRenderbuffers(1, &depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return CheckComplete();
}

bool Framebuffer::Resize(unsigned newWidth, unsigned newHeight)
{
    bufferWidth = newWidth;
    bufferHeight = newHeight;
    
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glDeleteTextures(1, &colorTex);
    glDeleteRenderbuffers(1, &depthBuffer);
    glDeleteFramebuffers(1, &buffer);
    
    return Init(newWidth, newHeight);
}

void Framebuffer::Bind()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, buffer);
}

void Framebuffer::Unbind()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void Framebuffer::DrawToScreen()
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, buffer);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    // 
    glBlitFramebuffer(0, 0, bufferWidth, bufferHeight, 0, 0, bufferWidth, bufferHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
}

void Framebuffer::Cleanup()
{
    glDeleteTextures(1, &colorTex);
    glDeleteRenderbuffers(1, &depthBuffer);
    glDeleteFramebuffers(1, &buffer);
}

bool Framebuffer::CheckComplete()
{
    glBindFramebuffer(GL_FRAMEBUFFER, buffer);
    GLenum result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    
    if (result != GL_FRAMEBUFFER_COMPLETE)
    {
        LOG_ERROR("Framebuffer incomplete")
        return false;
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return true;
}

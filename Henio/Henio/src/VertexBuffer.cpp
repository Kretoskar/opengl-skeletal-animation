#include "VertexBuffer.h"

void VertexBuffer::Init()
{
    // VAO - contains VBOs
    glGenVertexArrays(1, &VAO);
    // VBO - memory buffer containing vertex data (pos, normal, color...)
    glGenBuffers(1, &vertexVBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);

    // Vertex attrib pointer - defines where and how shaders can access vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, uv)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void VertexBuffer::UploadData(Mesh vertexData)
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glBufferData(GL_ARRAY_BUFFER, vertexData.vertices.size() * sizeof(Vertex), &vertexData.vertices.at(0), GL_DYNAMIC_DRAW);
    glBindVertexArray(0);
}

void VertexBuffer::Bind()
{
    glBindVertexArray(VAO);
}

void VertexBuffer::Unbind()
{
    glBindVertexArray(0);
}

void VertexBuffer::Draw(GLuint mode, unsigned start, unsigned num)
{
    glDrawArrays(mode, start, num);
}

void VertexBuffer::Cleanup()
{
    glDeleteBuffers(1, &vertexVBO);
    glDeleteVertexArrays(1, &VAO);
}

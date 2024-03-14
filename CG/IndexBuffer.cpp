#include "IndexBuffer.h"
#include "glad/glad.h"

IndexBuffer::IndexBuffer(){
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

IndexBuffer::IndexBuffer(const void* data, unsigned int size):IndexBuffer(){
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer(){
    glDeleteBuffers(1, &ID);
}

void IndexBuffer::SetBufferData(const void* data, unsigned int size){
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void IndexBuffer::Bind() const{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void IndexBuffer::Unbind() const{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

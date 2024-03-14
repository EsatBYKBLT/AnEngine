#include "VertexBuffer.h"
#include "glad/glad.h"

unsigned int VertexBuffer::getSize(int count, const unsigned int& gType){
    
    switch (gType){
    case GL_FLOAT:
        return count * sizeof(GL_FLOAT);
    }
    return 0;
}

VertexBuffer::VertexBuffer(){
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

VertexBuffer::VertexBuffer(const void* data, unsigned int size):VertexBuffer(){
    //glGenBuffers(1, &ID);
    //glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer(){
    glDeleteBuffers(1, &ID);
}

void VertexBuffer::SetBufferData(const void* data, unsigned int size) {
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}


void VertexBuffer::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VertexBuffer::Unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::setLayout(unsigned int* layout, unsigned int size) {

    // calculate stride
    int stride{};
    for (int i = 0; i < size; i += 2)
        stride += getSize(layout[i], layout[i + 1]);


    // set vertex attrib pointers 
    int offset{};
    for (int i = 0, j = 0; i < size; i += 2, j++) {
        glVertexAttribPointer(j, layout[i], GL_FLOAT, GL_FALSE, stride, (void*)offset);
        glEnableVertexAttribArray(j);

        offset += getSize(layout[i], layout[i + 1]);
    }

}


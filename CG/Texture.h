#pragma once

#include <stb_image.h>
#include <glad/glad.h>

#include <iostream>
#include <string>

#include "Image.h"


class Texture
{
    unsigned int ID{};
    int width{};
    int height{};
    int nrChannels{};
    void generateTexture() {
        // load and create a texture 
        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
public:
    Texture(Image& image) {
        generateTexture();

        if (image.data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data);
            glGenerateMipmap(GL_TEXTURE_2D);

            width = image.width;
            height = image.height;
        }
        else {
            std::cout << "Failed to load image texture" << std::endl;
        }

    }
	Texture(std::string path = "res/horse-face.png") {
        generateTexture();

        // load image, create texture and generate mipmaps
        stbi_set_flip_vertically_on_load(true); 
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);

	}

    void loadImage(Image& image) {
        glBindTexture(GL_TEXTURE_2D, ID);
        if (image.data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data);
            glGenerateMipmap(GL_TEXTURE_2D);

            width = image.width;
            height = image.height;
        }
        else {
            std::cout << "Failed to load image texture" << std::endl;
        }
    }

    static void setActiveTexture(unsigned int glTexture) {
        glActiveTexture(glTexture);
    }

    void bind() {
        glBindTexture(GL_TEXTURE_2D, ID);
    }

    int getWidth() { return width; }
    int getHeight() { return height; }
    int getID() { return ID; }

};


// Texture.cpp
// Created by Edward Glöckner 2023-06-29.
// Last modified: 2023-08-08.

//*********************************************************************************
// Headers
//*********************************************************************************
#include "../include/Texture.h"

//*********************************************************************************
// Globals
//*********************************************************************************

std::vector<Texture *> Texture::textures;

//*********************************************************************************
// Public Class Functions
//*********************************************************************************

//
// Texture
// Description:
//      Constructor.
//      Loads the TGA image data from the specified file 'in_filename' and assigns the provided 
//      'in_name' to the texture. 
//      After loading the TGA data, the Texture object is added to the 'textures' vector for easy management.
// Parameters:
//      in_filename <std::string>: The filename of the TGA image to load.
//      in_name     <std::string>: The name to assign to the Texture object.
// Returns:
//      None (void).
//
Texture::Texture(std::string in_filename, std::string in_name) {
    imageData = NULL;
    loadTGA(in_filename);
    name = in_name;

    textures.push_back(this);
}

//
// ~Texture 
// Description:
//      Destructor. 
//      Removes the Texture object from the 'textures' vector to release its ownership. 
//      The TGA image data is also deleted to free up memory.
// Parameters:
//      None (void).
// Returns:
//      None (void).
//
Texture::~Texture() {
    for (std::vector<Texture *>::iterator it = textures.begin(); it != textures.end(); it++) {
        if ((*it) == this) {
            textures.erase(it);
        }
    }

    if (imageData) {
        delete imageData;
    }
}

//*********************************************************************************
// Private Class Functions
//*********************************************************************************

//
// loadTGA 
// Description:
//      Loads the TGA image data from the specified file 'filename'. 
//      Reads the TGA header and validates the image type. 
//      If the image type is supported (TGA type 2 - uncompressed RGB image), the function
//      reads the image dimensions and pixel depth. 
//      It then allocates memory for the image data and reads the pixel data from the file. 
//      The pixel data is rearranged from BGR format to RGB format to match OpenGL's requirements, and
//      finally, an OpenGL texture is created from the image data using the 'createTexture' function.
// Parameters:
//      filename <std::string>: The filename of the TGA image to load.
// Returns:
//      bool: True if the TGA image was successfully loaded and the OpenGL texture was created, false otherwise.
//
bool Texture::loadTGA(std::string filename) {
    TGA_Header TGAheader;

    std::ifstream file(filename.data(), std::ios_base::binary);

    if (!file.is_open()) {
        return false;
    }

    if (!file.read((char*)&TGAheader, sizeof(TGAheader))) {
        return false;
    }

    if (TGAheader.ImageType != 2) { // unsupported type
        return false;
    }

    width = TGAheader.ImageWidth;
    height = TGAheader.ImageHeight;
    bpp = TGAheader.PixelDepth;

    if (width <= 0 || height <= 0 || (bpp != 24 && bpp != 32)) {
        return false;
    }
    
    GLuint type = GL_RGBA;

    if (bpp == 24) {
        type = GL_RGB;
    }

    GLuint bytesPerPixel = bpp / 8;
    GLuint imageSize = width * height * bytesPerPixel;

    imageData = new GLubyte[imageSize];

    if (imageData == NULL) { // out of memory
        return false;
    }

    if (!file.read((char*)imageData, imageSize)) {
        delete imageData;
        return false;
    }
    
    // BGR --> RGB. Swap B and R
    for (GLuint i = 0; i < (int)imageSize; i+=bytesPerPixel) {
        GLuint temp = imageData[i];
        imageData[i] = imageData[i+2];
        imageData[i+1] = temp;
    }

    createTexture(imageData, width, height, type);

    return true;
}

//
// createTexture
// Description:
//      Creates an OpenGL texture from the provided image data. 
//      Generates an OpenGL texture ID, binds the texture, sets the texture parameters, and uploads 
//      the image data to the GPU. 
//      The texture can then be used for rendering in OpenGL.
// Parameters:
//      imageData <unsigned char*>: The pointer to the image data.
//      width <int>:                The width of the image.
//      height <int>:               The height of the image.
//      type <int>:                 The type of texture (GL_RGB or GL_RGBA).
// Returns:
//      <bool>: True if the OpenGL texture was successfully created, false otherwise.
//
bool Texture::createTexture(unsigned char* imageData, int width, int height, int type) {
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, imageData);
    return true;
}


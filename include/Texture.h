// Texture.h
// Created by Edward Glöckner 2023-06-29.
// Last modified: 2023-08-08.

// Texture
// Description:
// This class represents a texture loaded from a TGA (Truevision Graphics Adapter) image file. It allows loading
// and creating OpenGL textures from TGA files. The class provides functions to load the TGA image data from a file,
// create an OpenGL texture from the image data, and manage the texture object's lifetime. Multiple Texture objects
// can be created to represent different textures, and they are stored in the 'textures' vector for easy access and
// management.

//*********************************************************************************
// Header guard
//*********************************************************************************
#ifndef __TEXTURE_H
#define __TEXTURE_H

//*********************************************************************************
// Headers
//*********************************************************************************
#define GL_SILENCE_DEPRECATION

#ifdef WIN32
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
#endif

#if defined(__APPLE__) && defined(__MACH__)
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

//*********************************************************************************
// Globals
//*********************************************************************************
struct TGA_Header {
    GLubyte ID_Length;
    GLubyte ColorMapByte;
    GLubyte ImageType;
    GLubyte ColorMapSpecification[5];
    GLshort xOrigin;
    GLshort yOrigin;
    GLshort ImageWidth;
    GLshort ImageHeight;
    GLubyte PixelDepth;
};

//*********************************************************************************
// Class
//*********************************************************************************
class Texture {
    public:
        // Constructors and destructors
        Texture(std::string in_filename, std::string in_name = "");
        ~Texture();
        
        // Public class members
        unsigned char*  imageData;
        unsigned int    bpp; // bits per pixel
        unsigned int    width;
        unsigned int    height;
        unsigned int    texID;
        std::string     name;

        static std::vector<Texture *> textures;

    private:
        // Private class functions
        bool loadTGA(std::string filename);
        bool createTexture(unsigned char* imageData, int width, int height, int type);
         
};

#endif


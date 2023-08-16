// Light.h
// Created by Edward Glöckner 2023-06-29.
// Last modified: 2023-08-08.

//*********************************************************************************
// Header guard
//*********************************************************************************
#ifndef __LIGHT_H
#define __LIGHT_H

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

#include <vector>

//*********************************************************************************
// Globals
//*********************************************************************************
enum LIGHT_TYPE {
    LIGHT_SPOT,
    LIGHT_POINT,
    LIGHT_DIRECTIONAL
};

//*********************************************************************************
// Class
//*********************************************************************************
class Light {
    public:
        // Constructors and destructors
        Light(LIGHT_TYPE light_type);
        ~Light();
    
        // Public class functions
        static void Initialize(void);
        void Visible(bool value=true);

        void setDiffuse(float r, float g, float b, float a);
        void setAmbient(float r, float g, float b, float a);
        void setSpecular(float r, float g, float b, float a);

        void setLightType(LIGHT_TYPE light_type);

        void setPosition(float x, float y, float z);

        // Set spotlight specific member functions
        void setSpotDirection(float x, float y, float z);
        void setCutOff(float value);
        void setExponent(float value);
        void setAttenuation(float constant, float linear, float quadratic);

        int getLightNum(void);
        void updateLight(void);

        // Public class members
        static int num_lights;
        static std::vector<int> available_lights;
        static std::vector<Light *> lights;

    private:
        // Private class members
        GLfloat position[4]; // <x, y, z, type of light>
        GLfloat diffuse[4];
        GLfloat ambient[4];
        GLfloat specularity[4];
        GLfloat spotDirection[4];

        float cutoff;
        float exponent;

        bool visible;
        int lightType;
        int lightNum;
};

#endif


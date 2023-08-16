// Light.cpp
// Created by Edward Glöckner 2023-06-29.
// Last modified: 2023-08-08.

//*********************************************************************************
// Headers
//*********************************************************************************
#include "../include/Light.h"
#include <OpenGL/OpenGL.h>

//*********************************************************************************
// Globals
//*********************************************************************************

int Light::num_lights = 0;
std::vector<int> Light::available_lights;
std::vector<Light *> Light::lights;

//*********************************************************************************
// Public Class Functions
//*********************************************************************************

//
// Initialize
// Description:
// Initializes the Light object. Recieves the maxmimum number of lights allowed by the OpenGL implementation
// and populates the available lights vector with light indices to create new lights.
// Parameters:
//      None (void).
// Returns:
//      None (void).
//
void Light::Initialize(void) {
    glGetIntegerv(GL_MAX_LIGHTS, &num_lights);

    for (int i = 0; i < num_lights; i++) {
        available_lights.push_back(GL_LIGHT0 + i);
    }
}

//
// Light
// Description:
//      Constructor.
//      Sets the properties of the lights.
// Parameters:
//      light_type <LIGHT_TYPE>: The type of light to create 
//      (can be LIGHT_SPOT, LIGHT_POINT, or LIGHT_DIRECTIONAL).
// Returns:
//      None (void).
//
Light::Light(LIGHT_TYPE light_type) {
    lights.push_back(this); 

    if ((int)available_lights.size() > 0) {
        lightNum = available_lights[0];

        available_lights.erase(available_lights.begin());

        Visible(true);

        setLightType(light_type);
        setPosition(0, 0, 0);
        setSpotDirection(0, -1, 0);
        setCutOff(45);
        setExponent(12);
        setAmbient(0, 0, 0, 1);
        setDiffuse(1, 1, 1, 1);
        setSpecular(1, 1, 1, 1);

        updateLight();
    }
    else {
        lightNum = 0;
        Visible(false);
    }
}

//
// ~Light
// Description:
//      Destructor.
//      Cleans up all the lights from the Light object.
// Parameters:
//      None (void).
// Returns:
//      None (void).
//
Light::~Light() {
    if (lightNum != 0) {
        available_lights.push_back(lightNum);
    }

    for (std::vector<Light *>::iterator it = lights.begin(); it != lights.end(); it++) {
        if ((*it) == this) {
            lights.erase(it);
        }
    }
}

//
// Visible
// Description:
//      Sets the visibility of the Light object.
// Parameters:
//      value <bool>: The visibility status of the light (true for visible, false for invisible).
// Returns:
//      None (void).
//
void Light::Visible(bool value) {
    visible = value;

    if (visible == true) {
        glEnable(lightNum);
    }
    else {
        glDisable(lightNum);
    }
}

//
// setDiffuse
// Description:
//      Sets the diffuse color of the Light object.
//      The diffuse color is the color of the light when it falls on an object. 
// Parameters:
//      r <float>: The red component of the diffuse color (0.0 to 1.0).
//      g <float>: The green component of the diffuse color (0.0 to 1.0).
//      b <float>: The blue component of the diffuse color (0.0 to 1.0).
//      a <float>: The alpha component of the diffuse color (0.0 to 1.0).
// Returns:
//      None (void).
//
void Light::setDiffuse(float r, float g, float b, float a) {
    diffuse[0] = r;
    diffuse[1] = g;
    diffuse[2] = b;
    diffuse[3] = a;

    glLightfv(lightNum, GL_DIFFUSE, diffuse);
}

//
// setAmbient
// Description:
//      This function sets the ambient color of the Light object. 
//      The ambient color is the color of the light when no light falls on an object.
// Parameters:
//      r <float>: The red component of the ambient color (0.0 to 1.0).
//      g <float>: The green component of the ambient color (0.0 to 1.0).
//      b <float>: The blue component of the ambient color (0.0 to 1.0).
//      a <float>: The alpha component of the ambient color (0.0 to 1.0).
// Returns:
//      None (void).
//
void Light::setAmbient(float r, float g, float b, float a) {
    ambient[0] = r;
    ambient[1] = g;
    ambient[2] = b;
    ambient[3] = a;

    glLightfv(lightNum, GL_AMBIENT, ambient);
}

//
// setSpecular
// Description:
//      This function sets the specular color of the Light object. 
//      The specular color is the highlight color of the light when it reflects off a shiny surface.
// Parameters:
//      r <float>: The red component of the specular color (0.0 to 1.0).
//      g <float>: The green component of the specular color (0.0 to 1.0).
//      b <float>: The blue component of the specular color (0.0 to 1.0).
//      a <float>: The alpha component of the specular color (0.0 to 1.0).
// Returns:
//      None (void).
//
void Light::setSpecular(float r, float g, float b, float a) {
    specularity[0] = r;
    specularity[1] = g;
    specularity[2] = b;
    specularity[3] = a;
    
    glLightfv(lightNum, GL_SPECULAR, specularity);
}

//
// setLightType
// Description:
//      This function sets the type of light for the Light object. 
//      The 'light_type' parameter can be LIGHT_SPOT, LIGHT_POINT, or LIGHT_DIRECTIONAL, 
//      representing spotlights, point lights, and directional lights, respectively.
//      Based on the light type, the position and direction properties of the light are adjusted accordingly.
// Parameters:
//      light_type <LIGHT_TYPE>: The type of light to set (LIGHT_SPOT, LIGHT_POINT, or LIGHT_DIRECTIONAL).
// Returns:
//      None (void).
//
void Light::setLightType(LIGHT_TYPE light_type) {
    lightType = light_type;

    if (light_type == LIGHT_SPOT) {
        position[3] = 1.0f;
    }
    else if (light_type == LIGHT_POINT) {
        position[3] = 1.0f;
        setCutOff(100.0f);
    }
    else if (light_type == LIGHT_DIRECTIONAL) {
        position[3] = 0.0f;
    }

    updateLight();
}

//
// setPosition
// Description:
//      This function sets the position of the Light object in 3D space. 
//      The parameters 'x', 'y', and 'z' represent the x, y, and z coordinates of the light position,
//      respectively. For spot and point lights, the 'w' coordinate is set to 1.0, 
//      and for directional lights, the 'w' coordinate is set to 0.0.
// Parameters:
//      x <float>: The x-coordinate of the light position.
//      y <float>: The y-coordinate of the light position.
//      z <float>: The z-coordinate of the light position.
// Returns:
//      None (void).
//
void Light::setPosition(float x, float y, float z) {
    position[0] = x;
    position[1] = y;
    position[2] = z;
    
    glLightfv(lightNum, GL_POSITION, position);
}

//
// setSpotDirection
// Description:
//      This function sets the direction of the Light object for spotlight types. 
//      The parameters 'x', 'y', and 'z' represent the x, y, and z components of the spotlight direction, 
//      respectively. The spotlight direction vector determines the direction in which the spotlight emits light.
// Parameters:
//      x <float>: The x-component of the spotlight direction vector.
//      y <float>: The y-component of the spotlight direction vector.
//      z <float>: The z-component of the spotlight direction vector.
// Returns:
//      None (void).
//
void Light::setSpotDirection(float x, float y, float z) {
    spotDirection[0] = x;
    spotDirection[1] = y;
    spotDirection[2] = z;

    glLightfv(lightNum, GL_SPOT_DIRECTION, spotDirection);

}

//
// setCutOff
// Description:
// This function sets the cutoff angle for the Light object. 
// The cutoff angle is used for spotlight types and determines the spread angle of the light beam.
// Parameters:
//      value <float>: The cutoff angle in degrees.
// Returns:
//      None (void).
//
void Light::setCutOff(float value) {
    cutoff = value;

    glLightf(lightNum, GL_SPOT_CUTOFF, cutoff);
}

//
// setExponent
// Description:
// This function sets the exponent value for the Light object. 
// The exponent is used for spotlight types and affects the intensity of the light within the cutoff angle. 
// Higher exponent values result in a more focused spotlight beam.
// Parameters:
//      value <float>: The exponent value.
// Returns:
//      None (void).
//
void Light::setExponent(float value) {
    exponent = value;

    glLightf(lightNum, GL_SPOT_EXPONENT, exponent);
}

//
// setAttenuation
// Description:
//      This function sets the attenuation properties of the Light object. 
//      Attenuation affects how the light intensity decreases with distance from the light source.
// Parameters:
//      constant <float>: The constant attenuation factor.
//      linear <float>: The linear attenuation factor.
//      quadratic <float>: The quadratic attenuation factor.
// Returns:
//      None (void).
//
void Light::setAttenuation(float constant, float linear, float quadratic) {
    glLightf(lightNum, GL_CONSTANT_ATTENUATION, constant);
    glLightf(lightNum, GL_LINEAR_ATTENUATION, linear);
    glLightf(lightNum, GL_QUADRATIC_ATTENUATION, quadratic);
}

//
// getLightNum
// Description:
//      This function returns the light number assigned to the Light object. 
//      The light number represents the index of the OpenGL light that this Light object corresponds to.
// Parameters:
//      None (void).
// Returns:
//      lightNum <int>: The light number assigned to the Light object.
//
int Light::getLightNum(void) {
    return lightNum;
}

//
// updateLight
// Description:
//      This function updates the OpenGL light properties of the Light object. 
//      It sets the position and spotlight direction based on the current properties of the Light object. 
//      This function should be called after making any changes to the
//      light properties to update the corresponding OpenGL light.
// Parameters:
//      None (void).
// Returns:
//      None (void).
//
void Light::updateLight(void) {
    glLightfv(lightNum, GL_POSITION, position);
    glLightfv(lightNum, GL_SPOT_DIRECTION, spotDirection);
}


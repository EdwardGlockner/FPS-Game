// model.h
// Created by Edward Glöckner 2023-06-29.
// Last modified: 2023-08-09.

//*********************************************************************************
// Header guard
//*********************************************************************************
#ifndef __MODEL_H
#define __MODEL_H

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
#include <sstream>
#include "Texture.h"
#include "Vector3.h"

//*********************************************************************************
// Globals
//*********************************************************************************

// Material properties
struct Material {
    float Ka[4]; // (r,g,b,a)
    float Kd[4];
    float Ks[4];
    float Ke[4];

    float shininess;
    float alpha;
    float illum;

    Texture *ambientMap;
    Texture *diffuseMap;
    Texture *specularMap;
    Texture *emissionMap;
    Texture *shininessMap;
    Texture *transparencyMap;
    Texture *bumpMap;

    std::string name;

    Material() {
        float defaultAmbient[4] = {0.0f, 0.0f, 0.0f, 1.0f};
        float defaultDiffuse[4] = {1.0f, 1.0f, 1.0f, 1.0f};
        float defaultSpecular[4] = {0.0f, 0.0f, 0.0f, 1.0f};
        float defaultEmission[4] = {0.0f, 0.0f, 0.0f, 1.0f};

        std::memcpy(Ka, defaultAmbient, sizeof(float) * 4);
        std::memcpy(Kd, defaultDiffuse, sizeof(float) * 4);
        std::memcpy(Ks, defaultSpecular, sizeof(float) * 4);
        std::memcpy(Ke, defaultEmission, sizeof(float) * 4);

        ambientMap = NULL;
        diffuseMap = NULL;
        specularMap = NULL;
        emissionMap = NULL;
        shininessMap = NULL;
        transparencyMap = NULL;
        bumpMap = NULL;

        shininess = 2.0f;
        alpha = 1.0f;
        illum = 1.0f;
    }
};

// Face data
struct Face {
    Vector3 **vertices;
    int numVertices;

    Vector3 **normals;
    int numNormals;

    Vector3 **UVWs;
    int numUVWs;

    Material *material;

    Vector3 faceCenter;
    Vector3 faceNormal;

    Face() {
        vertices = NULL;
        normals = NULL;
        UVWs = NULL;

        material = NULL;
    }
};

struct GroupObject {
    std::vector<Face *> faces;
    std::string objectName;
    std::string groupName;
};

//*********************************************************************************
// Class
//*********************************************************************************
class Model {
    public:
        // Constructors and destructors
        Model(std::string in_filename = "");
        ~Model();

        // Public class functions
        void drawModel(void);
        void drawObject(bool transparency = false);
        void drawFace(Face &face);

        void deleteObjects(void);
        
        bool loadObject(std::string in_filename);
        void loadMaterials(std::string in_filename);

        float getRadius(void);
        Vector3 getCenter(void);
        std::string getPath(void);

    private:
        // Private class members
        std::vector<GroupObject *> objects;
        std::vector<Vector3 *> vertices;
        std::vector<Vector3 *> normals;
        std::vector<Vector3 *> UVWs;

        std::vector <Material *> materials;

        Vector3 boundingPoints[8];
        float radius;
        Vector3 center;

        bool objectLoaded;

        GLuint displayList;

        std::string filename;
};

#endif


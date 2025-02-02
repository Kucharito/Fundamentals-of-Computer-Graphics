#pragma once
#include "ModelInterface.h"
#include "ShaderProgram.h"
#include "Transformation.h"
#include "Rotation.h"
#include "DynamicRotation.h"
#include "Texture.h"

// Author: Adam Kuchár
// Login: KUC0396

class DrawableObject {
private:
    ModelInterface* model;
    ShaderProgram* shaderProgram;
    Transformation* transformation;
    Texture* texture;

    void applyTransformation(const char* name);
    bool isSkyboxObject;

    int id;
    static int idCounter;

public:
    DrawableObject(ModelInterface* model, ShaderProgram* shaderProgram);
    ~DrawableObject();

    int getID() const;
    void draw();
    void moveTransformation(int fromIndex, int toIndex);
    void applyTexture();
    void setTexture(Texture* texture);

    void setSkybox(bool isSkyboxObject);
    bool isSkybox();

    void addTransformationInterface(TransformationInterface* transformationInterface);
    
    static void resetIDCounter(); 

};

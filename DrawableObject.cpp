#include "DrawableObject.h"

int DrawableObject::idCounter = 1;


DrawableObject::DrawableObject(ModelInterface* model, ShaderProgram* shaderProgram)
{
    this->model = model;
    this->shaderProgram = shaderProgram;
    this->transformation = new Transformation();
    this->isSkyboxObject = false;
    this->id = idCounter++;
}

void DrawableObject::resetIDCounter() {
    idCounter = 1; 
}


DrawableObject::~DrawableObject() {
    delete transformation;
}

int DrawableObject::getID() const
{
    return id;
}

void DrawableObject::draw() {
    applyTransformation("modelMatrix");
    applyTexture();
   
    model->draw();
    shaderProgram->unbindShader();
}

void DrawableObject::moveTransformation(int fromIndex, int toIndex) {
    if (transformation != nullptr) {
        transformation->moveTransformation(fromIndex, toIndex);
    }
}

void DrawableObject::applyTexture()
{
    if (texture != nullptr)
    {
        shaderProgram->updateTexture(texture);
    }
}

void DrawableObject::setTexture(Texture* texture)
{

    this->texture = texture;
}

void DrawableObject::setSkybox(bool isSkyboxObject)
{
    this->isSkyboxObject = isSkyboxObject;

}

bool DrawableObject::isSkybox()
{
    return isSkyboxObject;
}

void DrawableObject::addTransformationInterface(TransformationInterface* transformationInterface) {
    transformation->addTransformation(transformationInterface);
}

void DrawableObject::applyTransformation(const char* name) {
    transformation->applyTransformation(name, *shaderProgram);
}


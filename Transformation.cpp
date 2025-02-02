#include "Transformation.h"

Transformation::Transformation()
{
    modelMatrix = glm::mat4(1.0f);
}

void Transformation::addTransformation(TransformationInterface* transformation) {
    transformations.push_back(transformation); 
}

glm::mat4 Transformation::calculateModelMetrix() {
    modelMatrix = glm::mat4(1.0f);
    for (auto* transformation : transformations) {
        modelMatrix *= transformation->calculateModelMetrix(); 
    }
    return modelMatrix;
}
void Transformation::moveTransformation(int fromIndex, int toIndex) {
    if (fromIndex >= 0 && fromIndex < transformations.size() &&
        toIndex >= 0 && toIndex < transformations.size() &&
        fromIndex != toIndex) {
        auto transformation = transformations[fromIndex];
        transformations.erase(transformations.begin() + fromIndex);
        transformations.insert(transformations.begin() + toIndex, transformation);
    }
}

void Transformation::applyTransformation(const char* name, ShaderProgram& shaderProgram) {
    glm::mat4 modelMatrix = calculateModelMetrix();
    shaderProgram.updateModel(modelMatrix);
}




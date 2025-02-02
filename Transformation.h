#pragma once

// Author: Adam Kuchár
// Login: KUC0396

#include "TransformationInterface.h"
#include "ShaderProgram.h"
#include <vector>

class Transformation : public TransformationInterface {
private:
    std::vector<TransformationInterface*> transformations;
    glm::mat4 modelMatrix;

public:
    Transformation();

    void addTransformation(TransformationInterface* transformation); 
	void moveTransformation(int fromIndex, int toIndex);
    glm::mat4 calculateModelMetrix() override;
    void applyTransformation(const char* name, ShaderProgram& shaderProgram);
};

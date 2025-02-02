#pragma once

// Author: Adam Kuchár
// Login: KUC0396

#include "TransformationInterface.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Rotation : public TransformationInterface {
protected:
    glm::vec3 axis;
    float angle;

    
public:
    Rotation() {};
    Rotation(const glm::vec3& axis, float angle);
    glm::mat4 calculateModelMetrix() override;

};

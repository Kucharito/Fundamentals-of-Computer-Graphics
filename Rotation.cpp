#include "Rotation.h"

Rotation::Rotation(const glm::vec3& axis, float angle)
{
    this->angle = angle;
    this->axis = axis;
}

glm::mat4 Rotation::calculateModelMetrix() {
    return glm::rotate(glm::mat4(1.0f), angle, axis);
}

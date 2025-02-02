#include "Scale.h"
#include <glm/gtc/matrix_transform.hpp>

Scale::Scale(float scale)
{
    this->scale = scale;
}


glm::mat4 Scale::calculateModelMetrix() {
    return glm::scale(glm::mat4(1.0f), glm::vec3(scale));
}

#include "Translation.h"

Translation::Translation(const glm::vec3& translation)
{
    this->translation = translation;
}

glm::mat4 Translation::calculateModelMetrix() {
    return glm::translate(glm::mat4(1.0f), translation);
}

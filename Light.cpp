#include "Light.h"
#include "ShaderProgram.h"

Light::Light() {
    color = glm::vec3(1.0f, 1.0f, 1.0f);
}

void Light::setColor(const glm::vec3& color) {
    this->color = color;
    notifyObservers();
}

const glm::vec3& Light::getColor() const {
    return color;
}

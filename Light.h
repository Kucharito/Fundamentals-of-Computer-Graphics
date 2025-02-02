#pragma once

// Author: Adam Kuchár
// Login: KUC0396

#include <glm/glm.hpp>
#include "Subject.h"

typedef struct {
    float constant;
    float linear;
    float quadratic;
}Attenuation;

class Light : public Subject {
public:
    Light();
    void setColor(const glm::vec3& color);
    const glm::vec3& getColor() const;

protected:
    glm::vec3 color;
};

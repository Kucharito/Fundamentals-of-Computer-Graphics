#pragma once

// Author: Adam Kuchár
// Login: KUC0396

#include "TransformationInterface.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Translation : public TransformationInterface {
private:
    glm::vec3 translation;

public:
    Translation(const glm::vec3& translation);
    glm::mat4 calculateModelMetrix() override;
};

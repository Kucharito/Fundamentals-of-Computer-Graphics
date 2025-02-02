#pragma once

// Author: Adam Kuchár
// Login: KUC0396

#include "TransformationInterface.h"
#include <glm/glm.hpp>

class Scale : public TransformationInterface {
private:
    float scale;

public:
    Scale(float scale);
    glm::mat4 calculateModelMetrix() override;
};

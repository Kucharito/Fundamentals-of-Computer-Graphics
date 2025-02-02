#pragma once

// Author: Adam Kuchár
// Login: KUC0396

#include <glm/glm.hpp>

class TransformationInterface {
public:
    virtual glm::mat4 calculateModelMetrix() = 0;
    virtual ~TransformationInterface() = default;
};

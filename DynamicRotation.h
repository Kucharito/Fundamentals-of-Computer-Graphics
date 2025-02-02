#pragma once

// Author: Adam Kuchár
// Login: KUC0396

#include "Rotation.h"
#include <glm/gtc/matrix_transform.hpp>

class DynamicRotation :public Rotation {
private:
	float angleIncrement;
	float interval;

public:
	DynamicRotation(const glm::vec3& axis, float angle,float angleIncrement);
	glm::mat4 calculateModelMetrix() override;
};
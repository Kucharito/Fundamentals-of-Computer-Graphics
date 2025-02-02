#pragma once

// Author: Adam Kuchár
// Login: KUC0396

#include <glm/glm.hpp>
#include <vector>
#include "TransformationInterface.h"
#include <glm/gtc/matrix_transform.hpp>

class BezierCurve : public TransformationInterface
{
private:
	glm::mat4 A;
	std::vector<glm::vec3> controlPoints;
	float t;
	float delta;

public:
	BezierCurve();
	void addControlPoint(glm::vec3& point);

	glm::mat4 calculateModelMetrix() override;
};


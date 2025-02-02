#include "BezierCurve.h"

BezierCurve::BezierCurve()
{
    A = glm::mat4(
        glm::vec4(-1.0, 3.0, -3.0, 1.0),
        glm::vec4(3.0, -6.0, 3.0, 0.0),
        glm::vec4(-3.0, 3.0, 0.0, 0.0),
        glm::vec4(1.0, 0.0, 0.0, 0.0)
    );
	t = 0.1f;
	delta = 0.01;
}

void BezierCurve::addControlPoint(glm::vec3& point)
{
	controlPoints.push_back(point);
}

glm::mat4 BezierCurve::calculateModelMetrix()
{
	if (controlPoints.size() != 4)
	{
		return glm::mat4(1.0f);
	}
	glm::mat4x3 B = glm::mat4x3(
		controlPoints[0],
		controlPoints[1],
		controlPoints[2],
		controlPoints[3]
	);

	glm::vec4 parameters = glm::vec4(t * t * t, t * t, t, 1.0f);
	glm::vec3 position = parameters * A * glm::transpose(B);

	if (t >= 1.0f || t <= 0.0f) delta *= -1;
	t += delta;

	return glm::translate(glm::mat4(1.0f), position);

}


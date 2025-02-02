#include "DynamicRotation.h"

DynamicRotation::DynamicRotation(const glm::vec3& axis, float angle, float angleIncrement) : Rotation(axis, angle)
{
	this->axis = axis;
	this->angle = angle;
	this->angleIncrement = angleIncrement;
}
glm::mat4 DynamicRotation::calculateModelMetrix()
{
	angle += angleIncrement;
	return glm::rotate(glm::mat4(1.0f), angle, axis);
}

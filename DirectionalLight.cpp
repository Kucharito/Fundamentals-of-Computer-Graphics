#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
{
	this->color = glm::vec3(1.0f);
	this->direction = glm::vec3(0.0f);
}

const glm::vec3& DirectionalLight::getDirection() const
{
	return direction;
}

void DirectionalLight::setDirection(const glm::vec3& direction)
{
	this->direction = direction;
	notifyObservers();
}

void DirectionalLight::notifyObservers()
{
	for (IObserver* observer : observers) {
		observer->update(3);//lightcolor
		observer->update(5);//direction
	}
}

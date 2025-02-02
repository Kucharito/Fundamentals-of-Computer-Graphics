#include "PointLight.h"

PointLight::PointLight()
{
	this->color = glm::vec3(1.0f);
	this->position = glm::vec3(0.0f);
	this->attenuation.constant = 1.0f;
	this->attenuation.linear = 0.3f;
	this->attenuation.quadratic = 0.1f;
}

void PointLight::setAttenuation(float constant, float linear, float quadratic)
{
	attenuation.constant = constant;
	attenuation.linear = linear;
	attenuation.quadratic = quadratic;
	notifyObservers();
}

Attenuation PointLight::getAttenuation() const
{
	return attenuation;
}


void PointLight::setPosition(const glm::vec3& position)
{
	this->position = position;
	notifyObservers();
}


const glm::vec3& PointLight::getPosition() const
{
	 return position;
}

void PointLight::notifyObservers()
{
	for (IObserver* observer : observers) {
		observer->update(2);//position
		observer->update(3);//lightcolor
		observer->update(4);//attenuation
	}
}

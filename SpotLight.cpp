#include "SpotLight.h"
#include "iostream"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

SpotLight::SpotLight()
{
	color = glm::vec3(1.0f);
	position = glm::vec3(0.0f);
	direction = glm::vec3(0.0f);
	cutOff = 0.5f;
	attenuation = { 1.0f, 0.3f, 3.f };
}

void SpotLight::setAttenuation(float constant, float linear, float quadratic)
{
	attenuation.constant = constant;
	attenuation.linear = linear;
	attenuation.quadratic = quadratic;
	notifyObservers();
}

Attenuation SpotLight::getAttenuation() const
{
	return attenuation;
}

const glm::vec3& SpotLight::getPosition() const
{
	return position;
}

void SpotLight::setPosition(const glm::vec3& position)
{
	this->position = position;
	notifyObservers();
}

const glm::vec3& SpotLight::getDirection() const
{
	return direction;
}

void SpotLight::setDirection(const glm::vec3& direction)
{
	this->direction = direction;
	notifyObservers();
}

void SpotLight::setCutOff(float cutOff)
{
	this->cutOff = cutOff;
	notifyObservers();
}

float SpotLight::getCutOff() const
{
	return cutOff;
}

void SpotLight::notifyObservers()
{
	for (IObserver* observer : observers) {
		observer->update(2);//position
		observer->update(3);//lightcolor
		observer->update(4);//attenuation
		observer->update(5);//direction
		observer->update(6);//cutOff
	}
}

void SpotLight::update(int type)
{
	if (type == 7) {
		this->direction = camera->getFront();
		setDirection(direction);
	}
	else if (type == 8)
	{
		this->position = camera->getCameraPosition();
		setPosition(position);
	}
}

void SpotLight::addCamera(Camera* camera)
{
	this->camera = camera;
}

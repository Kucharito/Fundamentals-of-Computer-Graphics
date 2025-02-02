#pragma once

// Author: Adam Kuchár
// Login: KUC0396

#include "Light.h"

class PointLight : public Light {
private:
	glm::vec3 position;
	Attenuation attenuation;

public:
	PointLight();

	void setAttenuation(float constant,float linear,float quadratic);
	Attenuation getAttenuation() const;

	const glm::vec3& getPosition() const;
	void setPosition(const glm::vec3& position);

	void notifyObservers();
};


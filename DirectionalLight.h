#pragma once

// Author: Adam Kuchár
// Login: KUC0396

#include "Light.h"

class DirectionalLight : public Light {
private:
	glm::vec3 direction;

public:
	DirectionalLight();

	const glm::vec3& getDirection() const;
	void setDirection(const glm::vec3& direction);

	void notifyObservers();
};

#pragma once

// Author: Adam Kuchár
// Login: KUC0396

#include "Light.h"
#include "Camera.h"

class SpotLight : public Light, public IObserver {
private:
	glm::vec3 direction;
	float cutOff;
	glm::vec3 position;
	Attenuation attenuation;
	Camera* camera;

public:
	SpotLight();

	void setAttenuation(float constant, float linear, float quadratic);
	Attenuation getAttenuation() const;

	const glm::vec3& getPosition() const;
	void setPosition(const glm::vec3& position);

	const glm::vec3& getDirection() const;
	void setDirection(const glm::vec3& direction);

	void setCutOff(float cutOff);
	float getCutOff() const;

	void notifyObservers();
	void update(int type) override;
	void addCamera(Camera* camera);

};
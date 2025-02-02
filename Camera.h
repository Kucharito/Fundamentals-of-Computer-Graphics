#pragma once

// Author: Adam Kuchár
// Login: KUC0396

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Subject.h"

class ShaderProgram;
class Camera : public Subject {
private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    float alpha;
    float phi;
    float movementSpeed;

public:
    Camera(glm::vec3 startPosition, glm::vec3 front, glm::vec3 startUp);

    void moveForward();
    void moveBackward();
    void moveLeft();
    void moveRight();
    void rotate(float alphaOffset, float phiOffset);
    void resetPosition(glm::vec3 position, glm::vec3 target);
    void notifyObservers() override;
    void setMovementSpeed(float movementSpeed);

    glm::mat4 getCamera();
    glm::mat4 getProjection();
	glm::vec3 getFront();
    glm::vec3 getCameraPosition();
};

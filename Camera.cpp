#include "Camera.h"

Camera::Camera(glm::vec3 startPosition, glm::vec3 front, glm::vec3 startUp)
{
    this->position = startPosition;
    this->front = front;
    this->up = startUp;
	this->movementSpeed = 1.0f;
}

void Camera::moveForward()
{
    position = position + (glm::normalize(front) * movementSpeed);
    notifyObservers();
}

void Camera::moveBackward()
{
    position = position - (glm::normalize(front) * movementSpeed);
    notifyObservers();
}

void Camera::moveLeft()
{
    position = position - (glm::normalize(glm::cross(front, up)) * movementSpeed);
    notifyObservers();
}

void Camera::moveRight()
{
    position = position + (glm::normalize(glm::cross(front, up)) * movementSpeed);
    notifyObservers();
}

void Camera::rotate(float alphaOffset, float phiOffset) {
    alpha += alphaOffset;
    phi += phiOffset;

    if (alpha > 89.0f) alpha = 89.0f;
    if (alpha < -89.0f) alpha = -89.0f;

    front.x = cos(glm::radians(alpha)) * cos(glm::radians(phi));
    front.y = sin(glm::radians(alpha)); 
    front.z = cos(glm::radians(alpha)) * sin(glm::radians(phi));

    front = glm::normalize(front);  

    notifyObservers();
}

glm::mat4 Camera::getCamera()
{
    return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::getProjection() {
    return glm::perspective(45.0f, 800.f / 600.f, 0.1f, 300.f);
}

glm::vec3 Camera::getFront()
{
    return front;
}

void Camera::resetPosition(glm::vec3 position, glm::vec3 target) {
    this->position = position;
    this->front = glm::normalize(target - position);
}

void Camera::notifyObservers() {
    for (IObserver* observer : observers) {
        observer->update(0);
        observer->update(1);
        observer->update(7);
		observer->update(8);
    }
}

glm::vec3 Camera::getCameraPosition() {
    return position;
}

void Camera::setMovementSpeed(float movementSpeed)
{
    this->movementSpeed = movementSpeed;
}

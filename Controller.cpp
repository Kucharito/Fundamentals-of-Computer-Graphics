#include "Controller.h"

Controller::Controller(Camera* camera)
{
    this->camera = camera;
    firstMouse = true;
    this->lastX = lastX;
    this->lastY = lastY;
}

void Controller::processKeyboardInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera->moveForward();
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera->moveBackward();
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera->moveLeft();
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera->moveRight();
}

void Controller::processMouseMovement(float xpos, float ypos) {
    const float sensitivity = 0.2f;
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = (xpos - lastX) * sensitivity;
    float yoffset = (lastY - ypos) * sensitivity;

    lastX = xpos;
    lastY = ypos;

    camera->rotate(yoffset, xoffset);
}

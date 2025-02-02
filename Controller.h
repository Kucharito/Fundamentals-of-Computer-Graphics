#pragma once

// Author: Adam Kuchár
// Login: KUC0396

#include "Camera.h"
#include <GLFW/glfw3.h>

class Controller {
private:
    Camera* camera;
    float lastX;
    float lastY;
    bool firstMouse;

public:
    Controller(Camera* camera);
    void processKeyboardInput(GLFWwindow* window);
    void processMouseMovement(float xpos, float ypos);
};

#pragma once

// Author: Adam Kuchár
// Login: KUC0396

#include "Scene.h"
#include <GLFW/glfw3.h>
#include <vector>
#include "Controller.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "DirectionalLight.h"

class Application {
private:
    GLFWwindow* window;
    std::vector<Scene*> scenes;
    Controller* controller;
    Camera* camera;
    std::size_t activeSceneIndex;
    PointLight* pointLight;
	SpotLight* spotLight;
	DirectionalLight* directionalLight;
    bool mKeyPressed = false; 


public:
    Application();
    void initialization();
    void run();
    void switchScene(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height); 

    void processClick(float cursorX, float cursorY); 
	void processClickRight(float cursorX, float cursorY);
	void processPick(float cursorX, float cursorY);

    void addBezierPoint(glm::vec3& point);


};

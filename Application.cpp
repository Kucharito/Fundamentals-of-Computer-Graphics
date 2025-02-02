#include "Application.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <iostream>

Application::Application()
{
	activeSceneIndex = 0;
	window = nullptr;
	camera = new Camera(glm::vec3(0.0f, 10.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	controller = new Controller(camera);

	for (int i = 0; i < 8; i++) {
		scenes.push_back(new Scene());
	}
	pointLight = new PointLight();
	spotLight = new SpotLight();
	directionalLight = new DirectionalLight();

}


void Application::initialization()
{
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(1300, 800, "ZPG", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glewExperimental = GL_TRUE;
	glewInit();

	scenes[0]->initScene();
	scenes[1]->initScene2();
	scenes[2]->initScene3();
	scenes[3]->initScene4();
	scenes[4]->initScene5();
	scenes[5]->initScene6();
	scenes[6]->initScene7();
	scenes[7]->initScene8();


	scenes[1]->addObserver(camera);
	spotLight->addCamera(camera);

	scenes[1]->addObserver(directionalLight);
	spotLight->setPosition(glm::vec3(0.0f, 10.0f, 5.0f));
	spotLight->setDirection(glm::vec3(0.0f, -1.0f, 0.0f));
	spotLight->setCutOff(glm::cos(glm::radians(20.0f)));
	spotLight->setColor(glm::vec3(1.0f, 1.f, 1.0f));
	spotLight->setAttenuation(1.0f, 0.09f, 0.032f);   


	directionalLight->setColor(glm::vec3(1.0f, 0.0f, 1.0f));
	directionalLight->setDirection(glm::vec3(10.0f, 0.0f, 0.0f));

	scenes[2]->addObserver(camera);
	scenes[2]->addObserver(pointLight);


	scenes[3]->addObserver(camera);
	scenes[3]->addObserver(pointLight);


	scenes[4]->addObserver(camera);


	scenes[5]->addObserver(camera);
	scenes[5]->addObserver(spotLight);
	camera->addObserver(spotLight);
	spotLight->addCamera(camera);


	scenes[6]->addObserver(camera);
	scenes[6]->addObserver(pointLight);


	scenes[7]->addObserver(camera);
	scenes[7]->addObserver(spotLight);
	camera->addObserver(spotLight);
	spotLight->addCamera(camera);

	pointLight->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	pointLight->setColor(glm::vec3(0.0f, 1.0f, 1.0f));

	glEnable(GL_DEPTH_TEST);
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
		if (app)
			app->switchScene(window, key, scancode, action, mods);
		});
}


void Application::run() {
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		scenes[activeSceneIndex]->draw();

		controller->processKeyboardInput(window);
		controller->processMouseMovement((float)xpos, (float)ypos);

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			processClick(xpos, ypos);
		}
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
			processClickRight(xpos, ypos);
		}
		if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
			if (!mKeyPressed) {
				mKeyPressed = true; 
				processPick(xpos, ypos);
			}
		}
		else {
			mKeyPressed = false;
		}
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}


void Application::processClick(float cursorX, float cursorY) {
	GLint width, height;
	glfwGetFramebufferSize(window, &width, &height);

	GLint x = static_cast<GLint>(cursorX);
	GLint y = height - static_cast<GLint>(cursorY) - 1;

	GLbyte color[4];
	GLfloat depth;
	GLuint index;

	glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
	glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
	glReadPixels(x, y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

	printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth: %f, stencil index: %u\n",
		x, y, color[0], color[1], color[2], color[3], depth, index);

	glm::vec3 screenCoords = glm::vec3(x, y, depth);
	glm::mat4 view = camera->getCamera();
	glm::mat4 projection = camera->getProjection();
	glm::vec4 viewport = glm::vec4(0, 0, width, height);

	glm::vec3 worldCoords = glm::unProject(screenCoords, view, projection, viewport);
	printf("World coordinates: [%f, %f, %f]\n", worldCoords.x, worldCoords.y, worldCoords.z);

	scenes[activeSceneIndex]->addTreeAtPosition(worldCoords);
}

void Application::processClickRight(float cursorX, float cursorY)
{
	GLuint index;

	GLint width, height;
	glfwGetFramebufferSize(window, &width, &height);

	GLint x = static_cast<GLint>(cursorX);
	GLint y = height - static_cast<GLint>(cursorY) - 1;

	glReadPixels(x, y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
	scenes[activeSceneIndex]->addCurveToObject(index);
}

void Application::processPick(float cursorX, float cursorY)
{
	GLfloat depth;
	GLint width, height;
	glfwGetFramebufferSize(window, &width, &height);

	GLint x = static_cast<GLint>(cursorX);
	GLint y = height - static_cast<GLint>(cursorY) - 1;

	glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

	glm::vec3 screenCoords = glm::vec3(x, y, depth);
	glm::mat4 view = camera->getCamera();
	glm::mat4 projection = camera->getProjection();
	glm::vec4 viewport = glm::vec4(0, 0, width, height);

	glm::vec3 worldCoords = glm::unProject(screenCoords, view, projection, viewport);
	printf("World coordinates: [%f, %f, %f]\n", worldCoords.x, worldCoords.y, worldCoords.z);

	addBezierPoint(worldCoords);

}


void Application::switchScene(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS && key == GLFW_KEY_SPACE) {
		activeSceneIndex = (activeSceneIndex + 1) % scenes.size();
		
		switch (activeSceneIndex) {
		case 1:
			camera->setMovementSpeed(0.5f);
			break;
		case 2:
			camera->setMovementSpeed(0.1f);
			break;
		case 3:
			camera->setMovementSpeed(0.1f);
			break;
		case 4:
			camera->setMovementSpeed(0.2f); 
			break;
		case 5:
			camera->setMovementSpeed(0.2f);
			break;
		case 6:
			camera->setMovementSpeed(0.1f);
			break;
		default:
			camera->setMovementSpeed(0.3f); 
			break;
		}

		if (activeSceneIndex == 2) {
			glm::vec3 cameraPosition(-5.0f, 0.0f, 8.0f);
			glm::vec3 targetPosition(-5.0f, 0.0f, 8.0f);
			camera->resetPosition(cameraPosition, targetPosition);
		}

		if (activeSceneIndex == 3) {
			glm::vec3 cameraPosition(-5.0f, 0.0f, 8.0f);
			glm::vec3 targetPosition(-5.0f, 0.0f, 8.0f);
			camera->resetPosition(cameraPosition, targetPosition);
		}
		if (activeSceneIndex == 6) {
			glm::vec3 cameraPosition(-5.0f, 1.0f, 8.0f);
			glm::vec3 targetPosition(-5.0f, 1.0f, 8.0f);
			camera->resetPosition(cameraPosition, targetPosition);
		}
		if (activeSceneIndex == 7) {
			glm::vec3 cameraPosition(-5.0f, 5.0f, 8.0f);
			glm::vec3 targetPosition(-5.0f, 5.0f, 8.0f);
			camera->resetPosition(cameraPosition, targetPosition);
		}
	}
}

void Application::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	float desiredAspect = 16.0f / 9.0f;
	float windowAspect = (float)width / (float)height;

	int viewportWidth, viewportHeight;
	int xOffset = 0, yOffset = 0;

	if (windowAspect > desiredAspect) {
		viewportHeight = height;
		viewportWidth = static_cast<int>(height * desiredAspect);
		xOffset = (width - viewportWidth) / 2;
	}
	else {
		viewportWidth = width;
		viewportHeight = static_cast<int>(width / desiredAspect);
		yOffset = (height - viewportHeight) / 2;
	}

	glViewport(xOffset, yOffset, viewportWidth, viewportHeight);
}


void Application::addBezierPoint(glm::vec3& point) {
	scenes[activeSceneIndex]->addPoint(point);
}

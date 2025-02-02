#pragma once

// Author: Adam Kuchár
// Login: KUC0396

#include "ShaderProgram.h"
#include "DrawableObject.h"
#include "tree.h"
#include "bushes.h"
#include "Scale.h"
#include "Translation.h"
#include "Rotation.h"
#include <vector>
#include <random>
#include <ctime>
#include "Camera.h"
#include "suzi_flat.h"
#include "Light.h"
#include "sphere.h"
#include "ShaderLoader.h"
#include "plain.h"
#define MAX_LIGHTS 4
#include "DynamicRotation.h"
#include "Material.h"
#include "Texture.h"
#include "TextureModel.h"
#include "plainTexture.h"
#include "skycube.h"
#include "ModelSkycube.h"
#include "ModelInterface.h"
#include "ModelObject.h"
#include "Camera.h"
#include "Transformation.h"
#include "BezierCurve.h"

class Scene {
private:
    std::vector<DrawableObject*> objects;
    //std::vector<DrawableObject*> rotatingObjects; 
    std::vector<ShaderProgram*> shaderPrograms; 
    Light* light;
    bool rotationActive;
	BezierCurve* bezierCurve;

public:
    Scene();
    ~Scene();
    void initScene();
    void initScene2();
    void initScene3();
    void initScene4();
    void initScene5();
	void initScene6();
    void initScene7();
	void initScene8();
    void draw();
    void addDrawableObject(DrawableObject* object);
    void addObserver(Camera* camera);
    void addObserver(Light* light);
    void addTreeAtPosition(const glm::vec3& position);
	void addPoint(glm::vec3& point);
	void addCurveToObject(int index);


};

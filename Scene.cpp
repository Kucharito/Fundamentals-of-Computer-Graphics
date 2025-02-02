#include "Scene.h"


Scene::Scene() {
	bezierCurve = new BezierCurve();
}

Scene::~Scene() {
	for (ShaderProgram* shader : shaderPrograms) {
		delete shader;
	}
	for (DrawableObject* object : objects) {
		delete object;
	}
}

void Scene::initScene() {
	DrawableObject::resetIDCounter(); 
	ShaderProgram* shaderProgram = new ShaderProgram("vertex_shader_triangle.glsl", "fragment_shader_triangle.glsl");
	shaderPrograms.push_back(shaderProgram);

	float points[] = {

		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
	};

	float points2[] = {

		-0.75f, -0.5f, 1.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 1.0f,
	};
	Model* modelTriangle = new Model(points, sizeof(points), 3);
	DrawableObject* triangle = new DrawableObject(modelTriangle, shaderProgram);
	triangle->addTransformationInterface(new Translation(glm::vec3(0.0f, 0.0f, 0.0f)));

	Model* modelTriangle2 = new  Model(points2, sizeof(points2), 3);
	DrawableObject* triangle2 = new DrawableObject(modelTriangle2, shaderProgram);
	triangle2->addTransformationInterface(new Translation(glm::vec3(0.0f, 0.0f, 0.0f)));


	addDrawableObject(triangle);
	addDrawableObject(triangle2);
}
void Scene::initScene2() {
	DrawableObject::resetIDCounter(); 
	ShaderProgram* shaderProgram2 = new ShaderProgram("vertex_shader_directional.glsl", "fragment_shader_directional.glsl");
	shaderProgram2->setShader();
	shaderPrograms.push_back(shaderProgram2);

	TransformationInterface* transformationInterface;
	int rotatedTrees = 30;
	srand((time(0)));
	int i = rand() % 20 + 50;
	for (int j = 0; j < i; j++) {
		float randomX = (rand() % 600 - 300) / 10.0f;
		float randomY = 0.0f;
		float randomZ = (rand() % 600 - 300) / 10.0f;
		float randomScale = (rand() % 60 + 5) / 100.0f;

		Model* modelTree = new Model(tree, sizeof(tree), 92814);
		DrawableObject* drawableObject = new DrawableObject(modelTree, shaderProgram2);
		
		drawableObject->addTransformationInterface(new Translation(glm::vec3(randomX, randomY, randomZ)));

		if (j < rotatedTrees) {
		
			drawableObject->addTransformationInterface(new DynamicRotation(glm::vec3(0.f, 1.f, 0.f), 0, 0.5f));
		}
		else {
			drawableObject->addTransformationInterface(new Rotation(glm::vec3(0.f,1.f,0.f), 0.5f));

		}
		drawableObject->addTransformationInterface(new Scale(randomScale));

		//drawableObject->moveTransformation(2, 0);
		//drawableObject->moveTransformation(0, 1);
		addDrawableObject(drawableObject);
	}

	int k = rand() % 20 + 30;
	for (int j = 0; j < k; j++) {
		float randomX = (rand() % 600 - 300) / 10.0f;
		float randomY = 0.0f;
		float randomZ = (rand() % 600 - 300) / 10.0f;
		float randomScale = (rand() % 100 + 5) / 100.0f;

		Model* bushModel = new Model(bushes, sizeof(bushes), 8730);
		DrawableObject* drawableObject = new DrawableObject(bushModel, shaderProgram2);

		drawableObject->addTransformationInterface(new Translation(glm::vec3(randomX, randomY, randomZ)));
		drawableObject->addTransformationInterface(new Rotation(glm::vec3(0.f, 1.f, 0.f), 0.5f));
		drawableObject->addTransformationInterface(new Scale(randomScale));

		addDrawableObject(drawableObject);
	}

	Model* plainModel = new Model(plain, sizeof(plain), 6);
	DrawableObject* plainDrawable = new DrawableObject(plainModel, shaderProgram2);

	plainDrawable->addTransformationInterface(new Translation(glm::vec3(0.0f, 0.0f, 0.0f)));
	plainDrawable->addTransformationInterface(new Scale(37.0f));
	addDrawableObject(plainDrawable);
}


void Scene::initScene3() {
	DrawableObject::resetIDCounter();
	ShaderProgram* shaderProgram3 = new ShaderProgram("vertex_shader_phong.glsl", "fragment_shader_phong.glsl");

	shaderProgram3->setShader();
	shaderPrograms.push_back(shaderProgram3);

	std::vector<glm::vec3> spherePositions = {
		glm::vec3(-2.0f, 0.0f, 0.0f),
		glm::vec3(2.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 2.0f, 0.0f),
		glm::vec3(0.0f, -2.0f, 0.0f)
	};

	for (const auto& pos : spherePositions) {
		Model* modelSphere = new Model(sphere, sizeof(sphere), 2880);
		DrawableObject* sphereObject = new DrawableObject(modelSphere, shaderProgram3);

		sphereObject->addTransformationInterface(new Translation(pos));
		sphereObject->addTransformationInterface(new Scale(1.0f));

		addDrawableObject(sphereObject);
	}
}
void Scene::initScene7() {
	DrawableObject::resetIDCounter(); 

	ShaderProgram* shaderProgram3 = new ShaderProgram("vertex_shader_phong_lights.glsl", "fragment_shader_phong_lights.glsl");

	shaderProgram3->setShader();
	shaderPrograms.push_back(shaderProgram3);

	glm::vec4 lightPositions[MAX_LIGHTS] = {
		glm::vec4(0.0, 0.0, 0.0, 1.0),
		glm::vec4(2.0, 0.0, 5.0, 1.0),
		glm::vec4(10.0, 10.0, -10.0, 1.0),
		glm::vec4(-10.0, 0.0, 10.0, 1.0)
	};

	glm::vec4 lightDiffuse[MAX_LIGHTS] = {
		glm::vec4(1.0, 1.0, 1.0, 1.0),
		glm::vec4(1.0, 1.0, 1.0, 1.0),
		glm::vec4(1.0, 1.0, 1.0, 1.0),
		glm::vec4(1.0, 1.0, 1.0, 1.0)
	};

	glm::vec4 lightSpecular[MAX_LIGHTS] = {
		glm::vec4(1.0, 1.0, 1.0, 1.0),
		glm::vec4(1.0, 1.0, 1.0, 1.0),
		glm::vec4(1.0, 1.0, 1.0, 1.0),
		glm::vec4(1.0, 1.0, 1.0, 1.0)
	};

	int numberOfLights = 2;

	for (int i = 0; i < numberOfLights; i++) {
		shaderProgram3->send("lights[" + std::to_string(i) + "].position", lightPositions[i]);
		shaderProgram3->send("lights[" + std::to_string(i) + "].diffuse", lightDiffuse[i]);
		shaderProgram3->send("lights[" + std::to_string(i) + "].specular", lightSpecular[i]);
	}
	shaderProgram3->send("numberOfLights", numberOfLights);

	std::vector<glm::vec3> spherePositions = {
		glm::vec3(-2.0f, 0.0f, 0.0f),
		glm::vec3(2.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 2.0f, 0.0f),
		glm::vec3(0.0f, -2.0f, 0.0f)
	};

	for (const auto& pos : spherePositions) {
		Model* modelSphere = new Model(sphere, sizeof(sphere), 2880);
		DrawableObject* sphereObject = new DrawableObject(modelSphere, shaderProgram3);

		sphereObject->addTransformationInterface(new Translation(pos));
		sphereObject->addTransformationInterface(new Scale(1.0f));

		addDrawableObject(sphereObject);
	}
}

void Scene::initScene4() {
	DrawableObject::resetIDCounter(); 

	//Blinn
	ShaderProgram* shaderProgram7 = new ShaderProgram("vertex_shader_blinn.glsl", "fragment_shader_blinn.glsl");
	shaderPrograms.push_back(shaderProgram7);

	Model* modelSphere2 = new Model(suziFlat, sizeof(suziFlat), 2904);
	DrawableObject* sphereObject2 = new DrawableObject(modelSphere2, shaderProgram7);

	sphereObject2->addTransformationInterface(new Translation(glm::vec3(15.0f, 0.0f, 0.0f)));
	sphereObject2->addTransformationInterface(new Scale(1.0f));

	addDrawableObject(sphereObject2);


	//Lambert
	ShaderProgram* shaderProgram6 = new ShaderProgram("vertex_shader_lambert.glsl", "fragment_shader_Lambert.glsl");
	shaderPrograms.push_back(shaderProgram6);

	Model* modelMonkey = new Model(suziFlat, sizeof(suziFlat), 2904);
	DrawableObject* monkeyObject = new DrawableObject(modelMonkey, shaderProgram6);

	monkeyObject->addTransformationInterface(new Translation(glm::vec3(10.0f, 0.0f, 0.0f)));
	monkeyObject->addTransformationInterface(new Scale(1.0f));

	addDrawableObject(monkeyObject);

	//Constant a phong
	ShaderProgram* shaderProgram4 = new ShaderProgram("vertex_shader_constant.glsl", "fragment_shader_constant.glsl");

	shaderPrograms.push_back(shaderProgram4);
	Model* modelSphere = new Model(suziFlat, sizeof(suziFlat), 2904);
	DrawableObject* sphereObject = new DrawableObject(modelSphere, shaderProgram4);

	sphereObject->addTransformationInterface(new Translation(glm::vec3(0.0f, 0.0f, 0.0f)));
	sphereObject->addTransformationInterface(new Scale(1.0f));
	addDrawableObject(sphereObject);


	ShaderProgram* shaderProgram5 = new ShaderProgram("vertex_shader_phong.glsl", "fragment_shader_phong.glsl");

	shaderPrograms.push_back(shaderProgram5);
	Model* modelSphere1 = new Model(suziFlat, sizeof(suziFlat), 2904);
	DrawableObject* sphereObject1 = new DrawableObject(modelSphere1, shaderProgram5);

	sphereObject1->addTransformationInterface(new Translation(glm::vec3(5.0f, 0.0f, 0.0f)));
	sphereObject1->addTransformationInterface(new Scale(1.0f));

	addDrawableObject(sphereObject1);
}
void Scene::initScene5() {
	DrawableObject::resetIDCounter();
	ShaderProgram* shaderProgram2 = new ShaderProgram("vertex_shader_les.glsl", "fragment_shader_les.glsl");

	shaderProgram2->setShader();
	shaderPrograms.push_back(shaderProgram2);

	ShaderProgram* shaderProgramPlain = new ShaderProgram("vertex_textures.glsl", "fragment_textures.glsl");
	shaderPrograms.push_back(shaderProgramPlain);

	TransformationInterface* transformationInterface;
	int rotatedTrees = 10;
	srand((time(0)));
	int i = rand() % 20 + 50;
	for (int j = 0; j < i; j++) {
		float randomX = (rand() % 600 - 300) / 10.0f;
		float randomY = 0.0f;
		float randomZ = (rand() % 600 - 300) / 10.0f;
		float randomScale = (rand() % 80 + 5) / 100.0f;

		Model* modelTree = new Model(tree, sizeof(tree), 92814);
		DrawableObject* drawableObject = new DrawableObject(modelTree, shaderProgram2);

		transformationInterface = new Translation(glm::vec3(randomX, randomY, randomZ));
		drawableObject->addTransformationInterface(transformationInterface);

		if (j < rotatedTrees) {
			transformationInterface = new DynamicRotation(glm::vec3(0.f, 1.f, 0.f), 0.0f, 0.05f);
		}
		else {
			transformationInterface = new Rotation(glm::vec3(0.f, 1.f, 0.f), 0.5f);
		}
		drawableObject->addTransformationInterface(transformationInterface);

		transformationInterface = new Scale(randomScale);
		drawableObject->addTransformationInterface(transformationInterface);
		//drawableObject->moveTransformation(2, 0);
		//drawableObject->moveTransformation(0, 1);

		addDrawableObject(drawableObject);
	}

	int k = rand() % 30 + 50;
	for (int j = 0; j < k; j++) {
		float randomX = (rand() % 600 - 300) / 10.0f;
		float randomY = 0.0f;
		float randomZ = (rand() % 600 - 300) / 10.0f;
		float randomScale = (rand() % 100 + 5) / 100.0f;

		Model* bushModel = new Model(bushes, sizeof(bushes), 8730);
		DrawableObject* drawableObject = new DrawableObject(bushModel, shaderProgram2);
		
		
		drawableObject->addTransformationInterface(new Translation(glm::vec3(randomX, randomY, randomZ)));
		drawableObject->addTransformationInterface(new Rotation(glm::vec3(0.f, 1.f, 0.f), 0.5f));
		drawableObject->addTransformationInterface(new Scale(randomScale));
		addDrawableObject(drawableObject);
	}

	
	ShaderProgram* shaderProgramSkycube = new ShaderProgram("vertex_textures_cube.glsl", "fragment_textures_cube.glsl");
	shaderPrograms.push_back(shaderProgramSkycube);

	ModelObject* modelObject = new ModelObject("house.obj");
	//TextureModel* textureModel = new TextureModel(plainTexture, sizeof(plainTexture), 6);
	ModelObject* modelObject3 = new ModelObject("teren.obj");
	ModelSkycube* textureModel1 = new ModelSkycube(skycube, sizeof(skycube), 36);
	ModelObject* modelObject1 = new ModelObject("zombie.obj");
	ModelObject* modelObject2 = new ModelObject("wooden watch tower2.obj");
	ModelObject* modelObject4 = new ModelObject("cottage_obj.obj");


	Texture* texture = new Texture("grass.png",0);
	Texture* texture1 = new Texture("posx.jpg","negx.jpg","posy.jpg","negy.jpg","posz.jpg", "negz.jpg", 1);
	Texture* texture2 = new Texture("house.png", 2);
	Texture* texture3 = new Texture("zombie.png", 3);
	Texture* texture4 = new Texture("Wood_Tower_Col.jpg", 4);
	Texture* texture5 = new Texture("grass.png", 5);
	Texture* texture6 = new Texture("cottage_diffuse.png", 6);

	DrawableObject* skycubeTexture = new DrawableObject(textureModel1, shaderProgramSkycube);
	//DrawableObject* plainTexture =new DrawableObject(textureModel, shaderProgramPlain);
	DrawableObject* plainTexture = new DrawableObject(modelObject3, shaderProgramPlain);
	DrawableObject* houseTexture = new DrawableObject(modelObject, shaderProgramPlain);
	DrawableObject* zombieTexture = new DrawableObject(modelObject1, shaderProgramPlain);
	DrawableObject* towerTexture = new DrawableObject(modelObject2, shaderProgramPlain);
	DrawableObject* cottageTexture = new DrawableObject(modelObject4, shaderProgramPlain);

	//plainTexture->addTransformationInterface(new Translation(glm::vec3(0.0f, 0.0f, 0.0f)));
	//plainTexture->addTransformationInterface(new Scale(38.0f));

	//plainTexture->setTexture(texture);

	//plainTexture->addTransformationInterface(new Translation(glm::vec3(0.0f, 0.0f, 0.0f)));
	plainTexture->addTransformationInterface(new Scale(1.5f));
	plainTexture->setTexture(texture5);

	skycubeTexture->setTexture(texture1);
	skycubeTexture->setSkybox(true); 

	houseTexture->setTexture(texture2);
	houseTexture->addTransformationInterface(new Scale(1.f));

	towerTexture->setTexture(texture4);
	towerTexture->addTransformationInterface(new Translation(glm::vec3(15.0f, -2.0f, 0.0f)));
	towerTexture->addTransformationInterface(new Scale(3.f));


	zombieTexture->setTexture(texture3);

	zombieTexture->addTransformationInterface(new Translation(glm::vec3(-10.0f, 0.0f, 0.0f)));
	zombieTexture->addTransformationInterface(new Scale(6.f));

	cottageTexture->setTexture(texture6);
	cottageTexture->addTransformationInterface(new Translation(glm::vec3(-25.0f, 0.0f, 15.0f)));
	cottageTexture->addTransformationInterface(new Scale(0.4f));

	addDrawableObject(plainTexture);
	addDrawableObject(skycubeTexture);
	addDrawableObject(houseTexture);
	addDrawableObject(zombieTexture);
	addDrawableObject(towerTexture);
	addDrawableObject(cottageTexture);
}

void Scene::initScene6() {
	DrawableObject::resetIDCounter();

	ShaderProgram* shaderProgram2 = new ShaderProgram("vertex_shader_reflektor.glsl", "fragment_shader_reflektor.glsl");
	shaderProgram2->setShader();
	shaderPrograms.push_back(shaderProgram2);

	ShaderProgram* shaderProgramPlain = new ShaderProgram("vertex_shader_combinedTeLe.glsl", "fragment_shader_combinedTeLe.glsl");
	shaderPrograms.push_back(shaderProgramPlain);
	
	TransformationInterface* transformationInterface;
	int rotatedTrees = 10;
	srand((time(0)));
	int i = rand() % 20 + 50;
	for (int j = 0; j < i; j++) {
		float randomX = (rand() % 600 - 300) / 10.0f;
		float randomY = 0.0f;
		float randomZ = (rand() % 600 - 300) / 10.0f;
		float randomScale = (rand() % 20 + 5) / 100.0f;

		//Model* modelTree = new Model(tree, sizeof(tree), 92814);
		//DrawableObject* drawableObject = new DrawableObject(modelTree, shaderProgram2);
		ModelObject* modelObject = new ModelObject("tree.obj");
		Texture* texture = new Texture("tree.png", 0);
		DrawableObject* drawableObject = new DrawableObject(modelObject, shaderProgramPlain);
		drawableObject->setTexture(texture);


		drawableObject->addTransformationInterface(new Translation(glm::vec3(randomX, randomY, randomZ)));

		if (j < rotatedTrees) {
			drawableObject->addTransformationInterface(new DynamicRotation(glm::vec3(0.f, 1.f, 0.f), 0, 0.5f));
		}
		else {
			drawableObject->addTransformationInterface(new Rotation(glm::vec3(0.f, 1.f, 0.f), 0.5f));

		}
		drawableObject->addTransformationInterface(new Scale(randomScale));

		//drawableObject->moveTransformation(2, 0);
		//drawableObject->moveTransformation(0, 1);
		

		addDrawableObject(drawableObject);


	}

	int k = rand() % 30 + 50;
	for (int j = 0; j < k; j++) {
		float randomX = (rand() % 600 - 300) / 10.0f;
		float randomY = 0.0f;
		float randomZ = (rand() % 600 - 300) / 10.0f;
		float randomScale = (rand() % 100 + 5) / 100.0f;

		Model* bushModel = new Model(bushes, sizeof(bushes), 8730);
		DrawableObject* drawableObject = new DrawableObject(bushModel, shaderProgram2);

		
		drawableObject->addTransformationInterface(new Translation(glm::vec3(randomX, randomY, randomZ)));
		drawableObject->addTransformationInterface(new Rotation(glm::vec3(0.f, 1.f, 0.f), 0.5f));
		drawableObject->addTransformationInterface(new Scale(randomScale));
		addDrawableObject(drawableObject);
	}

	
	ShaderProgram* shaderProgramSkycube = new ShaderProgram("vertex_textures_cube_night.glsl", "fragment_textures_cube_night.glsl");
	shaderPrograms.push_back(shaderProgramSkycube);

	ModelObject* modelObject = new ModelObject("house.obj");
	//TextureModel* textureModel = new TextureModel(plainTexture, sizeof(plainTexture), 6);
	ModelObject* modelObject1 = new ModelObject("zombie.obj");
	ModelObject* modelObject2 = new ModelObject("wooden watch tower2.obj");
	ModelObject* modelObject3 = new ModelObject("Login.obj");
	ModelSkycube* textureModel1 = new ModelSkycube(skycube, sizeof(skycube), 36);
	ModelObject* modelObject4 = new ModelObject("teren.obj");

	Texture* texture = new Texture("grass.png", 0);
	Texture* texture1 = new Texture("posx.jpg", "negx.jpg", "posy.jpg", "negy.jpg", "posz.jpg", "negz.jpg", 1);
	Texture* texture2 = new Texture("house.png", 2);
	Texture* texture3 = new Texture("zombie.png", 3);
	Texture* texture4 = new Texture("Wood_Tower_Col.jpg", 4);
	Texture* texture5 = new Texture("grass.png", 5);


	DrawableObject* skycubeTexture = new DrawableObject(textureModel1, shaderProgramSkycube);
	//DrawableObject* plainTexture = new DrawableObject(textureModel, shaderProgramPlain);
	DrawableObject* houseTexture = new DrawableObject(modelObject, shaderProgramPlain);
	DrawableObject* zombieTexture = new DrawableObject(modelObject1, shaderProgramPlain);
	DrawableObject* towerTexture = new DrawableObject(modelObject2, shaderProgramPlain);
	DrawableObject* loginTexture = new DrawableObject(modelObject3, shaderProgramPlain);
	DrawableObject* plainTexture = new DrawableObject(modelObject4, shaderProgramPlain);


	plainTexture->addTransformationInterface(new Translation(glm::vec3(0.0f, 0.0f, 0.0f)));
	plainTexture->addTransformationInterface(new Scale(2.0f));

	plainTexture->setTexture(texture);

	skycubeTexture->setTexture(texture1);
	skycubeTexture->setSkybox(true);

	houseTexture->setTexture(texture2);
	houseTexture->addTransformationInterface(new Scale(1.f));

	towerTexture->setTexture(texture4);
	towerTexture->addTransformationInterface(new Translation(glm::vec3(15.0f, -2.0f, 0.0f)));
	towerTexture->addTransformationInterface(new Scale(3.f));


	zombieTexture->setTexture(texture3);

	zombieTexture->addTransformationInterface(new Translation(glm::vec3(-10.0f, 0.0f, 0.0f)));
	zombieTexture->addTransformationInterface(new Scale(6.f));

	loginTexture->setTexture(texture5);
	loginTexture->addTransformationInterface(new Translation(glm::vec3(-25.0f, 0.0f, 15.0f)));
	loginTexture->addTransformationInterface(new Rotation(glm::vec3(0.f, 1.f, 0.f), 1.57));
	loginTexture->addTransformationInterface(new Scale(5.f));


	addDrawableObject(plainTexture);
	addDrawableObject(houseTexture);
	addDrawableObject(zombieTexture);
	addDrawableObject(towerTexture);
	addDrawableObject(loginTexture);
	addDrawableObject(skycubeTexture);
}



void Scene::initScene8() {
	DrawableObject::resetIDCounter();

	ShaderProgram* shaderProgram2 = new ShaderProgram("vertex_shader_les_lights.glsl", "fragment_shader_les_lights.glsl");

	shaderProgram2->setShader();
	shaderPrograms.push_back(shaderProgram2);

	glm::vec4 lightPositions[MAX_LIGHTS] = {
		glm::vec4(0.0, 10.0, 5.0, 1.0),
		glm::vec4(12.0, 0.0, 0.0, 1.0),
		glm::vec4(-12.0, 20.0, -10.0, 1.0),
		glm::vec4(30.0, 0.0, 10.0, 1.0)
	};

	glm::vec4 lightDiffuse[MAX_LIGHTS] = {
		glm::vec4(0.0, 0.0, 1.0, 1.0),
		glm::vec4(0.8, 0.3, 1.0, 0.5),
		glm::vec4(0.7, 0.3, 0.5, 1.0),
		glm::vec4(1.2, 0.2, 0.2, 1.0)
	};

	glm::vec4 lightSpecular[MAX_LIGHTS] = {
		glm::vec4(0.0, 0.0, 1.0, 1.0),
		glm::vec4(0.6, 1.0, 0.6, 1.0),
		glm::vec4(0.1, 0.5, 0.7, 1.0),
		glm::vec4(0.4, 0.9, 0.4, 1.0)
	};

	int numberOfLights = 4;

	for (int i = 0; i < numberOfLights; i++) {
		shaderProgram2->send("lights[" + std::to_string(i) + "].position", lightPositions[i]);
		shaderProgram2->send("lights[" + std::to_string(i) + "].diffuse", lightDiffuse[i]);
		shaderProgram2->send("lights[" + std::to_string(i) + "].specular", lightSpecular[i]);
	}
	shaderProgram2->send("numberOfLights", numberOfLights);



	int rotatedTrees = 10;
	srand((time(0)));
	int i = rand() % 300 + 100;
	for (int j = 0; j < i; j++) {
		float randomX = (rand() % 600 - 300) / 10.0f;
		float randomY = 0.0f;
		float randomZ = (rand() % 600 - 300) / 10.0f;
		float randomScale = (rand() % 60 + 5) / 100.0f;

		Model* modelTree = new Model(tree, sizeof(tree), 92814);
		DrawableObject* drawableObject = new DrawableObject(modelTree, shaderProgram2);

		drawableObject->addTransformationInterface(new Translation(glm::vec3(randomX, randomY, randomZ)));
		
		if (j < rotatedTrees) {
			drawableObject->addTransformationInterface(new DynamicRotation(glm::vec3(0.f, 1.f, 0.f), 0, 0.5f));
		}
		else {
			drawableObject->addTransformationInterface(new Rotation(glm::vec3(0.f, 1.f, 0.f), 0.5f));

		}
		drawableObject->addTransformationInterface(new Scale(randomScale));
		//drawableObject->moveTransformation(2, 0);
		//drawableObject->moveTransformation(0, 1);
		addDrawableObject(drawableObject);


	}

	int k = rand() % 800 + 400;
	for (int j = 0; j < k; j++) {
		float randomX = (rand() % 600 - 300) / 10.0f;
		float randomY = 0.0f;
		float randomZ = (rand() % 600 - 300) / 10.0f;
		float randomScale = (rand() % 100 + 5) / 100.0f;

		Model* bushModel = new Model(bushes, sizeof(bushes), 8730);
		DrawableObject* drawableObject = new DrawableObject(bushModel, shaderProgram2);

		drawableObject->addTransformationInterface(new Translation(glm::vec3(randomX, randomY, randomZ)));
		drawableObject->addTransformationInterface(new Rotation(glm::vec3(0.f, 1.f, 0.f), 0.5f));
		drawableObject->addTransformationInterface(new Scale(randomScale));

		addDrawableObject(drawableObject);
	}

	Model* plainModel = new Model(plain, sizeof(plain), 6);
	DrawableObject* plainDrawable = new DrawableObject(plainModel, shaderProgram2);

	plainDrawable->addTransformationInterface(new Translation(glm::vec3(0.0f, 0.0f, 0.0f)));
	plainDrawable->addTransformationInterface(new Scale(37.0f));
	addDrawableObject(plainDrawable);
}



void Scene::addDrawableObject(DrawableObject* object)
{
	objects.push_back(object);
}
void Scene::draw() {
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glDepthMask(GL_FALSE);
	for (DrawableObject* object : objects) {
		if (object->isSkybox()) {
			glStencilFunc(GL_ALWAYS, 0, 0xFF); 
			object->draw();
		}
	}
	glDepthMask(GL_TRUE);

	for (DrawableObject* object : objects) {
		if (!object->isSkybox()) {
			glStencilFunc(GL_ALWAYS, object->getID(), 0xFF); 
			object->draw();
		}
	}

	glDisable(GL_STENCIL_TEST);
}

void Scene::addObserver(Camera* camera) {
	for (ShaderProgram* shader : shaderPrograms) {
		if (shader) {
			camera->addObserver(shader);
			shader->addCamera(camera);
		}
	}
}

void Scene::addObserver(Light* light) {
	for (ShaderProgram* shader : shaderPrograms) {
		if (shader) {
			light->addObserver(shader);
			shader->addLight(light);
		}
	}
}


void Scene::addTreeAtPosition(const glm::vec3& position) {
	ShaderProgram* shaderProgram = shaderPrograms[0];

	Model* treeModel = new Model(tree, sizeof(tree), 92814);
	DrawableObject* treeObject = new DrawableObject(treeModel, shaderProgram);

	treeObject->addTransformationInterface(new Translation(position));
	treeObject->addTransformationInterface(new Scale(0.8f));

	addDrawableObject(treeObject);

	printf("Added a new tree at position [%f, %f, %f]\n", position.x, position.y, position.z);
}

void Scene::addPoint(glm::vec3& point) {
	bezierCurve->addControlPoint(point);
}

void Scene::addCurveToObject(int index)
{
	DrawableObject* object = objects[index-1];
	object->addTransformationInterface(bezierCurve);
}

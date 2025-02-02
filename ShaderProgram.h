#pragma once

// Author: Adam Kuchár
// Login: KUC0396

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include "ShaderLoader.h"
#include "IObserver.h"
#include "Camera.h"
#include "Light.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "DirectionalLight.h"
#include "Texture.h"

class Camera;
class ShaderProgram : public IObserver, ShaderLoader {
private:
    GLuint programID;
    Camera* camera;
    vector<Light*>lights;

public:

    ShaderProgram(const std::string& vertexFilePath, const std::string& fragmentFilePath);

    void setShader();
    void unbindShader();
    void setUniform4fv(const char* name, const glm::mat4& matrix);
    void setUniform3fv(const std::string& name, const glm::vec3& vector);
    void addCamera(Camera* camera);
    void addLight(Light* light);

    void update(int type) override;
    void updateView(glm::mat4& matrix);
    void updateProjection(glm::mat4& matrix);
    void updateModel(glm::mat4& matrix);
    void updateColorLight(glm::vec3& color);
    void updatePositionLight(glm::vec3& position);
    void updateViewPosition(glm::vec3& position);
    void updateAttenuationLight(Attenuation attenuation);
    void updateDirectionLight(glm::vec3& direction);
    void updateCutOffLight(float cutOff);
    void updateTexture(Texture* texture);

    void send(const std::string& name, const glm::vec4& value);
    void send(const std::string& name, int value);

    void setUniformMatrix3fv(const std::string& name, const glm::mat3& matrix);
    void setUniform1f(const std::string& name, float value);
    void setUniform1i(const char* name, int value);

};

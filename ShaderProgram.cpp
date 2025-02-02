#include "ShaderProgram.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

ShaderProgram::ShaderProgram(const std::string& vertexFilePath, const std::string& fragmentFilePath) {
    programID = loadShader(vertexFilePath.c_str(), fragmentFilePath.c_str());
    camera = nullptr;
}

void ShaderProgram::setShader() {
    glUseProgram(programID);
}

void ShaderProgram::unbindShader()
{
    glUseProgram(0);
}

void ShaderProgram::setUniform4fv(const char* name, const glm::mat4& matrix) {
    this->setShader();
    GLint location = glGetUniformLocation(programID, name);
    if (location != -1) {
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

}

void ShaderProgram::setUniform3fv(const std::string& name, const glm::vec3& vector) {
    this->setShader();
    GLint location = glGetUniformLocation(programID, name.c_str());
    if (location != -1) {
        glUniform3fv(location, 1, glm::value_ptr(vector));
    }
}


void ShaderProgram::setUniformMatrix3fv(const std::string& name, const glm::mat3& matrix) {
    this->setShader();
    GLint location = glGetUniformLocation(programID, name.c_str());
	if (location != -1) {
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}

void ShaderProgram::setUniform1f(const std::string& name, float value)
{
    this->setShader();
    GLint location = glGetUniformLocation(programID, name.c_str());
    if (location != -1)
        glUniform1f(location, value);
        
}

void ShaderProgram::setUniform1i(const char* name, int value)
{
    this->setShader();
    GLint location = glGetUniformLocation(programID, name);
	if (location != -1)
		glUniform1i(location, value);
}

void ShaderProgram::send(const std::string& name, const glm::vec4& value) {
    GLint location = glGetUniformLocation(programID, name.c_str());
    if (location != -1) {
        glUniform4fv(location, 1, glm::value_ptr(value));
    }
}

void ShaderProgram::send(const std::string& name, int value) {
    GLint location = glGetUniformLocation(programID, name.c_str());
    if (location != -1) {
        glUniform1i(location, value);
    }
}

void ShaderProgram::addCamera(Camera* camera)
{
    this->camera = camera;
}

void ShaderProgram::addLight(Light* light)
{
    lights.push_back(light);
}

void ShaderProgram::updateView(glm::mat4& matrix)
{
    setUniform4fv("viewMatrix", matrix);
}
void ShaderProgram::updateProjection(glm::mat4& matrix)
{
    setUniform4fv("projectionMatrix", matrix);
}
void ShaderProgram::updateModel(glm::mat4& matrix)
{
    setUniform4fv("modelMatrix", matrix);
}
void ShaderProgram::updateColorLight(glm::vec3& color)
{
    setUniform3fv("lightColor", color);
}
void ShaderProgram::updatePositionLight(glm::vec3& position)
{
    setUniform3fv("lightPosition", position);
}
void ShaderProgram::updateViewPosition(glm::vec3& position) {
    setUniform3fv("viewPosition", position);
}

void ShaderProgram::updateAttenuationLight(Attenuation attenuation)
{
    setUniform3fv("attenuation", glm::vec3(attenuation.constant, attenuation.linear, attenuation.quadratic));
}

void ShaderProgram::updateDirectionLight(glm::vec3& direction)
{
    setUniform3fv("lightDirection", direction);
}

void ShaderProgram::updateCutOffLight(float cutOff)
{
    setUniform1f("cutOff", cutOff);
}

void ShaderProgram::updateTexture(Texture* texture)
{
    texture->bind();
    setUniform1i("textureUnitID", texture->getTextureUnit());
}



void ShaderProgram::update(int type)
{
    switch (type) {
    case 0: {
        glm::mat4 viewMatrix = camera->getCamera();
        updateView(viewMatrix);
        glm::vec3 viewPosition = camera->getCameraPosition();
        updateViewPosition(viewPosition);
        break;
    }
    case 1: {
        glm::mat4 projectionMatrix = camera->getProjection();
        updateProjection(projectionMatrix);
        break;
    }
    case 2: {
        for (auto light : lights) {
            PointLight* pointLight = dynamic_cast<PointLight*>(light);
            SpotLight* spotLight = dynamic_cast<SpotLight*>(light);

            if (pointLight != nullptr) {
                glm::vec3 lightPosition = pointLight->getPosition();
                updatePositionLight(lightPosition);
            }
            else if (spotLight != nullptr) {
                glm::vec3 lightPosition = spotLight->getPosition();
                updatePositionLight(lightPosition);
            }
        }
        break;
    }
    case 3: {
        for (auto light : lights) {
            PointLight* pointLight = dynamic_cast<PointLight*>(light);
            SpotLight* spotLight = dynamic_cast<SpotLight*>(light);
            DirectionalLight* directionalLight = dynamic_cast<DirectionalLight*>(light);

            if (pointLight != nullptr) {
                glm::vec3 lightColor = pointLight->getColor();
                updateColorLight(lightColor);
            }
            else if (spotLight != nullptr) {
                glm::vec3 lightColor = spotLight->getColor();
                updateColorLight(lightColor);
            }
            else if (directionalLight != nullptr) {
                glm::vec3 lightColor = directionalLight->getColor();
                updateColorLight(lightColor);
            }
        }
        break;
    }
    case 4: {
        for (auto light : lights) {
            PointLight* pointLight = dynamic_cast<PointLight*>(light);
            SpotLight* spotLight = dynamic_cast<SpotLight*>(light);

            if (pointLight != nullptr) {
                Attenuation attenuation = pointLight->getAttenuation();
                updateAttenuationLight(attenuation);
            }
            else if (spotLight != nullptr) {
                Attenuation attenuation = spotLight->getAttenuation();
                updateAttenuationLight(attenuation);
            }
        }
        break;
    }
    case 5: {
        for (auto light : lights) {
            SpotLight* spotLight = dynamic_cast<SpotLight*>(light);
            DirectionalLight* directionalLight = dynamic_cast<DirectionalLight*>(light);

            if (spotLight != nullptr) {
                glm::vec3 lightDirection = spotLight->getDirection();
                updateDirectionLight(lightDirection);
            }
            else if (directionalLight != nullptr) {
                glm::vec3 lightDirection = directionalLight->getDirection();
                updateDirectionLight(lightDirection);
            }
        }
        break;
    }
    case 6: {
        for (auto light : lights) {
            SpotLight* spotLight = dynamic_cast<SpotLight*>(light);

            if (spotLight != nullptr) {
                float cutOff = spotLight->getCutOff();
                updateCutOffLight(cutOff);
            }
        }
        break;
    }
    default:
        break;
    }
}

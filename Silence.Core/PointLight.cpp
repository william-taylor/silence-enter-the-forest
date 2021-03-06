
#include "PointLight.h"

PointLight::PointLight() :
    pointLightActive(true)
{
}

PointLight::~PointLight()
{
}

void PointLight::setPosition(glm::vec3 position)
{
    this->pointPosition = position;
}

void PointLight::setColour(glm::vec3 colour)
{
    this->pointColour = colour;
}

void PointLight::setAttribuation(glm::vec4 attr)
{
    this->att = attr;
}

void PointLight::send(GPU_Program * p, int index)
{
    auto sID = "pointLights[" + std::to_string(index) + "].";
    auto ID = p->getID();

    if (ID != NULL && pointLightActive)
    {
        glUniform3fv(glGetUniformLocation(ID, std::string(sID + "pointPosition").c_str()), 1, glm::value_ptr(pointPosition));
        glUniform3fv(glGetUniformLocation(ID, std::string(sID + "pointColour").c_str()), 1, glm::value_ptr(pointColour));
        glUniform4fv(glGetUniformLocation(ID, std::string(sID + "att").c_str()), 1, glm::value_ptr(att));
        glUniform1i(glGetUniformLocation(ID, std::string(sID + "pointActive").c_str()), 1);
    }

    if (ID != NULL && !pointLightActive)
    {
        glUniform1i(glGetUniformLocation(ID, std::string(sID + "pointActive").c_str()), 0);
    }
}

void PointLight::toggle()
{
    pointLightActive = !pointLightActive;
}

void PointLight::turnOff()
{
    pointLightActive = false;
}

void PointLight::turnOn()
{
    pointLightActive = true;
}
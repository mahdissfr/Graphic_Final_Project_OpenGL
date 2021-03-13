#pragma once

#include "pch.h"

#include "GraphicDevice.h"
#include "PositionedOrientedObject.h"
#include "IFunctionalObject.h"

class GraphicDevice;

class GameObject : public PositionedOrientedObject, public IFunctionalObject
{

public:
	GameObject(GraphicDevice* device);
	~GameObject();
	void					Render();
	void					Update(GLFWwindow* window);
	virtual void			Setup() = 0;
	void					NoMoreChange();
	double					vectorDistance(glm::vec3 a, glm::vec3 b);

	float					scons = 0.8;
	bool					changeMode = true;
	bool					move = false;
	float					moveDistance = 0.0;
	glm::vec3				v1;
	glm::vec3				v2;


	// timing
	float					deltaTime = 0.0f;	// time between current frame and last frame
	float					lastFrame = 0.0f;

protected:
	unsigned int			vbo;
	unsigned int			vao;
	unsigned int			ebo;
	GraphicDevice* device;
	float* vertices;
	unsigned int* indices;
	unsigned int			texture;
	short					indicesSize;
	short					verticesSize;

};

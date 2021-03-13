#include "GraphicDevice.h"

GraphicDevice::GraphicDevice()
{
	
}

void GraphicDevice::SetCamera(Camera* camera) {
	this->camera = camera;
}


void GraphicDevice::SetupDevice()
{
	shader = new Shader("platform.vs", "platform.fs");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);
}

void GraphicDevice::Render(std::vector<GameObject*>* objects)
{

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader->use();

	for (auto object = objects->begin(); object != objects->end(); object++)
	{
		(*object)->Render();
	}

}

void GraphicDevice::NoMoreChange() {
	this->changeMode = false;
}

void GraphicDevice::SetChangeMode() {
	this->changeMode = true;
}

Shader* GraphicDevice::GetShader()
{
	return this->shader;
}
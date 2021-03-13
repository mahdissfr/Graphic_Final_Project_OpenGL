#pragma once
#include "pch.h"

#include "GameObject.h"
#include "Shader.h"
#include "Camera.h"

class GameObject;

class GraphicDevice
{

public:
	GraphicDevice();

	void					SetupDevice();
	void					Render(std::vector<GameObject*>* objects);
	void					NoMoreChange();
	void					SetChangeMode();
	void					SetCamera(Camera* camera);

	Shader*					GetShader();

	bool					changeMode = true;
	Camera*					camera;

private:

	Shader*					shader;

};

#include "GameObject.h"
#include <iterator> 
using namespace std;

GameObject::GameObject(GraphicDevice* device) :
	vbo(0),
	vao(0),
	ebo(0),
	vertices(nullptr),
	indices(nullptr),
	texture(0),
	indicesSize(0),
	verticesSize(0)
{
	this->device = device;
}

GameObject::~GameObject()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	glDeleteTextures(1, &texture);
	delete vertices;
	delete indices;
}



void GameObject::Render()
{
	glBindTexture(GL_TEXTURE_2D, texture);
	unsigned int modelLoc = glGetUniformLocation(device->GetShader()->ID, "transform");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(this->GetTransform()));
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);
	
}

void GameObject::Update(GLFWwindow* window) {
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
		//if (glfwGetKey(window, GLFW_KEY_X) == GLFW_RELEASE and !move){
		move = true;
		v1 = device->camera->GetPosition();
		v2 = device->camera->GetForward();
		moveDistance= vectorDistance(GetPosition(), v1);
	}
	else if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
	//else if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS and move) {
		move = false;
	}
	
	if (move) {
		v1 = device->camera->GetPosition();
		v2 = device->camera->GetForward();
		glm::vec3 pos = glm::vec3(v1.x + moveDistance * v2.x, v1.y + moveDistance * v2.y, v1.z - moveDistance * v2.z);
		SetPosition(pos);
	}

	//scale
	glm::vec3 scl = GetScale();
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
		scl += glm::vec3(-1 * scons * deltaTime, 0.0, 0.0);
	}
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
		scl += glm::vec3(scons * deltaTime, 0.0, 0.0);
	}
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
		scl += glm::vec3(0.0, scons * deltaTime, 0.0);
	}
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
		scl += glm::vec3(0.0, -1 * scons * deltaTime, 0.0);
	}
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
		scl += glm::vec3(0.0, 0.0, scons * deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
		scl += glm::vec3(0.0, 0.0, -1 * scons * deltaTime);
	}
	if (scl.x < 0)
		scl.x = 0;
	if (scl.y < 0)
		scl.y = 0;
	if (scl.z < 0)
		scl.z = 0;
	SetScale(scl);
	//rotation
	//pitch

	auto angle = GetQuaternion();
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
		SetQuaternion(glm::rotate(angle, glm::radians(20.f * deltaTime), glm::vec3(0.0f, 1.0f, 0.0f)));
	}
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
		SetQuaternion(glm::rotate(angle, glm::radians(20.f * deltaTime), glm::vec3(0.0f, -1.0f, 0.0f)));
	}
	//yaw
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
		SetQuaternion(glm::rotate(angle, glm::radians(20.f * deltaTime), glm::vec3(1.0f, 0.0f, 0.0f)));
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
		SetQuaternion(glm::rotate(angle, glm::radians(20.f * deltaTime), glm::vec3(-1.0f, 0.0f, 0.0f)));
	}
	//roll
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
		SetQuaternion(glm::rotate(angle, glm::radians(20.f * deltaTime), glm::vec3(0.0f, 0.0f, 1.0f)));
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		SetQuaternion(glm::rotate(angle, glm::radians(20.f * deltaTime), glm::vec3(0.0f, 0.0f, -1.0f)));
	}
}


void GameObject::NoMoreChange() {
	this->changeMode = false;
}

double GameObject::vectorDistance(glm::vec3 a, glm::vec3 b) {
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}

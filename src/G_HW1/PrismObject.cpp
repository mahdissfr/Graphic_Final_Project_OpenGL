#include "PrismObject.h"

#include <stb_image.h>
PrismObject::PrismObject(GraphicDevice* device) : GameObject(device)
{
	
	float v[] = {

		// Triangle 1
		1.f, -1 / sqrt(3), 1.f,
		1.0,0.0,0.0,

		sqrt(3) / 2, -1 / 2, -1 / 2,
		0.0,1.0,0.0,

		-1 * sqrt(3) / 2, -1 / 2, -1 / 2,
		0.0,0.0,1.0,

		//Triangle 2
		0.f, 1.f, 1 / 2,
		1.0,0.0,0.0,

		sqrt(3) / 2, -1 / 2, 1 / 2,
		0.0,0.0,1.0,

		-1 * sqrt(3) / 2, -1 / 2, 1 / 2,
		0.0,1.0,0.0

	};

	unsigned int ii[] = {
		// Bottom
		0, 2, 1,

		// Top
		3, 4, 5,

		// Side1
		0, 1, 3,
		3, 1, 4,

		// Side 2
		1, 2, 4,
		4, 2, 5,

		// Side 3
		2, 0, 5,
		5, 0, 3,
	};

	verticesSize = *(&v + 1) - v;
	indicesSize = *(&ii + 1) - ii;
	vertices = new float[verticesSize];
	indices = new unsigned int[indicesSize];
	for (size_t i = 0; i < verticesSize; i++)
	{
		vertices[i] = v[i];
	}
	for (size_t i = 0; i < indicesSize; i++)
	{
		indices[i] = ii[i];
	}

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verticesSize, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indicesSize, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);


	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	unsigned char* data = stbi_load("wall.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

void PrismObject::Update(GLFWwindow* window)
{
	GameObject::Update(window);
}


void PrismObject::Setup()
{
}
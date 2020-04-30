#include "graphics/window.h"
//#include "utils/fileutils.h"
#include "graphics/shader.h"

int main()
{
	using namespace rxogl;
	using namespace graphics;
	//using namespace utils;

	Window window("rxogl", 960, 540);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	std::cout << glGetString(GL_VERSION) << std::endl;

	static const float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f
	};

	// Give vertices to oGL by creating a buffer 
	unsigned int vbo;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vbo);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// Give our vertices to oGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	Shader shader("shaders/basic.vert", "shaders/basic.frag");
	shader.enable();

	while (!window.closed())
	{
		window.clear();

		glDrawArrays(GL_QUADS, 0, 4);

		window.update();
	}

	return 0;
}
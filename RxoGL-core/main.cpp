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

	static const float cubeVertices[] = {
		//	-0.5f, -0.5f, 0.0f,
		//	-0.5f,  0.5f, 0.0f,
		//	 0.5f,  0.5f, 0.0f
		//	 //0.5f, -0.5f, 0.0f
		//};
		//
		-1.0f,-1.0f,-1.0f, // triangle 1 : begin
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, // triangle 1 : end
		 1.0f, 1.0f,-1.0f, // triangle 2 : begin
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f, // triangle 2 : end
		 1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f
	};

	static const float triangleVertices[] = {
		4.0f,-1.0f, 1.0f, // triangle 1 : begin
		6.0f,-1.0f, 1.0f,
		4.0f, 1.0f, 1.0f, // triangle 1 : end
	};

	static float color_buffer_data[]
	{
		0.583f, 0.771f, 0.014f,
		0.609f, 0.115f, 0.436f,
		0.327f, 0.483f, 0.844f,
		0.822f, 0.569f, 0.201f,
		0.435f, 0.602f, 0.223f,
		0.310f, 0.747f, 0.185f,
		0.597f, 0.770f, 0.761f,
		0.559f, 0.436f, 0.730f,
		0.359f, 0.583f, 0.152f,
		0.483f, 0.596f, 0.789f,
		0.559f, 0.861f, 0.639f,
		0.195f, 0.548f, 0.859f,
		0.014f, 0.184f, 0.576f,
		0.771f, 0.328f, 0.970f,
		0.406f, 0.615f, 0.116f,
		0.676f, 0.977f, 0.133f,
		0.971f, 0.572f, 0.833f,
		0.140f, 0.616f, 0.489f,
		0.997f, 0.513f, 0.064f,
		0.945f, 0.719f, 0.592f,
		0.543f, 0.021f, 0.978f,
		0.279f, 0.317f, 0.505f,
		0.167f, 0.620f, 0.077f,
		0.347f, 0.857f, 0.137f,
		0.055f, 0.953f, 0.042f,
		0.714f, 0.505f, 0.345f,
		0.783f, 0.290f, 0.734f,
		0.722f, 0.645f, 0.174f,
		0.302f, 0.455f, 0.848f,
		0.225f, 0.587f, 0.040f,
		0.517f, 0.713f, 0.338f,
		0.053f, 0.959f, 0.120f,
		0.393f, 0.621f, 0.362f,
		0.673f, 0.211f, 0.457f,
		0.820f, 0.883f, 0.371f,
		0.982f, 0.099f, 0.879f
	};


	// Give vertices to oGL by creating a buffer 
	unsigned int vbo;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vbo);
	// The following commands will talk about our 'vertexbuffer' buffer
	//glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//// Give our vertices to oGL.
	//glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(
	//	0, 
	//	3, 
	//	GL_FLOAT, 
	//	GL_FALSE, 
	//	0, 
	//	(void*)0);

	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	Shader shader("shaders/basic.vert", "shaders/basic.frag");
	shader.enable();

	shader.mathStuff();

	while (!window.closed())
	{
		window.clear();

		if (window.isKeyPressed(GLFW_KEY_W))
		{
			shader.z--;
			shader.mathStuff();
		}
		if (window.isKeyPressed(GLFW_KEY_S))
		{
			shader.z++;
			shader.mathStuff();
		}
		if (window.isKeyPressed(GLFW_KEY_A))
		{
			shader.x--;
			shader.mathStuff();
		}
		if (window.isKeyPressed(GLFW_KEY_D))
		{
			shader.x++;
			shader.mathStuff();
		}
		if (window.isKeyPressed(GLFW_KEY_LEFT_SHIFT))
		{
			shader.y--;
			shader.mathStuff();
		}
		if (window.isKeyPressed(GLFW_KEY_SPACE))
		{
			shader.y++;
			shader.mathStuff();
		}

		shader.enable();
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0);
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0);
		glDrawArrays(GL_TRIANGLES, 0, 3 * 3);



		window.update();
	}

	return 0;
}
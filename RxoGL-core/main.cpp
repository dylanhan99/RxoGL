#include "graphics/window.h"
//#include "utils/fileutils.h"
#include "graphics/shader.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Renderer.h"
#include "Texture.h"

//#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"

#include "tests/TestClearColor.h"
#include "tests/TestTexture2D.h"

int main()
{
	Window window("rxogl", 960, 540);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	std::cout << glGetString(GL_VERSION) << std::endl;

	//static const float cubeVertices[] = {
	//	-1.0f,-1.0f,-1.0f, // 0
	//	-1.0f,-1.0f, 1.0f, // 1
	//	-1.0f, 1.0f, 1.0f, // 2 
	//	 1.0f, 1.0f,-1.0f, // 3 
	//	-1.0f, 1.0f,-1.0f, // 4 
	//	 1.0f,-1.0f, 1.0f, // 5
	//	 1.0f,-1.0f,-1.0f, // 6
	//	 1.0f, 1.0f, 1.0f  // 7
	//};

	//unsigned int cubeIndices[] = {
	//	0, 1, 2,
	//	3, 0, 4,
	//	5, 0, 6,
	//	3, 6, 0,
	//	0, 2, 4,
	//	5, 1, 0,
	//	2, 1, 5,
	//	7, 6, 3,
	//	6, 7, 5,
	//	7, 3, 4,
	//	7, 4, 2,
	//	7, 2, 5
	//};

	//static const float triangleVertices[] = {
	//	4.0f,-1.0f, 1.0f, // triangle 1 : begin
	//	6.0f,-1.0f, 1.0f,
	//	4.0f, 1.0f, 1.0f, // triangle 1 : end
	//};

	//static float color_buffer_data[]
	//{
	//	0.583f, 0.771f, 0.014f,
	//	0.609f, 0.115f, 0.436f,
	//	0.327f, 0.483f, 0.844f,
	//	0.822f, 0.569f, 0.201f,
	//	0.435f, 0.602f, 0.223f,
	//	0.310f, 0.747f, 0.185f,
	//	0.597f, 0.770f, 0.761f,
	//	0.559f, 0.436f, 0.730f,
	//	0.359f, 0.583f, 0.152f,
	//	0.483f, 0.596f, 0.789f,
	//	0.559f, 0.861f, 0.639f,
	//	0.195f, 0.548f, 0.859f,
	//	0.014f, 0.184f, 0.576f,
	//	0.771f, 0.328f, 0.970f,
	//	0.406f, 0.615f, 0.116f,
	//	0.676f, 0.977f, 0.133f,
	//	0.971f, 0.572f, 0.833f,
	//	0.140f, 0.616f, 0.489f,
	//	0.997f, 0.513f, 0.064f,
	//	0.945f, 0.719f, 0.592f,
	//	0.543f, 0.021f, 0.978f,
	//	0.279f, 0.317f, 0.505f,
	//	0.167f, 0.620f, 0.077f,
	//	0.347f, 0.857f, 0.137f,
	//	0.055f, 0.953f, 0.042f,
	//	0.714f, 0.505f, 0.345f,
	//	0.783f, 0.290f, 0.734f,
	//	0.722f, 0.645f, 0.174f,
	//	0.302f, 0.455f, 0.848f,
	//	0.225f, 0.587f, 0.040f,
	//	0.517f, 0.713f, 0.338f,
	//	0.053f, 0.959f, 0.120f,
	//	0.393f, 0.621f, 0.362f,
	//	0.673f, 0.211f, 0.457f,
	//	0.820f, 0.883f, 0.371f,
	//	0.982f, 0.099f, 0.879f
	//};

	// Give vertices to oGL by creating a buffer 
	//unsigned int vbo;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	//glGenBuffers(1, &vbo);
	// The following commands will talk about our 'vertexbuffer' buffer
	//glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//// Give our vertices to oGL.
	//glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	// alreadt bound in constructor
	//VertexArray va;
	//VertexBuffer vb_Cube(cubeVertices, sizeof(cubeVertices));
	//VertexBufferLayout layout_Cube;
	//layout_Cube.Push<float>(3);
	//va.AddBuffer(vb_Cube, layout_Cube);
	//
	//IndexBuffer ib(cubeIndices, 12 * 3);

	//Shader shader("F:/GitHub/RxoGL/RxoGL-core/res/shaders/basic.vert", "F:/GitHub/RxoGL/RxoGL-core/res/shaders/basic.frag");
	//VertexArray va;
	//glm::vec3 translationA(200, 200, 0);
	//glm::vec3 translationB(400, 200, 0);
	//glm::mat4 proj(glm::ortho(0.f, 960.f, 0.f, 540.f, -1.0f, 1.0f));
	//glm::mat4 view(glm::translate(glm::mat4(1.0f), glm::vec3(/*-10*/0, 0, 0)));
	//
	//static const float vertices[] =
	//{
	//	-50.f, -50.f, 0.0f, 0.0f,
	//	 50.f, -50.f, 1.0f, 0.0f,
	//	 50.f,  50.f, 1.0f, 1.0f,
	//	-50.f,  50.f, 0.0f, 1.0f
	//};
	//
	//unsigned int indeces[] =
	//{
	//	0, 1, 2,
	//	2, 3, 0
	//};
	//
	//VertexBuffer vb(vertices, 4 * 4 * sizeof(float));
	//
	//VertexBufferLayout layout;
	//layout.Push<float>(2);
	//layout.Push<float>(2);
	//va.AddBuffer(vb, layout);
	//
	//IndexBuffer ib(indeces, 2 * 3);
	//
	//shader.Bind();
	//
	//Texture texture("F:/GitHub/RxoGL/RxoGL-core/res/textures/OverwatchLogo.png");
	//texture.Bind(); // 0 by default
	//shader.SetUniform1i("u_Texture", 0); // slot 0 because the previous bind used the default



	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	Renderer renderer;

	// Setting up imgui
	{
		// GL 3.0 + GLSL 130
		const char* glsl_version = "#version 130";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window.GetWindow(), true);
		ImGui_ImplOpenGL3_Init(glsl_version);
		//io.Fonts->AddFontDefault();
		//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
		//IM_ASSERT(font != NULL);
	}

	tests::Test* currentTest = nullptr;
	tests::TestMenu* testMenu = new tests::TestMenu(currentTest);
	testMenu->RegisterTest<tests::TestClearColor>("Clear Color");

	tests::TestTexture2D* test = new tests::TestTexture2D();

	currentTest = test;

	while (!window.closed())
	{
		renderer.Clear();
		//shader.Bind();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (currentTest)
		{
			currentTest->OnUpdate(0.0f);
			currentTest->OnRender();
			ImGui::Begin("Test");
			if (currentTest != testMenu && ImGui::Button("<-"))
			{
				delete currentTest;
				currentTest = testMenu;
			}
			currentTest->OnImguiRender();
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}

		//{
		//	glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
		//	glm::mat4 mvp = proj * view * model;
		//	shader.SetUniformMat4f("u_MVP", mvp);
		//	renderer.Draw(va, ib, shader);
		//}
		//
		//{
		//	glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
		//	glm::mat4 mvp = proj * view * model;
		//	shader.SetUniformMat4f("u_MVP", mvp);
		//	renderer.Draw(va, ib, shader);
		//}


		// Rendering
		ImGui::Render();
		//glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		window.update();
	}
	if (currentTest != testMenu)
		delete testMenu;
	delete currentTest;
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	return 0;
}
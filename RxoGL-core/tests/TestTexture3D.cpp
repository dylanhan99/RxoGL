#include "TestTexture3D.h"


namespace tests
{
	TestTexture3D::TestTexture3D()
		:
		m_TranslationA(glm::vec3(50, 50, 50)),
		m_TranslationCam(glm::vec3(0, 0, 75)),
		x(m_TranslationA.x), y(m_TranslationA.y), z(m_TranslationA.z),
		//m_Proj(glm::ortho(0.f, 960.f, 0.f, 540.f, -1.0f, 1.0f)),
		//m_View(glm::translate(glm::mat4(1.0f), glm::vec3(/*-10*/0, 0, 0)))
		m_Proj(glm::perspective(glm::radians(45.0f), 960.0f / 540.0f, 0.1f, 1000.0f)),
		m_View(glm::lookAt(m_TranslationCam, glm::vec3(x, y, z), glm::vec3(0, 1, 0)))
	{
		static const float vertices[] = {
			-50.0f,-50.0f,-50.0f, 0.583f, 0.771f, 0.014f, 1, // 0
			-50.0f,-50.0f, 50.0f, 0.609f, 0.115f, 0.436f, 1, // 1
			-50.0f, 50.0f, 50.0f, 0.327f, 0.483f, 0.844f, 1, // 2 
			 50.0f, 50.0f,-50.0f, 0.822f, 0.569f, 0.201f, 1, // 3 
			-50.0f, 50.0f,-50.0f, 0.435f, 0.602f, 0.223f, 1, // 4 
			 50.0f,-50.0f, 50.0f, 0.310f, 0.747f, 0.185f, 1, // 5
			 50.0f,-50.0f,-50.0f, 0.597f, 0.770f, 0.761f, 1, // 6
			 50.0f, 50.0f, 50.0f, 0.559f, 0.436f, 0.730f, 1  // 7
		};

		unsigned int indeces[] = {
			0, 1, 2,
			3, 0, 4,
			5, 0, 6,
			3, 6, 0,
			0, 2, 4,
			5, 1, 0,
			2, 1, 5,
			7, 6, 3,
			6, 7, 5,
			7, 3, 4,
			7, 4, 2,
			7, 2, 5
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


		m_VAO = std::make_unique<rxogl::VertexArray>();
		m_VBO = std::make_unique<rxogl::VertexBuffer>(vertices, sizeof(vertices));
		//m_ColBO = std::make_unique<VertexBuffer>(color_buffer_data, sizeof(color_buffer_data));
		m_IBO = std::make_unique<rxogl::IndexBuffer>(indeces, 12 * 3);

		rxogl::BufferLayout layout;
		layout.Push<float>(3); // position
		layout.Push<float>(4); // color
		m_VAO->AddBuffer(*m_VBO, layout);
		//m_VAO->AddBuffer(*m_ColBO, layout);

		m_Shader = std::make_unique<Shader>("F:/GitHub/RxoGL/RxoGL-core/res/shaders/basic.vert", "F:/GitHub/RxoGL/RxoGL-core/res/shaders/basic.frag");
		m_Shader->Bind();
		//m_Texture = std::make_unique<Texture>("F:/GitHub/RxoGL/RxoGL-core/res/textures/OverwatchLogo.png");
		//m_Shader->SetUniform1i("u_Texture", 0); // slot 0 because the previous bind used the default
	}

	TestTexture3D::~TestTexture3D()
	{
	}

	void TestTexture3D::OnUpdate(float deltaTime)
	{
	}

	void TestTexture3D::OnRender()
	{
		rxogl::Renderer renderer;

		m_Shader->Bind();
		//m_Texture->Bind();
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
			//glm::mat4 model = glm::mat4(1.0f);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
		}
	}

	void TestTexture3D::OnImguiRender()
	{
		ImGui::SliderFloat3("Translation A", &m_TranslationA.x, -600.f, 600.f/*0.0f, 960.0f*/);
		ImGui::SliderFloat3("Camera Trans ", &m_TranslationCam.x, -100.0f, 100.0f);
	}
}
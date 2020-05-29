#include "TestTexture2D.h"
#include "../ConstantsRxogl.h"

namespace tests
{
	TestTexture2D::TestTexture2D()
		: 
		m_TranslationA(glm::vec3(200, 200, 0)), m_TranslationB(glm::vec3(400, 200, 0)),
		m_Proj(glm::ortho(0.f, 960.f, 0.f, 540.f, -1.0f, 1.0f)), 
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(/*-10*/0, 0, 0)))
	{
		static const float vertices[] =
		{
			-50.f, -50.f, 0.0f, 0.583f, 0.771f, 0.014f, 1, 0.0f, 0.0f, 0.0f,
			 50.f, -50.f, 0.0f, 0.609f, 0.115f, 0.436f, 1, 1.0f, 0.0f, 0.0f,
			 50.f,  50.f, 0.0f, 0.327f, 0.483f, 0.844f, 1, 1.0f, 1.0f, 0.0f,
			-50.f,  50.f, 0.0f, 0.822f, 0.569f, 0.201f, 1, 0.0f, 1.0f, 0.0f,
		
			100.f, -50.f, 0.0f, 0.435f, 0.602f, 0.223f, 1, 0.0f, 0.0f, 1.0f,
			200.f, -50.f, 0.0f, 0.310f, 0.747f, 0.185f, 1, 1.0f, 0.0f, 1.0f,
			200.f,  50.f, 0.0f, 0.597f, 0.770f, 0.761f, 1, 1.0f, 1.0f, 1.0f,
			100.f,  50.f, 0.0f, 0.559f, 0.436f, 0.730f, 1, 0.0f, 1.0f, 1.0f
		};

		unsigned int indeces[] =
		{
			0, 1, 2,
			2, 3, 0,

			4, 5, 6,
			6, 7, 4
		};

		m_VAO = std::make_unique<rxogl::VertexArray>();
		m_VBO = std::make_unique<rxogl::VertexBuffer>(vertices, sizeof(vertices));
		m_IBO = std::make_unique<rxogl::IndexBuffer>(indeces, 4 * 3);

		rxogl::BufferLayout layout;
		layout.Push<glm::vec3>(1); // vec3 Pos
		layout.Push<glm::vec4>(1); // vec4 Color
		layout.Push<glm::vec2>(1); // Texture
		layout.Push<float>(1); // Texture ID
		m_VAO->AddBuffer(*m_VBO, layout);

		m_Shader = std::make_unique<Shader>("F:/GitHub/RxoGL/RxoGL-core/res/shaders/basic.vert", "F:/GitHub/RxoGL/RxoGL-core/res/shaders/basic.frag");
		m_Shader->Bind();
		m_OWTexture = std::make_unique<rxogl::Texture>("F:/GitHub/RxoGL/RxoGL-core/res/textures/OverwatchLogo.png");
		m_YTTexture = std::make_unique<rxogl::Texture>("F:/GitHub/RxoGL/RxoGL-core/res/textures/youtube.png");
		m_OWTexture->Bind();
		m_YTTexture->Bind(1);
	}

	TestTexture2D::~TestTexture2D()
	{
	}

	void TestTexture2D::OnUpdate(float deltaTime)
	{
		m_Shader->Bind();
		m_OWTexture->Bind();
		m_YTTexture->Bind(1);

		int samplers[2] = { 0, 1 };
		m_Shader->SetUniform1iv("u_Textures", 2, samplers);
	}

	void TestTexture2D::OnRender()
	{
		rxogl::Renderer renderer;
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
		}
	}

	void TestTexture2D::OnImguiRender()
	{
		ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0.0f, 960.0f);
		ImGui::SliderFloat3("Translation B", &m_TranslationB.x, 0.0f, 960.0f);
	}
}
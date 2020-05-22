#include "TestTexture2D.h"


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
			-50.f, -50.f, 0.0f, 0.0f,
			 50.f, -50.f, 1.0f, 0.0f,
			 50.f,  50.f, 1.0f, 1.0f,
			-50.f,  50.f, 0.0f, 1.0f
		};

		unsigned int indeces[] =
		{
			0, 1, 2,
			2, 3, 0
		};

		m_VAO = std::make_unique<VertexArray>();
		m_VBO = std::make_unique<VertexBuffer>(vertices, 4 * 4 * sizeof(float));
		m_IBO = std::make_unique<IndexBuffer>(indeces, 2 * 3);

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		m_VAO->AddBuffer(*m_VBO, layout);

		m_Shader = std::make_unique<Shader>("F:/GitHub/RxoGL/RxoGL-core/res/shaders/basic.vert", "F:/GitHub/RxoGL/RxoGL-core/res/shaders/basic.frag");
		m_Shader->Bind();
		m_Texture = std::make_unique<Texture>("F:/GitHub/RxoGL/RxoGL-core/res/textures/OverwatchLogo.png");
		m_Shader->SetUniform1i("u_Texture", 0); // slot 0 because the previous bind used the default
	}

	TestTexture2D::~TestTexture2D()
	{
	}

	void TestTexture2D::OnUpdate(float deltaTime)
	{
	}

	void TestTexture2D::OnRender()
	{
		Renderer renderer;
		m_Shader->Bind();
		m_Texture->Bind();
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
		}
		
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
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
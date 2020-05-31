#include "TestTexture2D.h"
#include "../ConstantsRxogl.h"
#include <array>

namespace tests
{

	static std::array<constants::Vertex, 4> CreateQuad(float x, float y, float texID)
	{
		float size = 100.f;

		constants::Vertex v0, v1, v2, v3;
		v0.Position = glm::vec3(x, y, 0.f);
		v0.Color = glm::vec4(0.609f, 0.115f, 0.436f, 1);
		v0.TexCoords = glm::vec2(0.0f, 0.0f);
		v0.TexIndex = texID;

		v1.Position = glm::vec3(x + size, y, 0.f);
		v1.Color = glm::vec4(0.609f, 0.115f, 0.436f, 1);
		v1.TexCoords = glm::vec2(1.0f, 0.0f);
		v1.TexIndex = texID;

		v2.Position = glm::vec3(x + size, y + size, 0.f);
		v2.Color = glm::vec4(0.609f, 0.115f, 0.436f, 1);
		v2.TexCoords = glm::vec2(1.0f, 1.0f);
		v2.TexIndex = texID;

		v3.Position = glm::vec3(x, y + size, 0.f);
		v3.Color = glm::vec4(0.609f, 0.115f, 0.436f, 1);
		v3.TexCoords = glm::vec2(0.0f, 1.0f);
		v3.TexIndex = texID;

		return { v0, v1, v2, v3 };
	}

	TestTexture2D::TestTexture2D()
		: 
		m_TranslationA(glm::vec3(200, 200, 0)), m_TranslationB(glm::vec3(400, 200, 0)),
		m_Proj(glm::ortho(0.f, 960.f, 0.f, 540.f, -1.0f, 1.0f)), 
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(/*-10*/0, 0, 0)))
	{
		//static const float vertices[] =
		//{
		//	-50.f, -50.f, 0.0f, 0.583f, 0.771f, 0.014f, 1, 0.0f, 0.0f, 0.0f,
		//	 50.f, -50.f, 0.0f, 0.609f, 0.115f, 0.436f, 1, 1.0f, 0.0f, 0.0f,
		//	 50.f,  50.f, 0.0f, 0.327f, 0.483f, 0.844f, 1, 1.0f, 1.0f, 0.0f,
		//	-50.f,  50.f, 0.0f, 0.822f, 0.569f, 0.201f, 1, 0.0f, 1.0f, 0.0f,
		//
		//	100.f, -50.f, 0.0f, 0.435f, 0.602f, 0.223f, 1, 0.0f, 0.0f, 1.0f,
		//	200.f, -50.f, 0.0f, 0.310f, 0.747f, 0.185f, 1, 1.0f, 0.0f, 1.0f,
		//	200.f,  50.f, 0.0f, 0.597f, 0.770f, 0.761f, 1, 1.0f, 1.0f, 1.0f,
		//	100.f,  50.f, 0.0f, 0.559f, 0.436f, 0.730f, 1, 0.0f, 1.0f, 1.0f
		//};

		//auto q0 = CreateQuad(-50.f, -50.f, 0.0f);
		//auto q1 = CreateQuad(100.f, -50.f, 1.0f);

		//constants::Vertex vertices[100];
		//memcpy(vertices, q0.data(), q0.size() * sizeof(constants::Vertex));
		//memcpy(vertices + q0.size(), q1.data(), q1.size() * sizeof(constants::Vertex));

		//unsigned int indeces[] =
		//{
		//	0, 1, 2,
		//	2, 3, 0,
		//
		//	4, 5, 6,
		//	6, 7, 4,
		//};
		const size_t MaxQuadCount = 1000;
		const size_t MaxVertCount = MaxQuadCount * 4;
		const size_t MaxIndexCount = MaxQuadCount * 6;

		unsigned int indeces[MaxIndexCount];
		unsigned int offset = 0;
		for (size_t i = 0; i < MaxIndexCount; i+=6)
		{
			indeces[i + 0] = 0 + offset;
			indeces[i + 1] = 1 + offset;
			indeces[i + 2] = 2 + offset;

			indeces[i + 3] = 2 + offset;
			indeces[i + 4] = 3 + offset;
			indeces[i + 5] = 0 + offset;

			offset += 4;
		}


		m_VAO = std::make_unique<rxogl::VertexArray>();
		//m_VBO = std::make_unique<rxogl::VertexBuffer>(vertices, sizeof(vertices));
		m_VBO = std::make_unique<rxogl::VertexBuffer>(sizeof(vertices));
		m_IBO = std::make_unique<rxogl::IndexBuffer>(indeces, MaxIndexCount);

		rxogl::BufferLayout layout;
		layout.Push<glm::vec3>(1); // vec3 Pos
		layout.Push<glm::vec4>(1); // vec4 Color
		layout.Push<glm::vec2>(1); // Texture
		layout.Push<float>(1); // Texture ID
		m_VAO->AddBuffer(*m_VBO, layout);

		m_Shader = std::make_unique<Shader>("res/shaders/basic.vert", "res/shaders/basic.frag");
		m_Shader->Bind();
		m_OWTexture = std::make_unique<rxogl::Texture>("res/textures/OverwatchLogo.png");
		m_YTTexture = std::make_unique<rxogl::Texture>("res/textures/youtube.png");
		m_OWTexture->Bind();
		m_YTTexture->Bind(1);
	}

	TestTexture2D::~TestTexture2D()
	{
	}

	void TestTexture2D::OnUpdate(float deltaTime)
	{
		//auto q0 = CreateQuad(-50.f, -50.f, 0.0f);
		//auto q1 = CreateQuad(100.f, -50.f, 1.0f);
		//memcpy(vertices, q0.data(), q0.size() * sizeof(constants::Vertex));
		//memcpy(vertices + q0.size(), q1.data(), q1.size() * sizeof(constants::Vertex));

		//std::array<constants::Vertex, 4> prev;
		//int count = 0;
		//for (float y = -50.f; y < 250.f; y += 100.f)
		//{
		//	for (float x = -50.f; x < 250.f; x += 100.f)
		//	{
		//		float tex = 0.f;
		//		if (count % 2 != 0)
		//			tex = 1.f;
		//		auto quad = CreateQuad(x, y, tex);
		//		if(count = 0)
		//			memcpy(vertices, quad.data(), quad.size() * sizeof(constants::Vertex));
		//		else
		//			memcpy(vertices + prev.size(), prev.data(), prev.size() * sizeof(constants::Vertex));
		//
		//		prev = quad;
		//
		//		count++;
		//		m_IndexCount += 6;
		//	}
		//}
		int vertexCount = 0;
		for (float y = -50.f; y < 250.f; y += 100.f)
		{
			for (float x = -50.f; x < 250.f; x += 100.f)
			{
				float tex = 0.f;
				if (vertexCount % 8 == 0)
					tex = 1.f;
				auto quad = CreateQuad(x, y, tex);
				vertices[vertexCount]	  = quad[0];
				vertices[vertexCount + 1] = quad[1];
				vertices[vertexCount + 2] = quad[2];
				vertices[vertexCount + 3] = quad[3];

				vertexCount += 4;
			}
		}

		m_VBO->SetData(vertices, sizeof(vertices));

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
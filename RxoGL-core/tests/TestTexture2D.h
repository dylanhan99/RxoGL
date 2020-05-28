#pragma once
#include "Test.h"

#include "../vendor/imgui/imgui.h"

#include "../VertexArray.h"
#include "../Texture.h"
#include "../Buffer.h"
#include "../graphics/shader.h"

#include <memory>

namespace tests
{
	class TestTexture2D : public Test
	{
	private:
		glm::vec3 m_TranslationA, m_TranslationB;
		glm::mat4 m_Proj, m_View;
		std::unique_ptr<rxogl::VertexArray> m_VAO;
		std::unique_ptr<rxogl::VertexBuffer> m_VBO;
		std::unique_ptr<rxogl::IndexBuffer> m_IBO;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<rxogl::Texture> m_OWTexture, m_YTTexture;
	public:
		TestTexture2D();
		~TestTexture2D();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImguiRender() override;
	};
}
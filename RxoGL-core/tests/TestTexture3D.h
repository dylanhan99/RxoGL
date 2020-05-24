#pragma once
#include "Test.h"

#include "../vendor/imgui/imgui.h"
#include "../VertexArray.h"
#include "../VertexBufferLayout.h"
#include "../IndexBuffer.h"
#include "../Texture.h"

#include <memory>

namespace tests
{
	class TestTexture3D : public Test
	{
	private:
		float x, y, z;

		glm::vec3 m_TranslationA, m_TranslationCam;
		glm::mat4 m_Proj, m_View;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<VertexBuffer> m_ColBO;
		std::unique_ptr<IndexBuffer> m_IBO;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;
	public:
		TestTexture3D();
		~TestTexture3D();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImguiRender() override;
	};
}
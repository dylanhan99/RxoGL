#pragma once
#include "Test.h"

#include <map>

#include "../graphics/renderers/BatchRenderer2D.h"

namespace tests
{
	struct Character {
		unsigned int TextureID;  // ID handle of the glyph texture
		glm::ivec2   Size;       // Size of glyph
		glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
		unsigned int Advance;    // Offset to advance to next glyph
	};

	class TestTextRender : public Test
	{
	private:
		std::map<char, Character> Characters;
		Shader* m_Shader;
		unsigned int VAO, VBO;
		glm::vec3 m_TranslationA;
		
		void RenderText(Shader& s, std::string text, float x, float y, float scale, glm::vec3 color);
	public:
		TestTextRender();
		~TestTextRender();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImguiRender() override;

	};
}
#include "TestTextRender.h"
#include "../vendor/imgui/imgui.h"

namespace tests
{
	void TestTextRender::RenderText(Shader& s, std::string text, float x, float y, float scale, glm::vec3 color)
	{
		// activate corresponding render state	
		s.Bind();
		s.SetUniform3f("textColor", color.x, color.y, color.z);
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(VAO);

		// iterate through all characters
		std::string::const_iterator c = text.begin();
		for (c = text.begin(); c != text.end(); c++)
		{
			Character ch = Characters[*c];

			float xpos = x + ch.Bearing.x * scale;
			float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

			float w = ch.Size.x * scale;
			float h = ch.Size.y * scale;
			// update VBO for each character
			float vertices[6][4] = {
				{ xpos,     ypos + h,   0.0f, 0.0f },
				{ xpos,     ypos,       0.0f, 1.0f },
				{ xpos + w, ypos,       1.0f, 1.0f },

				{ xpos,     ypos + h,   0.0f, 0.0f },
				{ xpos + w, ypos,       1.0f, 1.0f },
				{ xpos + w, ypos + h,   1.0f, 0.0f }
			};
			// render glyph texture over quad
			glBindTexture(GL_TEXTURE_2D, ch.TextureID);
			// update content of VBO memory
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			// render quad
			glDrawArrays(GL_TRIANGLES, 0, 6);
			// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
		}
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TestTextRender::TestTextRender()
		: m_TranslationA(200.f, 200.f, 0)
	{
		//GLCall(glClearColor(0, 0, 0, 1));
		//GLCall(glClear(GL_COLOR_BUFFER_BIT));


		m_Shader = new Shader("res/shaders/text.vert", "res/shaders/text.frag");
		m_Shader->Bind();
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		{
			FT_Library lib;
			if(FT_Init_FreeType(&lib))
				std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
			FT_Face face;
			if (FT_New_Face(lib, "res/fonts/arial.ttf", 0, &face))
				std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
			FT_Set_Pixel_Sizes(face, 0, 400);
			//FTCall(FT_Load_Char(face, 'X', FT_LOAD_RENDER));

			glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

			for (unsigned char c = 0; c < 128; c++)
			{
				// load character glyph 
				if (FT_Load_Char(face, c, FT_LOAD_RENDER))
				{
					std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
					continue;
				}
				// generate texture
				unsigned int texture;
				glGenTextures(1, &texture);
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexImage2D(
					GL_TEXTURE_2D,
					0,
					GL_RED,
					face->glyph->bitmap.width,
					face->glyph->bitmap.rows,
					0,
					GL_RED,
					GL_UNSIGNED_BYTE,
					face->glyph->bitmap.buffer
				);
				// set texture options
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				// now store character for later use
				Character character = {
					texture,
					glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
					glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
					face->glyph->advance.x
				};
				Characters.insert(std::pair<char, Character>(c, character));
			}
		}
	}	
	
	TestTextRender::~TestTextRender()
	{
		//FT_Done_Face(face);
		//FT_Done_FreeType(lib);
	}

	void TestTextRender::OnUpdate(float deltaTime)
	{
		int texIDs[2] = { 0, 1 };
		m_Shader->SetUniform1iv("text", 1, texIDs);
	}

	void TestTextRender::OnRender()
	{
		m_Shader->Bind();
		glm::mat4 proj = glm::ortho(0.f, 960.f, 0.f, 540.f, -1.0f, 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);

		glm::mat4 mvp = proj * view * model; // This should be handled in Layer. See comment in layer.cpp
		m_Shader->SetUniformMat4f("u_MVP", mvp);

		RenderText(*m_Shader, "OpenGL Text Test fReeeTypeee", m_TranslationA.x, m_TranslationA.y, 1.0f, glm::vec3(1.f, 1.f, 1.f));
		//RenderText(*m_Shader, "(C) LearnOpenGL.com", 540.0f, 570.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));

	}

	void TestTextRender::OnImguiRender()
	{
		ImGui::SliderFloat3("Layer1", &m_TranslationA.x, 0.0f, 960.0f);
	}
}
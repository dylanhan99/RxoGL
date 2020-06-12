#pragma once
#include "Renderable2D.h"

namespace rxogl
{
	class StaticSprite : public Renderable2D
	{
	private:
		VertexArray* m_VAO;
		VertexBuffer* m_VBO;
		IndexBuffer* m_IBO;
		Shader& m_Shader;
	public:
		StaticSprite(float x, float y, float z, float width, float height, glm::vec4 color, Shader& shader);
		//StaticSprite(glm::vec3 position, glm::vec2 size, glm::vec4 color, Shader& shader);
		~StaticSprite();

		inline const VertexArray* GetVAO() const { return m_VAO; }
		inline const IndexBuffer* GetIBO() const { return m_IBO; }

		inline Shader& GetShader() const { return m_Shader; }
	};
}
#pragma once
#include "Test.h"

#include <vector>
#include "../BatchRenderer2D.h"
#include "../StaticSprite.h"
#include "../Sprite.h"

namespace tests
{
	class TestSimpleBatchRenderer2D : public Test
	{
	private:
		Shader* m_Shader;
		std::vector<rxogl::Renderable2D*> sprites;

	public:
		TestSimpleBatchRenderer2D();
		~TestSimpleBatchRenderer2D();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImguiRender() override;

	};
}
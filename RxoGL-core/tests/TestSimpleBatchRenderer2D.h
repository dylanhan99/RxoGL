#pragma once
#include "Test.h"

#include "../BatchRenderer2D.h"
#include "../StaticSprite.h"
#include "../Sprite.h"

namespace tests
{
	class TestSimpleBatchRenderer2D : public Test
	{
	private:
		Shader* m_Shader;
		rxogl::Sprite* sprite;
		rxogl::Sprite* sprite2;

	public:
		TestSimpleBatchRenderer2D();
		~TestSimpleBatchRenderer2D();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImguiRender() override;

	};
}
#pragma once
#include "Test.h"

#include "../SimpleRenderer2D.h"
#include "../Renderable2D.h"

namespace tests
{
	class TestSimpleRenderer2D : public Test
	{
	private:
		Shader* m_Shader;

		rxogl::StaticSprite* sprite;
		rxogl::StaticSprite* sprite2;

		std::vector<rxogl::Renderable2D*> sprites;

	public:
		TestSimpleRenderer2D();
		~TestSimpleRenderer2D();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImguiRender() override;

	};
}
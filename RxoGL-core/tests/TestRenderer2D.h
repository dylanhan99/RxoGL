#pragma once
#include "Test.h"

#include "../SimpleRenderer2D.h"
#include "../Renderable2D.h"

namespace tests
{
	class TestRenderer2D : public Test
	{
	private:
		Shader* m_Shader;

		//std::unique_ptr <rxogl::Renderable2D> sprite;
		rxogl::Renderable2D* sprite;
		rxogl::Renderable2D* sprite2;
	public:
		TestRenderer2D();
		~TestRenderer2D();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImguiRender() override;

	};
}
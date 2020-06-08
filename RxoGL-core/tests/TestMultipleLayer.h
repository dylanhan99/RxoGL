#pragma once
#include "Test.h"

#include <vector>
#include "../graphics/BatchRenderer2D.h"
#include "../graphics/StaticSprite.h"
#include "../graphics/Sprite.h"

#include "../graphics/layers/TileLayer.h"

namespace tests
{
	class TestMultipleLayer : public Test
	{
	private:
		Shader* m_Shader1;
		Shader* m_Shader2;
		std::vector<rxogl::Renderable2D*> sprites;

		rxogl::TileLayer* layer1;
		rxogl::TileLayer* layer2;

	public:
		TestMultipleLayer();
		~TestMultipleLayer();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImguiRender() override;

	};
}
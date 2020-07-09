#pragma once
#include "Test.h"

#include <vector>
#include "../graphics/renderers/BatchRenderer2D.h"
#include "../graphics/renderables/StaticSprite.h"
#include "../graphics/renderables/Sprite.h"
#include "../graphics/renderables/Label.h"

#include "../graphics/layers/TileLayer.h"
#include "../graphics/layers/UILayer.h"
#include "../graphics/layers/Group.h"
#include "../graphics/textures/TextureSheet.h"

namespace tests
{
	class TestSceneryLayers : public Test
	{
	private:

	public:
		TestSceneryLayers();
		~TestSceneryLayers();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImguiRender() override;
	};
}
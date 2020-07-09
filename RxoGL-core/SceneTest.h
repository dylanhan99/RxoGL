#pragma once
#include "Scene.h"

namespace rxogl { namespace scenes {

	class SceneTest : public Scene
	{
	public:
		SceneTest();
		~SceneTest() override;

		void OnUpdate(float deltatime) override;
		void OnRender() override;
		void OnImguiRender() override;
	};

} }
#include "SceneTest.h"

namespace rxogl { namespace scenes {
	SceneTest::SceneTest()
	{

	}

	SceneTest::~SceneTest()
	{
		Scene::~Scene();
	}

	void SceneTest::OnUpdate(float deltatime)
	{

	}

	void SceneTest::OnRender()
	{
		// Update scene variables before rendering layers ^^^

		Scene::OnRender();
	}

	void SceneTest::OnImguiRender()
	{

	}

} }
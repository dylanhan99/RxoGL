#include "Scene.h"
#include "vendor/imgui/imgui.h"

namespace rxogl { namespace scenes {
	SceneMenu::SceneMenu(Scene*& currentScenePointer)
		: m_CurrentScene(currentScenePointer)
	{

	}

	SceneMenu::~SceneMenu()
	{
		for (auto& test : m_Scenes)
			delete test.second();
	}

	void SceneMenu::OnImguiRender()
	{
		for (auto& test : m_Scenes)
		{
			if (ImGui::Button(test.first.c_str()))
				m_CurrentScene = test.second();
		}
	}
} }
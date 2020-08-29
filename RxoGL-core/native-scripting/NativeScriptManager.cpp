#include "NativeScriptManager.h"
#include "../ecs/ECS.h"

namespace rxogl
{
	NativeScriptManager*  NativeScriptManager::m_Instance = nullptr;
	NativeScriptManager::NativeScriptManager()
	{
		for (auto& nsc : m_NativeScripts)
		{
			nsc->InstantiateFunction();
			nsc->OnCreateFunction();
		}
	}

	void NativeScriptManager::Init()
	{
		for (auto& nsc : m_NativeScripts)
		{
			nsc->InstantiateFunction();
			nsc->OnCreateFunction();
		}
	}

	void NativeScriptManager::Update(float deltatime)
	{
		for (auto& nsc : m_NativeScripts)
			nsc->OnUpdateFunction(deltatime);
	}
}
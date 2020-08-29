#pragma once

#include <vector>
#include <memory>

//#include "../ecs/ECS.h"

namespace rxogl
{
	namespace ecs { class NativeScriptComponent; }

	class NativeScriptManager
	{
	private:
		static NativeScriptManager* m_Instance; // Singleton

		std::vector<std::shared_ptr<ecs::NativeScriptComponent>> m_NativeScripts;
	public:
		NativeScriptManager();
		
		void Init();
		void Update(float deltatime);
		
		void AddScript(std::shared_ptr<ecs::NativeScriptComponent>sPtr)
		{ m_NativeScripts.push_back(sPtr); }

		static NativeScriptManager* GetInstance()
		{
			if (m_Instance == NULL)
				m_Instance = new NativeScriptManager();

			return m_Instance;
		}

		static void DeleteInstance()
		{
			if (m_Instance)
			{
				delete m_Instance;
				m_Instance = NULL;
			}
		}
	};
}
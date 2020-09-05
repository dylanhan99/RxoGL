#pragma once
#include "rxogl.h"
#include "ecs/ECS.h"

namespace Game { namespace Script {

	class PlayerControlScript : public rxogl::ecs::NativeScript
	{
	public:
		void OnCreate() override { std::cout << "PlayerControlScript Created...\n"; }
		void OnDestroy()override { std::cout << "PlayerControlScript Destroyed...\n"; }
		void OnUpdate(float deltatime) override
		{
			const Window& window = rxogl::Application::GetInstance()->GetWindow();
			auto transform = m_Entity->GetComponent<rxogl::ecs::Transform>();
			if (window.IsKeyPressed(GLFW_KEY_D))
			{
				transform->SetPos(transform->x() + 40.0f * deltatime, transform->y(), transform->z());
			}
			else if (window.IsKeyPressed(GLFW_KEY_A))
			{
				transform->SetPos(transform->x() - 40.0f * deltatime, transform->y(), transform->z());
			}

			if (window.IsKeyPressed(GLFW_KEY_S))
			{
				transform->SetPos(transform->x(), transform->y() - 40.0f * deltatime, transform->z());
			}
			else if (window.IsKeyPressed(GLFW_KEY_W))
			{
				transform->SetPos(transform->x(), transform->y() + 40.0f * deltatime, transform->z());
			}

		}
	};

} }
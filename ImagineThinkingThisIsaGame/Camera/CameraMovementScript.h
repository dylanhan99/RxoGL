#pragma once
#include "rxogl.h"
#include "ecs/ECS.h"

namespace Game { namespace Camera {

	class CameraMovementScript : public rxogl::ecs::NativeScript
	{
	private:
		rxogl::ecs::Transform& m_PlayerTransform;
		static float m_AspectRatio;
		static float m_ZoomLevel;
		static rxogl::CameraOrtho m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f; //In degrees, in the anti-clockwise direction
		float m_CameraTranslationSpeed = 40.0f, m_CameraRotationSpeed = 180.0f;

	public:
		CameraMovementScript(rxogl::ecs::Transform& playerTransform, float aspectRatio, bool rotation = false)
			: m_PlayerTransform(playerTransform), m_Rotation(rotation)
		{
			m_AspectRatio = aspectRatio;
			m_Camera = rxogl::CameraOrtho(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

			Events::EventDispatcher::GetInstance()->RegisterEvent(new Events::Event<float, float>(rxogl::constants::RX_EVENT_WINDOWRESIZE, &OnResize));
			Events::EventDispatcher::GetInstance()->RegisterEvent(new Events::Event<int, int>(rxogl::constants::RX_EVENT_SCROLLWHEEL, &OnMouseScrolled));
		}
		void OnCreate() override { std::cout << "CameraMovementScript Created...\n"; }
		void OnDestroy()override { std::cout << "CameraMovementScript Destroyed...\n"; }
		void OnUpdate(float deltatime) override
		{
			m_Camera.SetPosition(m_PlayerTransform.GetPosition());
			m_CameraTranslationSpeed = m_ZoomLevel;

			const glm::mat4& pv = m_Camera.GetProjectionViewMatrix();
			{
				m_Entity->m_Layer->GetShader()->Bind();
				glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3());
				glm::mat4 mvp = pv * model;
				m_Entity->m_Layer->GetShader()->SetUniformMat4f("u_MVP", mvp);
			}

		}
		static void OnResize(float width, float height)
		{
			m_AspectRatio = width / height;
			m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
			//m_Camera.SetProjection(0, 960, 0, 540);
		}
		static void OnMouseScrolled(int xOffset, int yOffset)
		{
			m_ZoomLevel -= yOffset * 5.f;
			m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
			m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
			//m_Camera.SetProjection(0, 960, 0, 540);
		}

		rxogl::CameraOrtho& GetCamera() { return m_Camera; }
		const rxogl::CameraOrtho& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }
	};

} }
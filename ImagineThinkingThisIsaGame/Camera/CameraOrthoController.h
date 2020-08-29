#pragma once
#include "rxogl.h"
#include "ecs/ECS.h"

namespace Game { namespace Camera {
	class CameraOrthoController : public rxogl::ecs::NativeScript
	{
	private:
		static float m_AspectRatio;
		static float m_ZoomLevel;
		static rxogl::CameraOrtho m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f; //In degrees, in the anti-clockwise direction
		float m_CameraTranslationSpeed = 40.0f, m_CameraRotationSpeed = 180.0f;
	public:
		CameraOrthoController(float aspectRatio, bool rotation = false);
		void OnCreate() override{ std::cout << "CameraOrthoController Created...\n"; }
		void OnDestroy()override{ std::cout << "CameraOrthoController Destroyed...\n"; }
		void OnUpdate(float deltatime) override;
		static void OnResize(float width, float height)
		{
			m_AspectRatio = width / height;
			m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		}
		static void OnMouseScrolled(int xOffset, int yOffset)
		{
			m_ZoomLevel -= yOffset * 5.f;
			//m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
			m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		}

		rxogl::CameraOrtho& GetCamera() { return m_Camera; }
		const rxogl::CameraOrtho& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }
	};
} }
#pragma once
#include "CameraOrtho.h"

namespace rxogl
{
	class CameraOrthoController
	{
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		CameraOrtho m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f; //In degrees, in the anti-clockwise direction
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
	public:
		CameraOrthoController(float aspectRatio, bool rotation = false);

		void OnUpdate(float deltatime);
		void OnResize(float width, float height);

		CameraOrtho& GetCamera() { return m_Camera; }
		const CameraOrtho& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }
	};
}
#include "CameraOrthoController.h"
#include "../Application.h"
#include "../Event.h"

namespace rxogl
{
	float CameraOrthoController::m_AspectRatio = NULL;
	float CameraOrthoController::m_ZoomLevel = 100.f;
	CameraOrtho CameraOrthoController::m_Camera = CameraOrtho();

	CameraOrthoController::CameraOrthoController(float aspectRatio, bool rotation)
		: m_Rotation(rotation)
	{
		m_AspectRatio = aspectRatio;
		m_Camera = CameraOrtho(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		Events::EventDispatcher::GetInstance()->RegisterEvent(new Events::Event<float, float>(rxogl::constants::RX_EVENT_WINDOWRESIZE, &OnResize));

	}

	void CameraOrthoController::OnUpdate(float deltatime)
	{
		const Window& window = Application::GetInstance()->GetWindow();
		
		if (window.IsKeyPressed(GLFW_KEY_D))
		{
			m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * deltatime;
			m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * deltatime;
		}
		else if (window.IsKeyPressed(GLFW_KEY_A))
		{
			m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * deltatime;
			m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * deltatime;
		}

		if (window.IsKeyPressed(GLFW_KEY_S))
		{
			m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * deltatime;
			m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * deltatime;
		}
		else if (window.IsKeyPressed(GLFW_KEY_W))
		{
			m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * deltatime;
			m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * deltatime;
		}

		if (m_Rotation)
		{
			if (window.IsKeyPressed(GLFW_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * deltatime;
			if (window.IsKeyPressed(GLFW_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * deltatime;

			if (m_CameraRotation > 180.0f)
				m_CameraRotation -= 360.0f;
			else if (m_CameraRotation <= -180.0f)
				m_CameraRotation += 360.0f;

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);
		m_CameraTranslationSpeed = m_ZoomLevel;
	}

	//void CameraOrthoController::OnResize(float width, float height)
	//{
	//	m_AspectRatio = width / height;
	//	m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	//}

	//bool CameraOrthoController::OnMouseScrolled(MouseScrolledEvent& e)
	//{

	//	m_ZoomLevel -= e.GetYOffset() * 0.25f;
	//	m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
	//	m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	//	return false;
	//}

	//bool CameraOrthoController::OnWindowResized(WindowResizeEvent& e)
	//{

	//	OnResize((float)e.GetWidth(), (float)e.GetHeight());
	//	return false;
	//}
}
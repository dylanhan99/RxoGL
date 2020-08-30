#include "CameraOrthoController.h"
#include "ConstantsRxogl.h"

namespace Game { namespace Camera {

	float				CameraOrthoController::m_AspectRatio = NULL;
	float				CameraOrthoController::m_ZoomLevel = 100.f;
	rxogl::CameraOrtho	CameraOrthoController::m_Camera = rxogl::CameraOrtho();

	CameraOrthoController::CameraOrthoController(float aspectRatio, bool rotation)
		: m_Rotation(rotation)
	{
		m_AspectRatio = aspectRatio;
		m_Camera = rxogl::CameraOrtho(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		Events::EventDispatcher::GetInstance()->RegisterEvent(new Events::Event<float, float>(rxogl::constants::RX_EVENT_WINDOWRESIZE, &OnResize));
		Events::EventDispatcher::GetInstance()->RegisterEvent(new Events::Event<int, int>(rxogl::constants::RX_EVENT_SCROLLWHEEL, &OnMouseScrolled));
	}

	void CameraOrthoController::OnUpdate(float deltatime)
	{
		//std::cout << "CameraOrthoController Updating...\n";
		const Window& window = rxogl::Application::GetInstance()->GetWindow();

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
			else if (m_CameraRotation <= -	180.0f)
				m_CameraRotation += 360.0f;

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);
		m_CameraTranslationSpeed = m_ZoomLevel;

		const glm::mat4& pv = m_Camera.GetProjectionViewMatrix();
		{
			m_Entity->m_Layer->GetShader()->Bind();
			glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3());
			glm::mat4 mvp = pv * model;
			m_Entity->m_Layer->GetShader()->SetUniformMat4f("u_MVP", mvp);
		}
	}
} }
#include "CameraOrtho.h"

#include "../Application.h"

namespace rxogl
{
	CameraOrtho::CameraOrtho(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), 
		m_ViewMatrix(1.0f)
	{
		m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;

		//m_Application = Application::GetInstance();
		//m_Window = &m_Application->GetWindow();
	}

	CameraOrtho::~CameraOrtho()
	{

	}

	void CameraOrtho::SetProjection(float left, float right, float bottom, float top)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.f, 1.f);
		m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void CameraOrtho::CalcViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.f), m_Position) * 
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		m_ViewMatrix = glm::inverse(transform);
		m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}
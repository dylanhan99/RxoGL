#pragma once

#include "../ConstantsRxogl.h"
#include <glm/ext.hpp>

namespace rxogl
{
	class CameraOrtho
	{
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionViewMatrix;

		glm::vec3 m_Position = { 0, 0, 0 };
		float m_Rotation = 0.f; // In degrees
	public:
		CameraOrtho(float left, float right, float bottom, float top);
		~CameraOrtho();

		const glm::mat4& GetProjectionMatrix()		const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix()			const { return m_ViewMatrix; }
		const glm::mat4& GetProjectionViewMatrix()	const { return m_ProjectionViewMatrix; }
		
		void SetProjection(float left, float right, float bottom, float top);
		void RecalcViewMatrix();
	};
}
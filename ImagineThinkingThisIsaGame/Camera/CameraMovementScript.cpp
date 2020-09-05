#include "CameraMovementScript.h"
#include "ConstantsRxogl.h"

namespace Game { namespace Camera {

		float				CameraMovementScript::m_AspectRatio = NULL;
		float				CameraMovementScript::m_ZoomLevel = 100.f;
		rxogl::CameraOrtho	CameraMovementScript::m_Camera = rxogl::CameraOrtho();

} }
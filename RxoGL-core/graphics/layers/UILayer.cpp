#include "UILayer.h"
#include "../renderers/BatchRenderer2D.h"
#include "../Font.h"
namespace rxogl
{
	UILayer::UILayer(Shader* shader)
		: Layer(new BatchRenderer2D(), shader, glm::ortho(0.f, 960.f, 0.f, 540.f, -200.0f, 200.0f))
	{

	}

	UILayer::~UILayer()
	{

	}
}
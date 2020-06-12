#include "TileLayer.h"
#include "../renderers/BatchRenderer2D.h"

namespace rxogl
{
	TileLayer::TileLayer(Shader* shader)
		: Layer(new BatchRenderer2D(), shader, glm::ortho(0.f, 960.f, 0.f, 540.f, -200.0f, 200.0f))
	{

	}

	TileLayer::~TileLayer()
	{

	}
}
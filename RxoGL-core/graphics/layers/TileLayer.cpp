#include "TileLayer.h"
#include "../BatchRenderer2D.h"

namespace rxogl
{
	TileLayer::TileLayer(Shader* shader)
		: Layer(new BatchRenderer2D(), shader, glm::ortho(0.f, 960.f, 0.f, 540.f, -1.0f, 1.0f))
	{

	}

	TileLayer::~TileLayer()
	{

	}
}
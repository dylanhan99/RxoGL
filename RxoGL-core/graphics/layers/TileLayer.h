#pragma once

#include "Layer.h"

namespace rxogl
{
	class TileLayer : public Layer
	{
	public:
		TileLayer(Shader* shader);
		~TileLayer();
	};
}
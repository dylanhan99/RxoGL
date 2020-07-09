#pragma once
#pragma once

#include "Layer.h"

namespace rxogl
{
	class UILayer : public Layer
	{
	public:
		UILayer(Shader* shader);
		~UILayer();
	};
}
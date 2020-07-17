#pragma once
#include "graphics/layers/Layer.h"

class UILayer : public rxogl::Layer
{
public:
	UILayer(Shader* shader);
	~UILayer();
};
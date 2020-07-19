#pragma once
#include "graphics/layers/Layer.h"

namespace Game { namespace Layers {

class UILayer : public rxogl::Layer
{
public:
	UILayer(Shader* shader);
	~UILayer();
};

}}
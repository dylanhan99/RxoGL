#include "UILayer.h"
#include "rxogl.h"

namespace Game { namespace Layers {

UILayer::UILayer(Shader* shader)
	: Layer(new rxogl::BatchRenderer2D(), shader, glm::ortho(0.f, 960.f, 0.f, 540.f, -200.0f, 200.0f))
{

}

UILayer::~UILayer()
{

}

} }
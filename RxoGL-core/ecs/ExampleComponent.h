#pragma once
#include "ECS.h"

namespace rxogl { namespace ecs {

	class PositionComponent : public Component
	{
	private:
		int xpos;
		int ypos;
	public:
		int x() { return xpos; }
		int y() { return ypos; }

		void Init() override
		{
			xpos = 0;
			ypos = 0;
		}

		void Update() override
		{
			xpos++;
			ypos++;
		}

		void SetPos(int x, int y)
		{
			xpos = x;
			ypos = y;
		}
	};
} }
#pragma once
#include <glm/glm.hpp>;

namespace constants {

	enum Type {
		t_Uint = sizeof(GL_UNSIGNED_INT),
		t_Float = sizeof(GL_FLOAT),
		t_Vec2 = sizeof(glm::vec2),
		t_Vec3 = sizeof(glm::vec3),
		t_Vec4 = sizeof(glm::vec4),
	};

	//enum Count
	//{
	//	c_Vec2 = 2,
	//	c_Vec3 = 3,
	//	c_Vec4 = 4
	//};

	struct Vertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoords;
		float TexIndex;
	};
}
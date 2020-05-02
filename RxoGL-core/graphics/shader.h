#pragma once

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include "../utils/fileutils.h"

#include <glm/glm.hpp>;
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace rxogl { namespace graphics {

	class Shader
	{
	public:
		int x, y, z;
	private:
		GLuint m_ShaderID;
		const char* m_VertPath;
		const char* m_FragPath;

	public:
		Shader(const char* vertPath, const char* fragPath);
		~Shader();

		void enable() const;
		void disable() const;

		void mathStuff() const;
	private:
		GLuint load();
	};

} }
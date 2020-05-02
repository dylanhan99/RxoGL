#include "shader.h"

namespace rxogl { namespace graphics {

	Shader::Shader(const char* vertPath, const char* fragPath)
		: m_VertPath(vertPath), m_FragPath(fragPath)
	{
		x = 0;
		y = 0;
		z = 3;

		m_ShaderID = load();
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_ShaderID);
	}

	GLuint Shader::load()
	{
		GLuint program = glCreateProgram();
		GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

		std::string vertSourceStr = utils::FileUtils::read_file(m_VertPath);
		std::string fragSourceStr = utils::FileUtils::read_file(m_FragPath);

		const char* vertSource = vertSourceStr.c_str();
		const char* fragSource = fragSourceStr.c_str();

		glShaderSource(vertex, 1, &vertSource, NULL);
		glCompileShader(vertex);

		GLint result;
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);

		if (result == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(vertex, length, &length, &error[0]);
			std::cout << "Failed to compile vertex shader!" << std::endl <<
				&error[0] << std::endl;
			glDeleteShader(vertex);

			return 0;
		}

		glShaderSource(fragment, 1, &fragSource, NULL);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);

		if (result == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(fragment, length, &length, &error[0]);
			std::cout << "Failed to compile fragment shader!" << std::endl << 
				&error[0] << std::endl;
			glDeleteShader(fragment);

			return 0;
		}

		glAttachShader(program, vertex);
		glAttachShader(program, fragment);

		glLinkProgram(program);
		glValidateProgram(program);
		
		glDeleteShader(vertex);
		glDeleteShader(fragment);

		return program;
	}

	void Shader::enable() const
	{
		glUseProgram(m_ShaderID);
	}

	void Shader::disable() const
	{
		glUseProgram(0);
	}

	void Shader::mathStuff() const
	{
		std::cout << x << " " << y << " " << z << " " << std::endl;
		// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
		glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)960 / (float)540, 0.1f, 100.0f);
		// Camera matrix
		glm::mat4 View = glm::lookAt(
			//glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
			//glm::vec3(0, 0, 0), // and looks at the origin
			//glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
			glm::vec3(x, y, z), // Camera is at (4,3,3), in World Space
			glm::vec3(0, 0, 0), // and looks at the origin
			glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
		// Model matrix : an identity matrix (model will be at the origin)
		glm::mat4 Model = glm::mat4(1.0f);
		// Our ModelViewProjection : multiplication of our 3 matrices
		glm::mat4 mvp = Projection * View * Model; // Remember, matrix multiplication is the other way around

												   // Get a handle for our "MVP" uniform
		// Only during the initialisation
		GLuint MatrixID = glGetUniformLocation(m_ShaderID, "MVP");

		// Send our transformation to the currently bound shader, in the "MVP" uniform
		// This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
	}
} }
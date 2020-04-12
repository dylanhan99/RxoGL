#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace rxogl { namespace graphics {

	class Window
	{
	private:
		const char* m_Title;
		int m_Width, m_Height;
		GLFWwindow* m_Window;

		bool m_Closed;
	public:
		Window(const char* title, int width, int height);
		~Window();

		void clear() const;
		void update();
		bool closed() const;

		inline int getWidth() { return m_Width; }
		inline int getHeight() { return m_Height; }

	private:
		bool init();

	};
}}
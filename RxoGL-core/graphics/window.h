#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define MAX_KEYS	1024
#define MAX_BUTTONS 32

class Window
{
private:
	std::string m_Title;
	int m_Width, m_Height;
	GLFWwindow* m_Window;

	bool m_Closed;
	bool m_Minimized = false;

	bool m_Keys[MAX_KEYS];
	bool m_MouseButtons[MAX_BUTTONS];
	double mx, my;

private:
	bool init();
	friend static void window_resize_callback(GLFWwindow* window, int width, int height);
	friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	friend static void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);
	friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

public:
	Window() {}
	Window(std::string title, int& width, int& height);
	~Window();

	void Update() const;
	bool Closed() const;

	inline const int&	getWidth()		const	{ return m_Width; }
	inline const int&	getHeight()		const	{ return m_Height; }
	inline GLFWwindow*	GetWindow()				{ return m_Window; }
	inline bool			IsMinimized()	const	{ return m_Minimized; }

	bool IsKeyPressed			(unsigned int keycode)	const;
	bool IsMouseButtonPressed	(unsigned int button)	const;
	void GetMousePosition		(double& x, double& y)	const;
	void SetViewPort(int& width, int& height);
};
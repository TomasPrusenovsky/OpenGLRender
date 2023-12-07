#pragma once
#include <GLFW/glfw3.h>
#include <iostream>


class Window
{
public:
	Window(uint32_t width, uint32_t height, const char* title);
	~Window();

	void Update();
	void SwapBuffers();
	void SetVSync(bool enabled);
	bool IsRunning() const { return m_Settings.shouldRun; }
	uint32_t Width() const { return m_Settings.width; }
	uint32_t Height() const { return m_Settings.height; }

private:
	struct Settings
	{
		uint32_t width;
		uint32_t height;
		const char* title;
		int openGL_major;
		int openGL_minor;
		bool VSync = true;
		bool shouldRun = true;
		bool isMinimized = false;
	};

	Settings m_Settings;

	void Init();
	void CreateWindow();
	void SetCallBacks();
	GLFWwindow* m_Window;

};
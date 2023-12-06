#include "Window.h"
#include <cassert>


Window::Window(uint32_t width, uint32_t height, const char* title) :
	m_Settings({width, height, title, 4, 6})
{
	Init();
	CreateWindow();
	SetCallBacks();
}

Window::~Window()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void Window::Update()
{
	glfwPollEvents();
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(m_Window);
}

void Window::Init()
{
	bool success = glfwInit();
	assert(success); // TODO: add Error handle for Release with Error class

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_Settings.openGL_major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_Settings.openGL_minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Window::CreateWindow()
{
	m_Window = glfwCreateWindow(m_Settings.width, m_Settings.height, m_Settings.title, NULL, NULL);
	
	if (m_Window == NULL)
		std::cerr << "Failed to create Window" << std::endl;

	glfwMakeContextCurrent(m_Window);

	glfwMakeContextCurrent(m_Window);
	glfwSetWindowUserPointer(m_Window, &m_Settings);
}

void Window::SetCallBacks()
{
	glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			Settings& data = *(Settings*)glfwGetWindowUserPointer(window);
			data.shouldRun = false;
		});

	glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			Settings& data = *(Settings*)glfwGetWindowUserPointer(window);
			data.height = height;
			data.width = width;

			if (width < 1 && height < 1)
				data.isMinimized = true;
			else
				data.isMinimized = false;
		});
}

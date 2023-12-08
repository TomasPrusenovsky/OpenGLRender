#include "Window.h"
#include <cassert>
#include <string>


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
	m_Time.Update();

	m_Tick.tick = false;
	double delta = m_Time.curr - m_Tick.prevTime;
	

	if (delta > m_Tick.delay)
	{
		m_FPS = 1.0 / m_Time.delta;
		m_Tick.prevTime = m_Time.curr;
		m_Tick.tick = true;
	}

	glfwPollEvents();
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(m_Window);
	Update();
}

void Window::SetVSync(bool enabled)
{
	if (enabled)
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);

	m_Settings.VSync = enabled;
}

void Window::ShowFPS()
{
	if (IsTick())
	{
		std::string titleFPS = std::to_string(FPS()) + "FPS";
		std::string timeDiff = std::to_string(m_Time.delta) + "ms";
		SetTitle(m_Settings.title + " " + titleFPS + " " + timeDiff);
	}
}

void Window::SetTitle(const std::string& title)
{
	glfwSetWindowTitle(m_Window, title.c_str());
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
	m_Window = glfwCreateWindow(m_Settings.width, m_Settings.height, m_Settings.title.c_str(), NULL, NULL);
	
	if (m_Window == NULL)
		std::cerr << "Failed to create Window" << std::endl;

	glfwMakeContextCurrent(m_Window);
	SetVSync(true);
	glfwSetWindowUserPointer(m_Window, &m_Settings);
}

void Window::SetCallBacks()
{
	glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			Settings& data = *(Settings*)glfwGetWindowUserPointer(window);
			data.shouldRun = false;
		});

	glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
		{
			Settings& data = *(Settings*)glfwGetWindowUserPointer(window);
			data.mouse.posX = (float)xpos;
			data.mouse.posY = (float)ypos;
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

void Window::Time::Update()
{
	prev = curr;
	curr = glfwGetTime();
	delta = curr - prev;
}

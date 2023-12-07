#include "OpenGLRender.h"

using namespace std;

// TODO: OpenGL error check using modern stuff

int main()
{
	float vertices[] = {
		-0.5f,  0.5f,
		-0.5f, -0.5f,
		 0.5f,  0.5f,
		 0.5f, -0.5f
	};

	Window win{ 800, 800, "e" };
	opengl::Init();

	opengl::Shader shader{ "shaders/basic.vert", "shaders/basic.frag" };
	opengl::VBO VBO{vertices, sizeof(vertices)};
	opengl::VAO VAO{};
	VAO.SpecifyData(0, 2, 0);
	VAO.BindVertexBuffer(VBO, 0, 0, 2 * sizeof(float));


	while (win.IsRunning())
	{
		glViewport(0, 0, win.Width(), win.Height());
		opengl::ClearColor(0.1f, 0.1f, 0.3f);

		shader.Bind();
		VAO.Bind();
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 8);

		win.SwapBuffers();
	}

	cout << "Hello CMake." << endl;
	return 0;
}

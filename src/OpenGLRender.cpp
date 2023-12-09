#include "OpenGLRender.h"

using namespace std;
using color = glm::vec3;

struct Vertex
{
	glm::vec3 vertices;
	color color;
	glm::vec3 normal;
};


int main()
{
	glm::vec3 red{ 1.0f, 0.0f, 0.0f };
	glm::vec3 green{ 0.0f, 1.0f, 0.0f };
	glm::vec3 blue{ 0.0f, 0.0f, 1.0f };

	Vertex v1{ {-0.5f,  0.5f, -1.0f }, red };
	Vertex v2{ {-0.5f, -0.5f,  0.0f }, green };
	Vertex v3{ { 0.5f,  0.5f, -1.0f }, blue };
	Vertex v4{ { 0.5f, -0.5f,  0.0f }, red };


	float vertices[] = { 
		
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,    0.0f, -1.0f, 0.0f, // Bottom side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,    0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,    0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,    0.0f, -1.0f, 0.0f, // Bottom side

	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,   -0.8f, 0.5f,  0.0f, // Left Side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,   -0.8f, 0.5f,  0.0f, // Left Side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,   -0.8f, 0.5f,  0.0f, // Left Side

	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,    0.0f, 0.5f, -0.8f, // Non-facing side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,    0.0f, 0.5f, -0.8f, // Non-facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,    0.0f, 0.5f, -0.8f, // Non-facing side

	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,    0.8f, 0.5f,  0.0f, // Right side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,    0.8f, 0.5f,  0.0f, // Right side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,    0.8f, 0.5f,  0.0f, // Right side

	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,    0.0f, 0.5f,  0.8f, // Facing side
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,    0.0f, 0.5f,  0.8f, // Facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,    0.0f, 0.5f,  0.8f  // Facing side
	};

	GLuint indices[] =
	{
		0, 1, 2, // Bottom side
		0, 2, 3, // Bottom side
		4, 6, 5, // Left side
		7, 9, 8, // Non-facing side
		10, 12, 11, // Right side
		13, 15, 14 // Facing side
	};


	Window win{ 800, 800, "Hello window" };
	opengl::Init();

	opengl::Shader shader{ "shaders/basic.vert", "shaders/basic.frag" };
	opengl::VBO VBO{vertices, sizeof(vertices)};
	opengl::EBO EBO{ indices, sizeof(indices) };
	opengl::VAO VAO{};
	VAO.SpecifyData(0, 3, 0);
	VAO.SpecifyData(1, 3, sizeof(glm::vec3));
	VAO.SpecifyData(2, 3, sizeof(glm::vec3) * 2.0f);
	VAO.BindVertexBuffer(VBO, 0, 0, sizeof(Vertex));
	VAO.BindElementBuffer(EBO);

	glm::mat4 proj{ 1.0f };
	glm::mat4 view{ 1.0f };

	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));
	glEnable(GL_DEPTH_TEST);

	while (win.IsRunning())
	{	
		opengl::ClearColor(0.1f, 0.4f, 0.1f);
		proj = glm::perspective(glm::radians(45.0f), win.AspectRatio(), 0.1f, 100.0f);
		win.ShowFPS();
		glm::mat4 model{ 1.0f };
		model = glm::rotate(model, glm::radians((float)glfwGetTime() * 50.0f), glm::vec3(0.f, 1.f, 0.0f));
	
		opengl::Viewport(win.Width(), win.Height());(0.1f, 0.1f, 0.3f);

		shader.Bind();
		glm::vec2 lPos{ 1.0f };
		lPos.x *= 2.0f * win.MouseX() / (float)win.Height() - 1.0f;
		lPos.y *= 2.0f * win.MouseY() / (float)win.Width() - 1.0f;

		shader.uni3f("u_lightPos", lPos.x, lPos.y, -1.0f);
		shader.uni4mat("u_proj", glm::value_ptr(proj));
		shader.uni4mat("u_view", glm::value_ptr(view));
		shader.uni4mat("u_model", glm::value_ptr(model));
		VAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		win.SwapBuffers();
	}

	cout << "Hello CMake." << endl;
	return 0;
}

#include "Basic.h"
#include "Basic.h"

namespace opengl
{

	void ClearColor(float r, float g, float b)
	{
		ClearColor(r, g, b, 1.0f);
	}

	void ClearColor(float r, float g, float b, float a)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(r, g, b, a);
	}

	void Viewport(GLint x, GLint y, GLsizei width, GLsizei height)
	{
		glViewport(x, y, width, height);
	}

	void Viewport(GLsizei width, GLsizei height)
	{
		Viewport(0, 0, width, height);		
	}
}
#pragma once
#include <glad/glad.h>

namespace opengl
{
	void ClearColor(float r, float g, float b);
	void ClearColor(float r, float g, float b, float a);

	void Viewport(GLint x, GLint y, GLsizei width, GLsizei height);
	void Viewport(GLsizei width, GLsizei height);
}
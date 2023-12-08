#pragma once
#include <glad/glad.h>

namespace opengl
{
	void Init();

	// TODO: make it better
	void APIENTRY GLDebugMessageCallback(GLenum source, GLenum type, GLuint id,
		GLenum severity, GLsizei length,
		const GLchar* msg, const void* data);
}
#pragma once
#include <glad/glad.h>

namespace opengl
{
	class Buffer
	{
	public:
		Buffer(const GLvoid* data, GLsizeiptr size, GLenum usage);
		Buffer(const GLvoid* data, GLsizeiptr size);

		const GLuint ID() const { return m_ID; }

	private:
		GLuint m_ID = 0;
	};
}
#include "Buffer.h"

namespace opengl
{
	Buffer::Buffer(const GLvoid* data, GLsizeiptr size, GLenum usage)
	{
		glCreateBuffers(1, &m_ID);
		glNamedBufferData(m_ID, size, data, usage);
	}

	Buffer::Buffer(const GLvoid* data, GLsizeiptr size) :
		Buffer(data, size, GL_STATIC_DRAW)
	{
	}
}
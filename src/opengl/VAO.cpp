#include "VAO.h"

namespace opengl
{
	VAO::VAO()
	{
		glCreateVertexArrays(1, &m_ID);
	}

	void VAO::Bind()
	{
		glBindVertexArray(m_ID);
	}

	void VAO::Unbind()
	{
		glBindVertexArray(0);
	}

	void VAO::BindVertexBuffer(const VBO& vbo, GLuint bindindex, GLintptr offset, GLsizei stride)
	{
		glVertexArrayVertexBuffer(m_ID, bindindex, vbo.ID(), offset, stride);
	}

	void VAO::BindElementBuffer(const EBO& ebo)
	{
		glVertexArrayElementBuffer(m_ID, ebo.ID());
	}
	void VAO::SpecifyData(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset)
	{
		glEnableVertexArrayAttrib(m_ID, attribindex);
		glVertexArrayAttribBinding(m_ID, attribindex, 0);
		glVertexArrayAttribFormat(m_ID, attribindex, size, type, normalized, relativeoffset);
	}
	void VAO::SpecifyData(GLuint attribindex, GLint size, GLuint relativeoffset)
	{
		SpecifyData(attribindex, size, GL_FLOAT, GL_FALSE, relativeoffset);
	}
}
#pragma once
#include "Buffers/VBO.h"
#include "Buffers/EBO.h"

namespace opengl
{
	class VAO
	{
	public:
		VAO();

		void Bind();
		void Unbind();

		void BindVertexBuffer(const VBO& vbo, GLuint bindindex, GLintptr offset, GLsizei stride);
		void BindElementBuffer(const EBO& ebo);
		void SpecifyData(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
		void SpecifyData(GLuint attribindex, GLint size, GLuint relativeoffset);

		
	private:
		GLuint m_ID;
	};
}
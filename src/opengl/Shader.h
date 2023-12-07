#pragma once
#include <string>
#include <glad/glad.h>

namespace opengl
{
	class Shader
	{
	public:
		Shader(const std::string& vertexFile, const std::string& fragmentFile);

		void Bind();
		void Unbind();

	private:
		bool GetFileContents(const std::string& filename, std::string& buffer);
		std::string LoadShader(const std::string& filename);
		void CreateProgram(const char* vertSource, const char* fragSource);

		GLuint m_ID;
	};
}
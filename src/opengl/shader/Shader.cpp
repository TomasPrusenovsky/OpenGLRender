#include "Shader.h"
#include <iostream>
#include <fstream>

namespace opengl
{
	Shader::Shader(const std::string& vertexFile, const std::string& fragmentFile) :
		m_Parser()
	{
		ShaderSource vertSource = m_Parser.GetSource(vertexFile, ShaderType::VERTEX);
		ShaderSource fragSource = m_Parser.GetSource(fragmentFile, ShaderType::FRAGMENT);
		CreateProgram(vertSource.contents.c_str(), fragSource.contents.c_str());
	}

	void Shader::Bind()
	{
		glUseProgram(m_ID);
	}

	void Shader::Unbind()
	{
		glUseProgram(0);
	}

	void Shader::uni1f(const std::string& name, float data1)
	{
		glUniform1f(GetUniformLocation(name), data1);
	}

	void Shader::uni2f(const std::string& name, float data1, float data2)
	{
		glUniform2f(GetUniformLocation(name), data1, data2);
	}

	void Shader::uni3f(const std::string& name, float data1, float data2, float data3)
	{
		glUniform3f(GetUniformLocation(name), data1, data2, data3);
	}

	void Shader::uni4f(const std::string& name, float data1, float data2, float data3, float data4)
	{
		glUniform4f(GetUniformLocation(name), data1, data2, data3, data4);
	}

	void Shader::uni4mat(const std::string& name, float* val_ptr)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, val_ptr);
	}

	void Shader::CreateProgram(const char* vertSource, const char* fragSource)
	{
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertSource, NULL);
		glCompileShader(vertexShader);
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragSource, NULL);
		glCompileShader(fragmentShader);

		m_ID = glCreateProgram();
		glAttachShader(m_ID, vertexShader);
		glAttachShader(m_ID, fragmentShader);
		glLinkProgram(m_ID);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	GLuint Shader::GetUniformLocation(const std::string& name)
	{
		if (!m_UniLocCache.contains(name))
			m_UniLocCache[name] = glGetUniformLocation(m_ID, name.c_str());
		return m_UniLocCache[name];
	}
}
#include "Shader.h"
#include <iostream>
#include <fstream>

namespace opengl
{
	Shader::Shader(const std::string& vertexFile, const std::string& fragmentFile)
	{
		std::string vertSource = LoadShader(vertexFile);
		std::string fragSource = LoadShader(fragmentFile);
		CreateProgram(vertSource.c_str(), fragSource.c_str());
	}

	void Shader::Bind()
	{
		glUseProgram(m_ID);
	}

	void Shader::Unbind()
	{
		glUseProgram(0);
	}

	void Shader::uni1f(const char* name, float data1)
	{
		glUniform1f(glGetUniformLocation(m_ID, name), data1);
	}

	void Shader::uni2f(const char* name, float data1, float data2)
	{
		glUniform2f(glGetUniformLocation(m_ID, name), data1, data2);
	}

	void Shader::uni3f(const char* name, float data1, float data2, float data3)
	{
		glUniform3f(glGetUniformLocation(m_ID, name), data1, data2, data3);
	}

	void Shader::uni4f(const char* name, float data1, float data2, float data3, float data4)
	{
		glUniform4f(glGetUniformLocation(m_ID, name), data1, data2, data3, data4);
	}

	void Shader::uni4mat(const char* name, float* val_ptr)
	{
		glUniformMatrix4fv(glGetUniformLocation(m_ID, name), 1, GL_FALSE, val_ptr);
	}

	bool Shader::GetFileContents(const std::string& filename, std::string& buffer)
	{
		std::ifstream file(filename.c_str(), std::ios_base::binary);
		if (file)
		{
			file.seekg(0, std::ios_base::end);
			std::streamsize size = file.tellg();
			if (size > 0)
			{
				file.seekg(0, std::ios_base::beg);
				buffer.resize(static_cast<std::size_t>(size));
				file.read(&buffer[0], size);
			}
			buffer.push_back('\0');
			return true;
		}
		else
		{
			return false;
		}
	}

	std::string Shader::LoadShader(const std::string& filename)
	{
		std::string buffer;
		bool success = GetFileContents(filename, buffer);
		if (!success)
			std::cerr << "Failed to load shader: " << filename << std::endl;

		return buffer;
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
}
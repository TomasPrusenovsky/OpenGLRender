#pragma once
#include "ShaderParser.h"
#include <glad/glad.h>

namespace opengl
{
	class Shader
	{
	public:
		Shader(const std::string& vertexFile, const std::string& fragmentFile);

		void Bind();
		void Unbind();

		//unifom upload
		void uni1f(const std::string& name, float data);
		void uni2f(const std::string& name, float data1, float data2);
		void uni3f(const std::string& name, float data1, float data2, float data3);
		void uni4f(const std::string& name, float data1, float data2, float data3, float data4);
		void uni4mat(const std::string& name, float* val_ptr);

	private:
		void CreateProgram(const char* vertSource, const char* fragSource);
		GLuint GetUniformLocation(const std::string& name);

		std::unordered_map<std::string, GLuint> m_UniLocCache;
		ShaderParser m_Parser;
		GLuint m_ID;
	};
}
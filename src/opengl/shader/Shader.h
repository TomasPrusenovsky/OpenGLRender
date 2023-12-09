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
		void uni1f(const char* name, float data);
		void uni2f(const char* name, float data1, float data2);
		void uni3f(const char* name, float data1, float data2, float data3);
		void uni4f(const char* name, float data1, float data2, float data3, float data4);
		void uni4mat(const char* name, float* val_ptr);

	private:
		void CreateProgram(const char* vertSource, const char* fragSource);

		ShaderParser m_Parser;
		GLuint m_ID;
	};
}
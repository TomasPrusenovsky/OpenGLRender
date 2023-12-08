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

		//unifom upload
		void uni1f(const char* name, float data);
		void uni2f(const char* name, float data1, float data2);
		void uni3f(const char* name, float data1, float data2, float data3);
		void uni4f(const char* name, float data1, float data2, float data3, float data4);
		void uni4mat(const char* name, float* val_ptr);

	private:
		bool GetFileContents(const std::string& filename, std::string& buffer);
		std::string LoadShader(const std::string& filename);
		void CreateProgram(const char* vertSource, const char* fragSource);

		GLuint m_ID;
	};
}
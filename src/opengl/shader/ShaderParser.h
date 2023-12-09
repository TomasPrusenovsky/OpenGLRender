#pragma once
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <iostream>

namespace opengl
{
	enum class UniformType
	{
		NONE,
		FLOAT, VEC2, VEC3, VEC4,
		MAT2, MAT3, MAT4
	};

	enum class ShaderType
	{
		VERTEX, FRAGMENT
	};

	struct ShaderSource
	{
		std::string contents;
		ShaderType type;
	};

	using StringToEnumMap = std::unordered_map<std::string, UniformType>;
	class ShaderParser
	{
	public:
		ShaderParser();
		ShaderSource GetSource(const std::string& filepath, ShaderType type);

	private:
		bool GetContents(const std::string& path, std::string& buffer);
		UniformType GetUniType(const std::string& type);

	private:
		using UniformCache = std::unordered_map<std::string, UniformType>;
		UniformCache m_UniCache;

		static StringToEnumMap s_Conversion;
	};
}

#include "ShaderParser.h"

namespace opengl
{
	StringToEnumMap ShaderParser::s_Conversion = 
	{
		{"float", UniformType::FLOAT},
		{"vec2", UniformType::VEC2},
		{"vec3", UniformType::VEC3},
		{"vec4", UniformType::VEC4},
		{"mat2", UniformType::MAT2},
		{"mat3", UniformType::MAT3},
		{"mat4", UniformType::MAT4}
	};

	ShaderParser::ShaderParser()
	{
	}

	ShaderSource ShaderParser::GetSource(const std::string& filepath, ShaderType type)
	{
		std::string buffer;
		if (!GetContents(filepath, buffer))
			std::cerr << "Failed to load: " << filepath << std::endl;

		return { buffer, type };
	}

	bool ShaderParser::GetContents(const std::string& path, std::string& buffer)
	{
		std::ifstream file{ path };
		std::string line;

		if (file)
		{
			while (std::getline(file, line))
			{
				if (line.find("uniform") != std::string::npos)
				{
					std::istringstream iss{ line };
					std::string type, name;
					iss >> type >> type >> name;
					name.pop_back();

					m_UniCache[name] = GetUniType(type);
				}
				buffer += line + '\n';
			}
			return true;
		}
		else
		{
			return false;
		}
	}

	UniformType ShaderParser::GetUniType(const std::string& type)
	{
		if (!s_Conversion.contains(type))
		{
			std::cerr << "Invalid (or not yet implemented) uniform type in shader: " << type << std::endl;
			return UniformType::NONE;
		}
		return s_Conversion[type];
	}
}
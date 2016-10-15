#include "shader.h"



Shader::Shader(const GLenum &GLType)
{
	if (GLType == GL_VERTEX_SHADER)
	{
		type = "Vertex";
	}
	else if (GLType == GL_FRAGMENT_SHADER)
	{
		type = "Fragment";
	}
	else if (GLType == GL_GEOMETRY_SHADER)
	{
		type = "Geometry";
	}


	id = glCreateShader(GLType);
}


void Shader::LoadFromFile(const std::string& filename)
{
	std::ifstream ifs;
	ifs.open(filename.c_str());

	if (!ifs.good())
	{
		std::cout << "Failed to open file: " << filename << std::endl;
		exit(-1);
	}

	std::stringstream ss;
	ss << ifs.rdbuf();

	ifs.close();

	source = ss.str();

	const char* sourceChars = source.c_str();

	glShaderSource(id, 1, &sourceChars, NULL);
}


void Shader::Compile()
{
	glCompileShader(id);

	// Check Error
	GLint succeed;
	glGetShaderiv(id, GL_COMPILE_STATUS, &succeed);

	if (succeed == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* infoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(id, infoLogLength, NULL, infoLog);

		std::cout << type << " shader compile failed: " << infoLog << std::endl;

		delete[] infoLog;
	}
	else
	{
		std::cout << type << " shader compile succeed" << std::endl;
	}
}
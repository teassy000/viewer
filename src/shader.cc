#include "shader.h"

#include <fstream>
#include <sstream>


Shader::Shader(const GLenum &GLType)
{
	if (GLType == GL_VERTEX_SHADER)
	{
		type_ = "Vertex";
	}
	else if (GLType == GL_FRAGMENT_SHADER)
	{
		type_ = "Fragment";
	}
	else if (GLType == GL_GEOMETRY_SHADER)
	{
		type_ = "Geometry";
	}


	id_ = glCreateShader(GLType);
}


void Shader::load_from_file(const std::string& filename)
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

	source_ = ss.str();

	const char* source_chars = source_.c_str();

	glShaderSource(id_, 1, &source_chars, NULL);
}


void Shader::load_from_buffer(const std::string& source)
{
	source_ = source;
	const char* source_chars = source_.c_str();

	glShaderSource(id_, 1, &source_chars, NULL);
}


bool Shader::compile()
{
	glCompileShader(id_);

	// Check Error
	GLint succeed;
	glGetShaderiv(id_, GL_COMPILE_STATUS, &succeed);


	bool result = false;
	if (succeed == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(id_, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* infoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(id_, infoLogLength, NULL, infoLog);

		std::cout << type_ << " shader compile failed: " << infoLog << std::endl;

		delete[] infoLog;

		result = false;
	}
	else
	{
		std::cout << type_ << " shader compile succeed" << std::endl;

		result = true;
	}

	return result;
}
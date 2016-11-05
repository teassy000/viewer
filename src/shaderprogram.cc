#include "shaderprogram.h"

ShaderProgram::ShaderProgram()
{
	programid_ = glCreateProgram();

	shadercount_ = 0;
}


ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(programid_);
}


void ShaderProgram::attach_shader(Shader shader)
{
	glAttachShader(programid_, shader.get_id());

	shadercount_++;
}


bool ShaderProgram::link()
{
	bool result;

	if (shadercount_ >= MIN_NUM_SHADER)
	{

		glLinkProgram(programid_);

		GLint succeed;
		glGetProgramiv(programid_, GL_LINK_STATUS, &succeed);

		if (succeed == GL_FALSE)
		{
			std::cout << "Shader program linking failed." << std::endl;
			result = false;
		}
		else
		{
			std::cout << "Shader program linking succeed." << std::endl;
			result = true;
		}
	}
	else
	{
		std::cout << "Cannot linking program: You need attach at least 2 shader to link shader program"
			<< std::endl;
		result = false;
	}

	return result;
}


GLuint ShaderProgram::attribute(const std::string& attribute)
{
	GLuint value;

	try {
		value = attributelist_.at(attribute);
	}
	catch (const std::out_of_range& oor) {
		std::cout << "Getting attribute " << attribute << " failed: " << oor.what() << std::endl;
		value = -1;
	}

	return value;
}



GLuint ShaderProgram::uniform(const std::string& uniform)
{
	GLuint value;

	try {
		value = uniformlist_.at(uniform);
	}
	catch (const std::out_of_range& oor) {
		std::cout << "Getting uniform " << uniform << " failed: " << oor.what() << std::endl;
		value = -1;
	}

	return value;
}


int ShaderProgram::add_attribute(const std::string& attribute)
{
	int id = glGetAttribLocation(programid_, attribute.c_str());

	if (id != -1)
	{
		attributelist_[attribute] = id;
	}
	else
	{
		std::cout << "Get attribute: \"" << attribute << "\" failed." << std::endl;
	}

	return id;
}


int ShaderProgram::add_uniform(const std::string& uniform)
{
	int id = glGetAttribLocation(programid_, uniform.c_str());

	if (id != -1)
	{
		uniformlist_[uniform] = id;
	}
	else
	{
		std::cout << "Get uniform: \"" << uniform << "\" failed." << std::endl;
	}

	return id;
}

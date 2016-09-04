#pragma once

#include <shader.h>
#include <map>


class ShaderProgram
{

	const unsigned int MIN_NUM_SHADER = 2;

public:
	ShaderProgram();
	~ShaderProgram();

public:
	void AttachShader(Shader shader);
	void Link();

	inline void Use() { glUseProgram(programId); }; //enable the program
	inline void Diable() { glUseProgram(0); }

	GLuint Attribute(const std::string& attribute);
	GLuint Uniform(const std::string& uniform);

	int AddAttribute(const std::string& attribute);
	int AddUniform(const std::string& uniform);

private:
	GLuint programId;
	GLuint shaderCount;		// num of shaders that attach to the program.

	std::map<std::string, int> attributeList;
	std::map<std::string, int> uniformList;
};


ShaderProgram::ShaderProgram()
{
	programId = glCreateProgram();

	shaderCount = 0;
}


ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(programId);
}


void ShaderProgram::AttachShader(Shader shader)
{
	glAttachShader(programId, shader.GetId());

	shaderCount++;
}


void ShaderProgram::Link()
{
	if (shaderCount >= MIN_NUM_SHADER)
	{

		glLinkProgram(programId);

		GLint succeed;
		glGetProgramiv(programId, GL_LINK_STATUS, &succeed);

		if (succeed == GL_FALSE)
		{
			std::cout << "Shader program linking failed." << std::endl;
		}
		else
		{
			std::cout << "Shader program linking succeed." << std::endl;
		}
	}
	else
	{
		std::cout << "Cannot linking program: You need attach at least 2 shader to link shader program"
			<< std::endl;
	}
}


GLuint ShaderProgram::Attribute(const std::string& attribute)
{
	GLuint value;

	try {
		value = attributeList.at(attribute);
	}
	catch (const std::out_of_range& oor) {
		std::cout << "Getting attribute " << attribute << " failed: " << oor.what() << std::endl;
		value = -1;
	}

	return value;
}



GLuint ShaderProgram::Uniform(const std::string& uniform)
{
	GLuint value;

	try {
		value = uniformList.at(uniform);
	}
	catch (const std::out_of_range& oor) {
		std::cout << "Getting uniform " << uniform << " failed: " << oor.what() << std::endl;
		value = -1;
	}

	return value;
}


int ShaderProgram::AddAttribute(const std::string& attribute)
{
	int id = glGetAttribLocation(programId, attribute.c_str());

	if (id != -1)
	{
		attributeList[attribute] = id;
	}
	else
	{
		std::cout << "Get attribute: \"" << attribute << "\" failed." << std::endl;
	}

	return id;
}


int ShaderProgram::AddUniform(const std::string& uniform)
{
	int id = glGetAttribLocation(programId, uniform.c_str());

	if (id != -1)
	{
		attributeList[uniform] = id;
	}
	else
	{
		std::cout << "Get attribute: \"" << uniform << "\" failed." << std::endl;
	}

	return id;
}

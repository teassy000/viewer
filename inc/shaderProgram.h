#pragma once
#include "precomp.h"
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
	inline void Disable() { glUseProgram(0); }

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



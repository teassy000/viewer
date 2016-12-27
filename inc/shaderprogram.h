#pragma once
#include "precomp.h"
#include "shader.h"
#include <map>


class ShaderProgram
{

	const unsigned int MIN_NUM_SHADER = 2;

public:
	ShaderProgram();
	~ShaderProgram();

public:
	void attach_shader(Shader shader);
	bool link();

	inline void use() { glUseProgram(programid_); }; //enable the program
	inline void del() { glDeleteProgram(programid_); }
	inline void disable() { glUseProgram(0); }


	GLuint attribute(const std::string& attribute);
	GLuint uniform(const std::string& uniform);

	int add_attribute(const std::string& attribute);
	int add_uniform(const std::string& uniform);

private:
	GLuint programid_;
	GLuint shadercount_;		// num of shaders that attach to the program.

	std::map<std::string, int> attributelist_;
	std::map<std::string, int> uniformlist_;
};



#pragma once

#include "precomp.h"

#include <string>
#include <fstream>
#include <sstream>


class Shader
{
	typedef std::string ShaderType;

public:
	Shader(const GLenum &GLType);
	~Shader() {};

public:
	void LoadFromFile(const std::string& filename);
	void Compile();

	inline GLuint GetId() { return id; }
	inline std::string GetSource() { return source; }

private:
	GLuint id;
	ShaderType type;
	std::string source;
};



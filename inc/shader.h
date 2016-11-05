#pragma once

#include "precomp.h"

#include <string>


class Shader
{
	typedef std::string ShaderType;

public:
	Shader(const GLenum &GLType);
	~Shader() {};

public:
	void load_from_file(const std::string& filename);
	void load_from_buffer(const std::string& source);
	bool compile();

	inline GLuint get_id() { return id_; }
	inline std::string get_source() { return source_; }

private:
	GLuint id_;
	ShaderType type_;
	std::string source_;
};



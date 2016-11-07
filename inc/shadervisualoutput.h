#pragma once
#include "precomp.h"
#include "shaderprogram.h"
#include "shadersource.h"

class ShaderVisualOutput
{
public:
	enum class ShaderType{vertexshader, fragmentshader};

	ShaderVisualOutput();
	~ShaderVisualOutput();

	void load(std::string, std::string);
	void reload();
	void render();

	void set_source(std::string, ShaderType);
	bool is_shader_compile_succeed() const { return iscompilesucceed; }

private:
	void load_vertexbuffer();

	void load_shader();
	void load_framebuffer();

private:
	std::unique_ptr<ShaderProgram> program_;
	std::string  fragment_source_;
	std::string  vertex_source_;
	bool iscompilesucceed;

	GLuint texture_;
	GLuint framebuffer_;
	GLuint vertexbuffer_;
};
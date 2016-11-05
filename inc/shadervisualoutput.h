#pragma once
#include "precomp.h"
#include "baserenderobject.h"
#include "shaderprogram.h"

class ShaderVisualOutput : public BaseRenderObject
{
public:
	ShaderVisualOutput();
	virtual ~ShaderVisualOutput();

	virtual void load() override;
	virtual void reload() override;
	virtual void render() override;
private:
	void load_shader();
	void load_framebuffer();

private:
	std::unique_ptr<ShaderProgram> program_;
	GLuint texture_;
	GLuint framebuffer_;
	GLuint vertexbuffer_;
};
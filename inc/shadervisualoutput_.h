#pragma once
#include "precomp.h"
#include "baserenderobject.h"
#include "shaderprogram.h"

class ShaderVisualOutput : public BaseRenderObject
{
public:
	ShaderVisualOutput();
	virtual ~ShaderVisualOutput();

	virtual void Load() override;
	virtual void Reload() override;
	virtual void Render() override;
private:
	void LoadShader();
	void LoadFramebuffer();

private:
	std::unique_ptr<ShaderProgram> program_;
	GLuint texture_;
	GLuint framebuffer_;
	GLuint vertexbuffer_;
};
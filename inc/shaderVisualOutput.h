#pragma once
#include "precomp.h"
#include "baseRenderObject.h"
#include "shaderProgram.h"

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
	std::unique_ptr<ShaderProgram> m_program;
	GLuint texture_;
	GLuint framebuffer_;
	GLuint vertexbuffer_;
};
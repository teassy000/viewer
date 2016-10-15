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
	std::unique_ptr<ShaderProgram> m_program;
};
#pragma once

#include "precomp.h"
#include "baseRenderObject.h"
#include "shaderProgram.h"
#include "fontAtlas.h"

#include <memory>

class ShaderTextsOutput : public BaseRenderObject
{
public:
	ShaderTextsOutput();
	virtual ~ShaderTextsOutput();

	virtual void Load() override;
	virtual void Reload() override;
	virtual void Render() override;
private:
	std::unique_ptr<ShaderProgram> m_program;
	std::unique_ptr<FontAtlas> m_fontAtlas;
};
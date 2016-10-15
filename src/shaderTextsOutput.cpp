#include "shaderTextsOutput.h"

ShaderTextsOutput::ShaderTextsOutput()
	: m_program(std::make_unique<ShaderProgram>())
	, m_fontAtlas(std::make_unique<FontAtlas>())
{
}

ShaderTextsOutput::~ShaderTextsOutput()
{
}


void ShaderTextsOutput::Load()
{
	m_fontAtlas.get()->Initialize();
}


void ShaderTextsOutput::Reload()
{

}


void ShaderTextsOutput::Render()
{

}

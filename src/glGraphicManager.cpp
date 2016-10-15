#include "glGraphicManager.h"
#include "utils.h"

glGraphicManager::glGraphicManager()
	: m_shaderOutput(std::make_unique<ShaderVisualOutput>())
{
}

glGraphicManager::~glGraphicManager()
{

}



void glGraphicManager::Load()
{
	m_shaderOutput.get()->Load();
}



void glGraphicManager::Reload()
{
	m_shaderOutput.get()->Reload();
}



void glGraphicManager::Render()
{
	m_shaderOutput.get()->Render();
}

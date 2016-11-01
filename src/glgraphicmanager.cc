#include "glgraphicmanager.h"
#include "utils.h"

glGraphicManager::glGraphicManager()
	: shaderoutput_(std::make_unique<ShaderVisualOutput>())
{
}

glGraphicManager::~glGraphicManager()
{

}



void glGraphicManager::Load()
{
	shaderoutput_.get()->Load();
}



void glGraphicManager::Reload()
{
	shaderoutput_.get()->Reload();
}



void glGraphicManager::Render()
{
	shaderoutput_.get()->Render();
}

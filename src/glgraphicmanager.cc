#include "glgraphicmanager.h"
#include "utils.h"

glGraphicManager::glGraphicManager()
	: shaderoutput_(std::make_unique<ShaderVisualOutput>())
{
}

glGraphicManager::~glGraphicManager()
{

}



void glGraphicManager::load()
{
	shaderoutput_.get()->load();
}



void glGraphicManager::reload()
{
	shaderoutput_.get()->reload();
}



void glGraphicManager::render()
{
	shaderoutput_.get()->render();
}


void glGraphicManager::shutdown()
{

}

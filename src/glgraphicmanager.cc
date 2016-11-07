#include "glgraphicmanager.h"
#include "utils.h"

glGraphicManager::glGraphicManager()
	: shaderoutput_(std::make_unique<ShaderVisualOutput>())
{
}

glGraphicManager::~glGraphicManager()
{

}


void glGraphicManager::load(std::string vertex_src, std::string fragment_src)
{
	shaderoutput_.get()->load(vertex_src, fragment_src);
}



bool glGraphicManager::reload()
{
	return shaderoutput_.get()->reload();
}



void glGraphicManager::render()
{
	shaderoutput_.get()->render();
}


void glGraphicManager::shutdown()
{

}


void glGraphicManager::set_source(std::string source, ShaderVisualOutput::ShaderType type)
{
	shaderoutput_->set_source(source, type);
}


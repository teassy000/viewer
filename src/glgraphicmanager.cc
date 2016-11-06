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


void glGraphicManager::save() const
{
	shaderoutput_->save_fragment_source();
}


std::string glGraphicManager::get_fragment_src() const
{
	std::string return_source = shaderoutput_->get_fragment_source();
	return return_source;
}


void glGraphicManager::set_fragment_src(std::string source)
{
	shaderoutput_->set_fragment_source(source);
}


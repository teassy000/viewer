#pragma once

#include "precomp.h"
#include "shadervisualoutput.h"


// Here's glGraphicManager do:
// render the shader program part and get the frame buffer
// alpha blend program part and font part.
class glGraphicManager
{
private:
	glGraphicManager();
	
public:
	static glGraphicManager* get_instance()
	{
		static glGraphicManager* instance_;
		if (instance_ == nullptr)
		{
			instance_ = new glGraphicManager();
		}
		return instance_;
	}

	~glGraphicManager();

	void load();
	void reload();
	void render();
	void shutdown();

private:
	std::unique_ptr<ShaderVisualOutput> shaderoutput_;
};

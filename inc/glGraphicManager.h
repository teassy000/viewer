#pragma once

#include "precomp.h"
#include "shaderVisualOutput.h"


// Here's glGraphicManager do:
// render the shader program part and get the frame buffer
// alpha blend program part and font part.
class glGraphicManager
{
private:
	glGraphicManager();
	
public:
	static glGraphicManager* getInstance()
	{
		static glGraphicManager* instance_;
		if (instance_ == nullptr)
		{
			instance_ = new glGraphicManager();
		}
		return instance_;
	}

	~glGraphicManager();

	void Load();
	void Reload();
	void Render();

private:
	std::unique_ptr<ShaderVisualOutput> shaderoutput_;
};

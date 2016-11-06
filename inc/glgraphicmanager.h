#pragma once

#include "precomp.h"
#include "shadervisualoutput.h"
#include <string>


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

	// for fragment shader source
	void save() const;
	std::string get_fragment_src() const;
	void set_fragment_src(std::string);

private:
	std::unique_ptr<ShaderVisualOutput> shaderoutput_;
};

#pragma once

#include "precomp.h"
#include "shaderVisualOutput.h"
#include "shaderTextsOutput.h"


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
		static glGraphicManager* m_instance;
		if (m_instance == nullptr)
		{
			m_instance = new glGraphicManager();
		}
		return m_instance;
	}

	~glGraphicManager();

	void Load();
	void Reload();
	void Render();

private:
	std::unique_ptr<ShaderVisualOutput> m_shaderOutput;
};

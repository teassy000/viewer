#pragma once

// Interface of rendering object such as:
// rendering output
// shader text
// debug information
class BaseRenderObject
{
public:
	virtual void Load() = 0;
	virtual void Reload() = 0;
	virtual void Render() = 0;
};

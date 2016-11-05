#pragma once

// Interface of rendering object such as:
// rendering output
// shader text
// debug information
class BaseRenderObject
{
public:
	virtual void load() = 0;
	virtual void reload() = 0;
	virtual void render() = 0;
};

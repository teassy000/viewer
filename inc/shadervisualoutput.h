#pragma once
#include "precomp.h"
#include "baserenderobject.h"
#include "shaderprogram.h"
#include "shadersource.h"

class ShaderVisualOutput : public BaseRenderObject
{
public:
	ShaderVisualOutput();
	virtual ~ShaderVisualOutput();

	virtual void load() override;
	virtual void reload() override;
	virtual void render() override;

	inline std::string get_fragment_source() const { return fragment_source_->get_source(); }
	inline void set_fragment_source(std::string src) { fragment_source_->set_source(src); }
	void save_fragment_source();
private:
	void load_vertexbuffer();
	void load_shader();
	void load_framebuffer();
	void load_shader_source();

private:
	std::unique_ptr<ShaderProgram> program_;
	std::unique_ptr<ShaderSource>  fragment_source_;
	std::unique_ptr<ShaderSource>  vertex_source_;

	GLuint texture_;
	GLuint framebuffer_;
	GLuint vertexbuffer_;
};
#pragma once
#include <string>

class ShaderSource
{
public:
	static ShaderSource* get_instance()
	{
		static ShaderSource* instance = new ShaderSource();
		return instance;
	}

	void read_vertex_src_fromfile(std::string filename);
	void read_fragment_src_fromfile(std::string filename);


	void save_to_vertex();
	void save_to_fragment();

	

	void set_vertex_source(std::string source) { vertex_source_ = source; }
	std::string get_vertex_source() const { return vertex_source_; }

	void set_vertex_filename(std::string filename) { vertex_filename_ = filename; }
	std::string get_vertex_filename() const { return vertex_filename_; }

	void set_fragment_source(std::string source) { fragment_source_ = source; }
	std::string get_fragment_source() const { return fragment_source_; }

	void set_fragment_filename(std::string filename) { fragment_filename_ = filename; }
	std::string get_fragment_filename() const { return fragment_filename_; }

private:
	std::string readfromfile(std::string filename);
	void save(std::string, std::string);

	std::string vertex_source_;
	std::string vertex_filename_;

	std::string fragment_source_;
	std::string fragment_filename_;
};
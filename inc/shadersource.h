#pragma once
#include <string>

class ShaderSource
{
public:
	void readfromfile(std::string filename);

	void save();
	
	void set_source(std::string source) { source_ = source; }
	std::string get_source() const { return source_; }

	void set_filename(std::string filename) { filename_ = filename; }
	std::string get_filename() const { return filename_; }
private:
	std::string source_;
	std::string filename_;
};
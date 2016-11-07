#include "shadersource.h"

#include <iostream>
#include <fstream>
#include <sstream>


void ShaderSource::read_vertex_src_fromfile(std::string filename)
{
	vertex_filename_ = filename;
	vertex_source_ = readfromfile(vertex_filename_);
}


void ShaderSource::read_fragment_src_fromfile(std::string filename)
{
	fragment_filename_ = filename;
	fragment_source_ = readfromfile(fragment_filename_);
}



std::string ShaderSource::readfromfile(std::string filename)
{
	std::ifstream ifs;
	ifs.open(filename.c_str());

	if (!ifs.good())
	{
		std::cout << "Failed to open file: " << filename << std::endl;
		exit(-1);
	}

	std::stringstream ss;
	ss << ifs.rdbuf();

	ifs.close();

	return ss.str();
}


void ShaderSource::save_to_vertex()
{
	save(vertex_source_, vertex_filename_);
}


void ShaderSource::save_to_fragment()
{
	save(fragment_source_, fragment_filename_);
}


void ShaderSource::save(std::string source,  std::string filename)
{
	// file name cannot be empty
	if (filename == std::string())
		return;

	std::ofstream ofs;
	ofs.open(filename.c_str());

	if (!ofs.good())
	{
		std::cout << "Failed to open file: " << filename << std::endl;
		exit(-1);
	}

	ofs << source;
	ofs.close();

	return;
}
#include "shadersource.h"

#include <iostream>
#include <fstream>
#include <sstream>


void ShaderSource::readfromfile(std::string filename)
{
	filename_ = filename;
	std::ifstream ifs;
	ifs.open(filename_.c_str());

	if (!ifs.good())
	{
		std::cout << "Failed to open file: " << filename << std::endl;
		exit(-1);
	}

	std::stringstream ss;
	ss << ifs.rdbuf();

	ifs.close();

	source_ = ss.str();
}


void ShaderSource::save()
{
	// file name cannot be empty
	if (filename_ == std::string())
		return;

	std::ofstream ofs;
	ofs.open(filename_.c_str());

	if (!ofs.good())
	{
		std::cout << "Failed to open file: " << filename_ << std::endl;
		exit(-1);
	}

	ofs << source_;
	ofs.close();

	return;
}
#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <glad\glad.h>

#include <ft2build.h>	// Include header which contains macros
#include FT_FREETYPE_H	// Include the macro which I need.



class FontLoader
{

public:
	FontLoader();
	~FontLoader();

	static bool InitFreeType();

	bool LoadFreeType(std::string filename, GLuint pixelSize);
	bool FreeFont();
	void RenderText(GLfloat x, GLfloat y, std::string text);


private:
	static FT_Library m_lib;

	GLfloat mSpace;
	GLfloat mLineHeight;
	GLfloat mNewLine;

	std::string mFontBuffer;
};


FontLoader::FontLoader()
{
}


FontLoader::~FontLoader()
{
}


bool FontLoader::InitFreeType()
{
	FT_Error error = FT_Init_FreeType(&m_lib);
	if (error != FT_Err_Ok)
	{
		std::cout << "Initialize FreeType failed." << std::endl;
		return false;
	}

	return true;
}


bool FontLoader::LoadFreeType(std::string filename, GLuint pixelSize)
{
	FT_Face face;
	FT_Error error = FT_New_Face(m_lib, filename.c_str(), 0, &face);

	switch(error) {
	case FT_Err_Ok:
		error = FT_Set_Pixel_Sizes(face, 0, pixelSize);
		if (error == FT_Err_Ok)
		{

		}
		break;
	case FT_Err_Unknown_File_Format:
		std::cout << "[Error]:Cannot open " << filename << std::endl;
		std::cout << "Unsupported file format." << std::endl;
		break;
	default:
		std::cout << "[Error]:Cannot open " << filename << std::endl;
		std::cout << "Please check if the font file is broken or the app have no access permission." << std::endl;
		break;
	}

	return true;
}


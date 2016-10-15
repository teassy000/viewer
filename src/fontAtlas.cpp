#include <iostream>
#include <algorithm>

#define NOMINMAX // because windows.h redefine the max
#include <glad\glad.h>

#include "utils.h"
#include "fontAtlas.h"



FT_Library FontAtlas::m_lib;

FontAtlas::FontAtlas()
{
	InitFreeType();
}


FontAtlas::~FontAtlas()
{
	FreeFont();
}


void FontAtlas::Initialize()
{
	InitFreeType();
	glGenBuffers(1, &vbo);
}


bool FontAtlas::InitFreeType()
{
	FT_Error error = FT_Init_FreeType(&m_lib);
	if (error != FT_Err_Ok)
	{
		std::cout << "Initialize FreeType failed." << std::endl;
		return false;
	}
	return true;
}


bool FontAtlas::LoadFreeType(std::string filename, int pixelSize)
{
	unsigned int w = 0;
	unsigned int h = 0;
	w = 0;
	h = 0;
	

	FT_Face face;
	FT_Error error = FT_New_Face(m_lib, filename.c_str(), 0, &face);

	switch (error) {
	case FT_Err_Ok:
		error = FT_Set_Pixel_Sizes(face, 0, pixelSize);
		if (error == FT_Err_Ok)
		{
			LoadFaceToTex(face);
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


void FontAtlas::LoadFaceToTex(FT_Face face)
{
	if (!face)
	{
		return;
	}

	FT_GlyphSlot g = face->glyph;

	unsigned int roww = 0;
	unsigned int rowh = 0;
	w = 0;
	h = 0;

	memset(ascii, 0, sizeof(ascii));

	//find the minimal size for a texture holding all visible ASCII chars.
	for (int i = 0; i < 128; i++)
	{
		if (FT_Load_Char(face, i, FT_LOAD_RENDER))
		{
			std::cout << "[Error]: Loading charactor " << (char)i << " failed.";
			continue;
		}
		if (roww += g->bitmap.width + 1 >= MAXWIDTH)
		{
			w = std::max(w, roww);
			h += rowh;
			roww = 0;
			rowh = 0;
		}
		roww += g->bitmap.width + 1;
		rowh = std::max(h, g->bitmap.rows);
	}


	w = std::max(w, roww);
	h += rowh;

	CreateTexture();

	// pasete all glyph into the texture, remembering the offset
	int ox = 0;
	int oy = 0;

	rowh = 0;

	for (int i = 32; i < 128; ++i)
	{
		if (FT_Load_Char(face, i, FT_LOAD_RENDER))
		{
			std::cout << "[Error]: Loading charactor " << (char)i << " failed.";
			continue;
		}

		if (ox + g->bitmap.width + 1 >= MAXWIDTH)
		{
			oy += rowh;
			rowh = 0;
			ox = 0;
		}

		glTexSubImage2D(GL_TEXTURE_2D,
			0,
			ox,
			oy,
			g->bitmap.width,
			g->bitmap.rows,
			GL_ALPHA,
			GL_UNSIGNED_BYTE,
			g->bitmap.buffer);

		ascii[i].ax = g->advance.x >> 6;
		ascii[i].ay = g->advance.y >> 6;

		ascii[i].bw = g->bitmap.width;
		ascii[i].bh = g->bitmap.rows;

		ascii[i].bl = g->bitmap_left;
		ascii[i].bt = g->bitmap_top;

		ascii[i].tx = ox / (float)w;
		ascii[i].ty = ox / (float)h;

		rowh = std::max(rowh, g->bitmap.rows);
		ox += g->bitmap.width + 1;
	}

	std::cerr << "Generated a " << w << " x " << h << "(" << w*h / 1024
		<< " kb) texture atlas" << std::endl;
}


void FontAtlas::CreateTexture()
{
	glActiveTexture(0);
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	glUniform1i(uniform_tex, 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, w, h, 0, GL_ALPHA, GL_UNSIGNED_BYTE, 0);

	// require 1 byte alignment when uploading texture
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


void FontAtlas::RenderText(float x, float y, std::string text)
{
	const uint8_t *p;

	glBindTexture(GL_TEXTURE_2D, texID);
	glUniform1i(uniform_tex, 0);

	glEnableVertexAttribArray(attribute_coord);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(attribute_coord, 4, GL_FLOAT, GL_FALSE, 0, 0);

	const int size = strlen(text.c_str());
	point coords[6*44];

	int c = 0;
	for (p = (const uint8_t *)text.c_str(); *p; p++)
	{
		float xt = x + ascii[*p].bl;
		float yt = -y - ascii[*p].bt;
		float cbw = ascii[*p].bw;
		float cbh = ascii[*p].bh;


		coords[c++] = point{ xt, -yt, ascii[*p].tx, ascii[*p].ty };
		coords[c++] = point{ xt + cbw, -yt, ascii[*p].tx + ascii[*p].bw / w, ascii[*p].ty };
		coords[c++] = point{ xt, -yt - cbh, ascii[*p].tx, ascii[*p].ty + ascii[*p].bh / h };
		coords[c++] = point{ xt + cbw, -yt, ascii[*p].tx + ascii[*p].bw / w,ascii[*p].ty };
		coords[c++] = point{ xt, -yt - cbh, ascii[*p].tx, ascii[*p].ty + ascii[*p].bh / h };
		coords[c++] = point{ xt + cbw, -yt - cbh, ascii[*p].tx + ascii[*p].bw / w, ascii[*p].ty + ascii[*p].bh / h };
	}

	/* Draw all the character on the screen in one go */
	glBufferData(GL_ARRAY_BUFFER, sizeof coords, coords, GL_DYNAMIC_DRAW);
	glDrawArrays(GL_TRIANGLES, 0, c);

	glDisableVertexAttribArray(attribute_coord);
}


void FontAtlas::FreeFont()
{
	glActiveTexture(0);
	glDeleteTextures(1, &texID);
}
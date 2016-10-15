#pragma once

#include <string>

#include <ft2build.h>	// Include header which contains macros
#include FT_FREETYPE_H	// Include the macro which I need.

// since font use a speical way to load texture, temporary use a indy texture.

class FontAtlas
{
public:
	struct point {
		float x;
		float y;
		float s;
		float t;
	};

	struct {
		float ax; // advance.x
		float ay; // advance.y

		float bw; // bitmap.width
		float bh; // bitmap.height

		float bl; // bitmap_left;
		float bt; // bitmap_top;

		float tx; // x offset of glphy in texture coordinates
		float ty; // y offset of glphy in texture coordinates
	}ascii[128]; // character info

	const unsigned int MAXWIDTH = 1024;

public:
	FontAtlas();
	~FontAtlas();

	void Initialize();
	bool LoadFreeType(std::string filename, int pixelSize);
	void FreeFont();
	void RenderText(float x, float y, std::string text);

	void SetCoord(GLuint id) { attribute_coord = id; }
	void SetTex(GLuint id) { uniform_tex = id; }
	void SetColor(GLuint id) { uniform_color = id; }


private:
	static bool InitFreeType();
	void LoadFaceToTex(FT_Face face);
	void CreateTexture();


private:
	static FT_Library m_lib;


	unsigned int w;
	unsigned int h;
	GLuint texID;
	GLuint attribute_coord;
	GLuint uniform_tex;
	GLuint uniform_color;

	GLuint vbo;

	std::string mFontBuffer;
};




#pragma once

#include <glad\glad.h>
#include <IL\il.h>

#include <string>
#include <iostream>

class Texture
{
public:
	Texture();
	~Texture();

public:
	void CreatePixels8(GLuint imgWidth, GLuint imgHeight);
	bool LoadTextureFromFile8(const std::string& filename);
	bool LoadTextureFromPixels8();
	void DuplicatePixel8(GLubyte* pixels, GLuint imgWidth, GLuint imgHeight);
	void BlitPixel8(GLuint x, GLuint y, Texture& destination);

	inline GLuint GetId()		const { return mTexID; }
	inline GLuint GetWidth()	const { return mTextureWidth; }
	inline GLuint GetHeight()	const { return mTextureHeight; }

	void FreeTuxture();

private:
	GLuint		mTexID;
	GLuint		mTextureWidth, mTextureHeight;
	GLuint		mImageWidth, mImageHeight;

	GLubyte*	mPixels8;

	GLenum		mPixelFormat;
};

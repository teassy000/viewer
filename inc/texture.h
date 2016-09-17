#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <IL\il.h>

#include <string>
#include <iostream>

class Texture
{
public:
	Texture(const GLenum &GLType);
	~Texture() {};

public:
	bool LoadTextureFromFile32(const std::string& filename);
	bool LoadTextureFromPixels32();

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

	GLuint*		mPixels32;
	GLubyte*	mPixels8;

	GLenum		mPixelFormat;
};


Texture::Texture(const GLenum &GLType)
	:mTexID(0),
	mTextureWidth(0),
	mTextureHeight(0),
	mImageWidth(0),
	mImageHeight(0),
	mPixels32(nullptr),
	mPixels8(nullptr)
{

}


bool Texture::LoadTextureFromFile32(const std::string& filename)
{
	bool textureLoaded = false;

	ILuint imageID;
	ilGenImages(1, &imageID);
	ilBindImage(imageID);

	ILboolean succeed = ilLoadImage(filename.c_str());
	if (succeed == IL_TRUE)
	{
		succeed = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
		if (succeed == IL_TRUE)
		{
			textureLoaded = LoadTextureFromPixels32();
		}
		ilDeleteImages(1, &imageID);
	}
	if (!textureLoaded)
	{
		std::cout << "[Error]: Unable to load " << filename << std::endl;
	}

	return textureLoaded;
}


bool Texture::LoadTextureFromPixels32()
{
	glGenTextures(1, &mTexID);
	glBindTexture(GL_TEXTURE_2D, mTexID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,mTextureWidth, mTextureHeight, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, mPixels32);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, NULL);

	GLenum error = glGetError();
	if (error != GL_NO_ERROR) 
	{ 
		std::cout << "Error loading texture from pixels!" << std::endl;
		return false; 
	}

	return true;
}


void Texture::CreatePixels8(GLuint imgWidth, GLuint imgHeight)
{
	if (imgWidth > 0 && imgHeight > 0)
	{
		FreeTuxture();

		GLuint size = imgWidth * imgHeight;
		mPixels8 = new GLubyte[ size ];
		memset(mPixels8, 0, size);

		mImageWidth = imgWidth;
		mImageHeight = imgHeight;
		mTextureWidth = mImageWidth;
		mTextureHeight = mImageHeight;

		mPixelFormat = GL_ALPHA;
	}
}


bool Texture::LoadTextureFromFile8(const std::string& filename)
{
	return true;
}


bool Texture::LoadTextureFromPixels8()
{
	bool result = true;

	if (mTexID == 0 && mPixels8 != nullptr)
	{


		glGenTextures(1, &mTexID);
		glBindTexture(GL_TEXTURE_2D, mTexID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mTextureWidth, mTextureHeight, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, mPixels8);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glBindTexture(GL_TEXTURE_2D, NULL);

		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
		{
			std::cout << "Error loading texture from pixels!" << std::endl;
			result = false;
		}
		else
		{
			delete[] mPixels8;
			mPixels8 = nullptr;

			mPixelFormat = GL_ALPHA;
		}

	}

	return result;
}


void Texture::DuplicatePixel8(GLubyte* pixels, GLuint imgWidth, GLuint imgHeight)
{
	if (imgWidth > 0 && imgHeight > 0)
	{
		FreeTuxture();

		GLuint size = imgWidth * imgHeight;
		mPixels8 = new GLubyte[size];
		memcpy(mPixels8, pixels, size);

		mImageWidth = imgWidth;
		mImageHeight = imgHeight;
		mTextureWidth = mImageWidth;
		mTextureHeight = mImageHeight;

		mPixelFormat = GL_ALPHA;
	}
}


void Texture::BlitPixel8(GLuint x, GLuint y, Texture& destination)
{
	// +(0,0)-------------------(x,0)+
	// |							 |
	// +(0,y)-------------------(x,y)+
	if (mPixels8 != nullptr && destination.mPixels8 != nullptr)
	{
		GLubyte* dPixels = destination.mPixels8;
		GLubyte* sPixels = mPixels8;
		for (unsigned i = 0; i < mImageHeight; ++i)
		{
			memcpy(&dPixels[(i + y)*destination.mTextureWidth + x], &sPixels[i*mTextureWidth], mImageWidth);
		}
	}
}


void Texture::FreeTuxture()
{
	if (mTexID != 0)
	{
		glDeleteTextures(1, &mTexID);
		mTexID = 0;
	}
	if (mPixels8 != nullptr)
	{
		delete[] mPixels8;
		mPixels8 = nullptr;
	}

	mTextureWidth = 0;
	mTextureHeight = 0;
}

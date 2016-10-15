#include "texture.h"


Texture::Texture()
	:mTexID(0),
	mTextureWidth(0),
	mTextureHeight(0),
	mImageWidth(0),
	mImageHeight(0),
	mPixels8(nullptr)
{

}


Texture::~Texture()
{
	FreeTuxture();
}


void Texture::CreatePixels8(GLuint imgWidth, GLuint imgHeight)
{
	if (imgWidth > 0 && imgHeight > 0)
	{
		FreeTuxture();

		GLuint size = imgWidth * imgHeight;
		mPixels8 = new GLubyte[size];
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

		glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, mTextureWidth, mTextureHeight, 0,
			GL_ALPHA, GL_UNSIGNED_BYTE, mPixels8);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

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

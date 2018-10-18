#include "texture.h"


#include <stdlib.h>
#include <stdio.h>
#include <png.h>
#include <iostream>

using namespace std;

bool loadPngImage(const char *name, int &outWidth, int &outHeight, bool &outHasAlpha, int &nbChanels, GLubyte **outData)
{
	png_structp png_ptr;
	png_infop info_ptr;
	unsigned int sig_read = 0;
	int color_type, interlace_type;
	bool gray = false;
	outHasAlpha = false;

	FILE *fp;
 
	if ((fp = fopen(name, "rb")) == NULL)
		return false;

	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	if (png_ptr == NULL)
	{
		fclose(fp);
		return false;
	}

	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		fclose(fp);
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		return false;
	}

	if (setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		fclose(fp);
		return false;
	}

	png_init_io(png_ptr, fp);
	png_set_sig_bytes(png_ptr, sig_read);

	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);

	png_uint_32 width, height;
	int bit_depth;
	png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
				 &interlace_type, NULL, NULL);
	outWidth = width;
	outHeight = height;

	if(color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA) gray = true;

	if(color_type == PNG_COLOR_TYPE_RGB_ALPHA || color_type == PNG_COLOR_TYPE_GRAY_ALPHA) outHasAlpha = true;

	nbChanels = (gray ? 1 : 3) + (outHasAlpha ? 1 : 0);
 
	unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
	*outData = (unsigned char*) malloc(row_bytes * outHeight);
 
	png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);
 
	for (int i = 0; i < outHeight; i++) {
		memcpy(*outData+(row_bytes * (outHeight-1-i)), row_pointers[i], row_bytes);
	}
 
	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
 
	fclose(fp);
 
	cout << "Image ("<< name <<") loaded " << width << "x" << height << " color(" << nbChanels << " chanels)" <<  endl;
	return true;
}

GLuint createTexture(const char *filename)
{
	GLubyte *textureImage;
	int width, height, nbChanels;
	bool hasAlpha;
	bool success = loadPngImage(filename, width, height, hasAlpha, nbChanels, &textureImage);
	if (!success) {
		cout << "Unable to load png file" << endl;
		return 0;
	}

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	GLint format;
	switch(nbChanels)
	{
		case 1:
			format = GL_RED;
			break;
		case 2:
			format = GL_RG;
		case 3:
			format = GL_RGB;
			break;
		case 4:
			format = GL_RGBA; 
			break;
	} 

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, textureImage);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	glBindTexture(GL_TEXTURE_2D, 0);

	return texture;
}
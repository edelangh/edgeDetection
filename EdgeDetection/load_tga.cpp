/** ===== OpenGL TGA Loader =====
 * Usage:
 *  - GLuint = load_tga_texture("blahhhh.tga");
 * Notes:
 *  - 8/16 bits, grayscale and colormaps aren't implemented
 *  - RLE is implemented
 * Warning:
 *  - I used a bunch of FILE, fopen, fread, etc... - Is it allowed?
 **/

#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <tchar.h>		// Header File For The Glaux Library
#include <stdio.h>
#include <iostream>
#include <map>

class BadTGAFormat
{
	const char	*what() const
	{
		return "Bad TGA Format! Only 24/32 bits are supported."
			" - Colormaps are ignored.";
	}
};


typedef struct	s_gl_texture
{
	GLint		width;
	GLint		height;

	GLenum		format;
	GLint		internalFormat;
	GLuint		id;

	GLubyte		*texels;
}				t_gl_texture;
#define PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop) )

PACK(
typedef struct			s_tga_header
{
	unsigned char		id_length;			/* size of id field */
	unsigned char		colormap_type;		/* 1 = color-mapped image */
	unsigned char		image_type;			/* compression type */

	short				cm_first_entry;		/* colormap origin */
	short				cm_length;			/* colormap length */
	unsigned char 		cm_size;			/* colormap size */

	short				x_origin;			/* x coord origin */
	short				y_origin;			/* y coord origin */

	short				width;				/* width */
	short				height;				/* height */

	unsigned char		pixel_depth;		/* bits per pixel */
	unsigned char		image_descriptor;	/* 24 bits = 0x00; 32 bits = 0x80 */
}   t_tga_header;);


static void		read_tga24(FILE *fp, t_gl_texture *texinfo)
{
	for (int i = 0; i < texinfo->width * texinfo->height; ++i)
	{
		texinfo->texels[(i * 3) + 2] = (GLubyte)fgetc(fp);
		texinfo->texels[(i * 3) + 1] = (GLubyte)fgetc(fp);
		texinfo->texels[(i * 3) + 0] = (GLubyte)fgetc(fp);
	}
}
static void		read_tga32(FILE *fp, t_gl_texture *texinfo)
{
	for (int i = 0; i < texinfo->width * texinfo->height; ++i)
	{
		texinfo->texels[(i * 4) + 2] = (GLubyte)fgetc(fp);
		texinfo->texels[(i * 4) + 1] = (GLubyte)fgetc(fp);
		texinfo->texels[(i * 4) + 0] = (GLubyte)fgetc(fp);
		texinfo->texels[(i * 4) + 3] = (GLubyte)fgetc(fp);
	}
}

static void		read_tga24_rle(FILE *fp, t_gl_texture *texinfo)
{
	GLubyte		*ptr = texinfo->texels;
	GLubyte		packet_header;
	GLubyte		rgb[3];
	int			i, size;

	while (ptr < texinfo->texels + (texinfo->width * texinfo->height) * 3)
	{
		packet_header = (GLubyte)fgetc(fp);
		size = 1 + (packet_header & 0x7f);

		if (packet_header & 0x80) /* RL packet */
		{
			fread(rgb, sizeof(GLubyte), 3, fp);
			for (i = 0; i < size; ++i, ptr += 3)
			{
				ptr[0] = rgb[2];
				ptr[1] = rgb[1];
				ptr[2] = rgb[0];
			}
		}
		else /* Non-RL packet */
		{
			for (i = 0; i < size; ++i, ptr += 3)
			{
				ptr[2] = (GLubyte)fgetc(fp);
				ptr[1] = (GLubyte)fgetc(fp);
				ptr[0] = (GLubyte)fgetc(fp);
			}
		}
	}
}
static void		read_tga32_rle(FILE *fp, t_gl_texture *texinfo)
{
	GLubyte		*ptr = texinfo->texels;
	GLubyte		packet_header;
	GLubyte		rgba[4];
	int			i, size;

	while (ptr < texinfo->texels + (texinfo->width * texinfo->height) * 4)
	{
		packet_header = (GLubyte)fgetc(fp);
		size = 1 + (packet_header & 0x7f);

		if (packet_header & 0x80) /* RL packet */
		{
			fread(rgba, sizeof(GLubyte), 4, fp);
			for (i = 0; i < size; ++i, ptr += 4)
			{
				ptr[0] = rgba[2];
				ptr[1] = rgba[1];
				ptr[2] = rgba[0];
				ptr[3] = rgba[3];
			}
		}
		else /* Non-RL packet */
		{
			for (i = 0; i < size; ++i, ptr += 4)
			{
				ptr[2] = (GLubyte)fgetc(fp);
				ptr[1] = (GLubyte)fgetc(fp);
				ptr[0] = (GLubyte)fgetc(fp);
				ptr[3] = (GLubyte)fgetc(fp);
			}
		}
	}
}


static void				get_texture_info(const t_tga_header *header,
		t_gl_texture *texinfo)
{
	texinfo->width = header->width;
	texinfo->height = header->height;

	if (header->pixel_depth <= 24)
	{
		texinfo->format = GL_RGB;
		texinfo->internalFormat = 3;
	}
	else
	{
		texinfo->format = GL_RGBA;
		texinfo->internalFormat = 4;
	}
}
static t_gl_texture		*read_tga_file(const char *filename)
{
	t_gl_texture	*texinfo;
	t_tga_header	header;
	FILE			*fp;

	// fopen allowed?!
	if (fopen_s(&fp, filename, "rb"))
	{
		return NULL;
	}
	fread(&header, sizeof(t_tga_header), 1, fp); // fread allowed?!

	if (!(texinfo = new t_gl_texture)) {
		return NULL;
	}
	get_texture_info(&header, texinfo);

	fseek(fp, header.id_length, SEEK_CUR);
	if (header.colormap_type)
		throw new BadTGAFormat;

	if (!(texinfo->texels = new GLubyte[texinfo->width
				* texinfo->height * texinfo->internalFormat]))
	{
		delete texinfo;
		return NULL;
	}

	switch (header.image_type)
	{
		case 2: /* Uncompressed 16-24-32 bits */
			switch (header.pixel_depth)
			{
				case 24:
					read_tga24(fp, texinfo);
					break;
				case 32:
					read_tga32(fp, texinfo);
					break;
				default:
					throw new BadTGAFormat;
					break;
			}
			break;

		case 10: /* RLE compressed 16-24-32 bits */
			switch (header.pixel_depth)
			{
				case 24:
					read_tga24_rle(fp, texinfo);
					break;
				case 32:
					read_tga32_rle(fp, texinfo);
					break;
				default:
					throw new BadTGAFormat;
					break;
			}
			break;

		default:
			throw new BadTGAFormat;
			break;
	}

	fclose(fp);
	return texinfo;
}

static std::map<std::string, GLuint>			_mapTga = std::map<std::string, GLuint>();

std::map<std::string, GLuint>	&getMapTga() {
	return (_mapTga);
}

GLuint					getTextureId(std::string &file) {
	return (_mapTga[file]);
}
GLuint					getTextureId(const char *file) {
	std::string tmp = file;
	return (_mapTga[tmp]);
}

GLuint					load_tga_texture(const char *filename)
{
	t_gl_texture	*tga_tex = NULL;
	GLuint			tex_id = -1;
	GLint			alignment;
	std::string		file = std::string(filename);

	if (!_mapTga[file]) {
		tga_tex = read_tga_file(filename);

		if (tga_tex && tga_tex->texels)
		{
			glGenTextures(1, &tga_tex->id);
			glBindTexture(GL_TEXTURE_2D, tga_tex->id);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glGetIntegerv(GL_UNPACK_ALIGNMENT, &alignment);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			//gluBuild2DMipmaps(GL_TEXTURE_2D, tga_tex->internalFormat, tga_tex->width,
			//		tga_tex->height, tga_tex->format, GL_UNSIGNED_BYTE, tga_tex->texels);
			glTexImage2D(GL_TEXTURE_2D, 0, tga_tex->internalFormat, tga_tex->width,
					tga_tex->height, 0, tga_tex->format, GL_UNSIGNED_BYTE, tga_tex->texels);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glPixelStorei(GL_UNPACK_ALIGNMENT, alignment);

			tex_id = tga_tex->id;

			delete [] tga_tex->texels;
			delete tga_tex;
			_mapTga[file] = tex_id;
		}
	}
	return (_mapTga[file]);
}

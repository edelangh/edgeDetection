#include "img2.h"
#include <stdlib.h>

t_img2*		img2_create(int width, int height)
{
	t_img2* i;

	i = (t_img2*)malloc(sizeof(t_img2));
	i->ddata = (double*)malloc(width * height * sizeof(double));
	i->width = width;
	i->height = height;
	return (i);
}

void		img2_destroy(t_img2* i)
{
	free(i->ddata);
	free(i);
}
/*
void		img2_copy_img(t_img2* dst, t_img* src)
{
	int	x, y;
	for (y = 0; y < src->height; ++y)
	{
		for (x = 0; x < src->width; ++x)
		{
			dst->ddata[y * dst->width + x] = src->udata[y * src->sl_div + x * src->bpp_div];
		}
	}
}

void		img_copy_img2(t_img* dst, t_img2* src)
{
	int	x, y;
	for (y = 0; y < src->height; ++y)
	{
		for  (x = 0; x < src->width; ++x)
		{
			dst->udata[y * dst->sl_div + x * dst->bpp_div] = src->ddata[y * src->width + x];
		}
	}
}
*/
void		img2_copy_img2(t_img2* dst, t_img2* src)
{
	int	x, y;
	for (y = 0; y < src->height; ++y)
	{
		for (x = 0; x < src->width; ++x)
		{
			dst->ddata[y * dst->width + x] = src->ddata[y * src->width + x];
		}
	}
}

void		img2_rgb2gray(t_img2* i)
{
	unsigned int	c;
	int				x, y;

	for (y = 0; y < i->height; ++y)
	{
		for (x = 0; x < i->width; ++x)
		{
			c = (unsigned int)i->ddata[y * i->width + x];
			i->ddata[y * i->width + x] = (((c >> 16) & 0xFF) + ((c >> 8) & 0xFF) + (c & 0xFF)) / 3;
		}
	}
}

void		img2_gray2rgb(t_img2* i)
{
	unsigned int	c;
	double 			d;
	int				x, y;

	for (y = 0; y < i->height; ++y)
	{
		for (x = 0; x < i->width; ++x)
		{
			d = i->ddata[y * i->width + x];
			if (d <= 0)
				c = 0;
			else if (d >= 0xFF)
				c = 0xFF;
			else
				c = (unsigned int)d;
			i->ddata[y * i->width + x] = c * (0xFFFFFF / 0xFF);
		}
	}
}

void		img2_mult_img2(t_img2* dst, t_img2* a, t_img2* b)
{
	int	x, y;
	for (y = 0; y < dst->height; ++y)
	{
		for (x = 0; x < dst->width; ++x)
		{
			dst->ddata[y * dst->width + x]
				= a->ddata[y * a->width + x]
				* b->ddata[y * b->width + x];
		}
	}
}

void		img2_div_img2(t_img2* dst, t_img2* a, t_img2* b)
{
	int	x, y;
	for (y = 0; y < dst->height; ++y)
	{
		for (x = 0; x < dst->width; ++x)
		{
			dst->ddata[y * dst->width + x]
				= a->ddata[y * a->width + x]
				/ b->ddata[y * b->width + x];
		}
	}
}

void		img2_add_img2(t_img2* dst, t_img2* a, t_img2* b)
{
	int	x, y;
	for (y = 0; y < dst->height; ++y)
	{
		for (x = 0; x < dst->width; ++x)
		{
			dst->ddata[y * dst->width + x]
				= a->ddata[y * a->width + x]
				+ b->ddata[y * b->width + x];
		}
	}
}

void		img2_sub_img2(t_img2* dst, t_img2* a, t_img2* b)
{
	int	x, y;
	for (y = 0; y < dst->height; ++y)
	{
		for (x = 0; x < dst->width; ++x)
		{
			dst->ddata[y * dst->width + x]
				= a->ddata[y * a->width + x]
				- b->ddata[y * b->width + x];
		}
	}
}

void		img2_add(t_img2* dst, double a)
{
	int	x, y;
	for (y = 0; y < dst->height; ++y)
	{
		for (x = 0; x < dst->width; ++x)
		{
			dst->ddata[y * dst->width + x] += a;
		}
	}
}

void		img2_ceuil(t_img2* dst, const double ceuil)
{
	int	x, y;
	for (y = 0; y < dst->height; ++y)
	{
		for (x = 0; x < dst->width; ++x)
		{
			if (dst->ddata[y * dst->width + x] > ceuil)
				dst->ddata[y * dst->width + x] = 0xFF;
			else
				dst->ddata[y * dst->width + x] = 0;
		}
	}
}
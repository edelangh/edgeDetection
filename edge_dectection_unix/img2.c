
#include "img2.h"

t_img2*		img2_create(int width, int height)
{
	t_img2* i;

	i = malloc(sizeof(t_img2));
	i->ddata = malloc(width * height * sizeof(double));
	i->width = width;
	i->height = height;
	return (i);
}

void		img2_destroy(t_img2* i)
{
	free(i->ddata);
	free(i);
}

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

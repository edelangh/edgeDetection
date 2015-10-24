
#include "img2.h"

void apply_kernel(t_img2 *img, t_kernel* k)
{
	int	w = k->width;
	int h = k->height;
	int x2;
	int	y2;
	double c;
	double*		out;

	out = malloc(sizeof(double) * img->width * img->height);
	int	x, y, j, i;
	for (y = 0; y < img->height; ++y)
	{
		for (x = 0; x < img->width; ++x)
		{
			c = 0;
			for (j = 0; j < h; ++j)
			{
				for (i = 0; i < w; ++i)
				{
					x2 = i + x - w/2;
					y2 = j + y - h/2;
					if (x2 < 0 || x2 >= img->width
						|| y2 < 0 || y2 >= img->height)
						continue ;
					c += img->ddata[y2 * img->width + x2]
						* k->ddata[j * k->width + i];
				}
			}
			out[y * img->width + x] = c;
		}
	}
	free(img->ddata);
	img->ddata = out;
}


#include "img2.h"

void apply_kernel(t_img2 *img, t_kernel* k)
{
	int	w = k->width;
	int h = k->height;
	int x2;
	int	y2;
	double c;

	int	x, y, j, i;
	for (y = 0; y < img->height; ++y)
	{
		for (x = 0; x < img->width; ++x)
		{
			c = 0;
			for (j = -h / 2; j <= h / 2; ++j)
			{
				for (i = -w / 2; i <= w / 2; ++i)
				{
					x2 = i + x;
					y2 = j + y;
					if (x2 < 0 || x2 > img->width
						|| y2 < 0 || y2 > img->height)
						continue ;
					c += img->ddata[y2 * img->width + x2]
						* k->ddata[(j + h / 2) * k->width + (i + w / 2)];
				}
			}
			img->ddata[y * img->width + x] = c;
		}
	}
}

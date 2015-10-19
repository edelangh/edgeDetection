
#include "ft_mlx.h"

int		max3(int a, int b, int c)
{
	int res;

	res = a;
	if (res < b)
		res = b;
	if (res < c)
		res = c;
	return (res);
}

int		min3(int a, int b, int c)
{
	int res;

	res = a;
	if (res > b)
		res = b;
	if (res > c)
		res = c;
	return (res);
}

void	lightness(t_img *i, int a)
{
	int	x;
	int	y;
	int	rvb[4];

	x = -1;
	while (++x < i->width)
	{
		y = -1;
		while (++y < i->height)
		{
			rvb[0] = i->data[x * i->bpp / 8 + y * i->sizeline];
			rvb[1] = i->data[x * i->bpp / 8 + y * i->sizeline + 1];
			rvb[2] = i->data[x * i->bpp / 8 + y * i->sizeline + 2];
			rvb[3] = ((max3(rvb[0], rvb[1], rvb[2]) + min3(rvb[0], rvb[1], rvb[2])) / 2);
			if (a == 2)
				rvb[3] = (rvb[0] + rvb[1] + rvb[2]) / 3;
			if (rvb[3] > 255 || rvb[3] < 0)
				rvb[3] = (rvb[3] > 0 ? 255 : 255);
			if (a == 1 || a == 2)
				i->udata[x * i->bpp_div + y * i->sl_div] = (rvb[3] << 16) | (rvb[3] << 8) | rvb[3];
			if (a == 3)
				i->udata[x * i->bpp_div + y * i->sl_div] = rvb[3];
			if ((i->udata[x * i->bpp_div + y * i->sl_div] > 0xFFFFFF))
				dprintf(1, "A%d\n", i->udata[x * i->bpp_div + y * i->sl_div]);
		}
	}
}

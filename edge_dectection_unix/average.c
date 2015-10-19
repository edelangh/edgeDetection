
#include <libft.h>
#include "edge_detection.h"

void	average(t_img	*i)
{
	int	y;
	int	x;
	unsigned int c;
	y = -1;
	while (++y < i->height)
	{
		x = -1;
		while (++x < i->width)
		{
			c = i->udata[y * i->sl_div + x * i->bpp_div];
			c = (c >> 16 & 0xFF) * 1/3
				+ (c >> 8 & 0xFF) * 1/3
				+ (c & 0xFF) * 1/3;
			i->udata[y * i->sl_div + x * i->bpp_div] = c << 16 | c << 8 | c;
		}
	}
}

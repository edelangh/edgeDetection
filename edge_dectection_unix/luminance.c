
#include <libft.h>
#include "edge_detection.h"

void	luminance(t_img	*i)
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
			c = (c >> 16 & 0xFF) * 0.299
				+ (c >> 8 & 0xFF) * 0.587
				+ (c & 0xFF) * 0.114;
			i->udata[y * i->sl_div + x * i->bpp_div] = c << 16 | c << 8 | c;
		}
	}
}

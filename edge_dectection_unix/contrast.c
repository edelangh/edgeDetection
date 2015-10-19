
#include <libft.h>
#include "edge_detection.h"

void	contrast_rgb(t_img *i, int contrast)
{
	int	y;
	int	x;
	int	r;
	int	g;
	int	b;
	unsigned int	c;

	if (!contrast)
		return ;
	y = -1;
	while (++y < i->height)
	{
		x = -1;
		while (++x < i->width)
		{
			r = (i->udata[y * i->sl_div + x * i->bpp_div] >> 16) & 0xFF;
			r = r / (255 / contrast);
			r = r * (255 / contrast);
			g = (i->udata[y * i->sl_div + x * i->bpp_div] >> 8) & 0xFF;
			g = g / (255 / contrast);
			g = g * (255 / contrast);
			b = (i->udata[y * i->sl_div + x * i->bpp_div]) & 0xFF;
			b = b / (255 / contrast);
			b = b * (255 / contrast);
	  		c = ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | ((b & 0xFF));
			i->udata[y * i->sl_div + x * i->bpp_div] = c;
		}
	}
}


void	contrast(t_img *i, int contrast)
{
	int	y;
	int	x;
	int	c;

	if (!contrast)
		return ;
	y = -1;
	while (++y < i->height)
	{
		x = -1;
		while (++x < i->width)
		{
			c = i->udata[y * i->sl_div + x * i->bpp_div] & 0xFF;
			c = c / (255 / contrast);
			c = c * (255 / contrast);
	  		c = ((c & 0xFF) << 16) | ((c & 0xFF) << 8) | ((c & 0xFF));
			i->udata[y * i->sl_div + x * i->bpp_div] = c;
		}
	}
}

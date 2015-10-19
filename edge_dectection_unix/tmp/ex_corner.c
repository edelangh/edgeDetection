
#include "edge_detection.h"
int harris_kernel2(t_env *e, t_img *img, int x, int y, int size)
{
  int i;
  int	j;
  int	s;
  int	c;
  int r;

  r = 0;
  s = size / 2 + 1;
  i = -s;
  while (++i < s)
  {
	j = -s;
	while (++j < s)
	{
	  if (y + i < 0 || x + j < 0 || y + i > img->height || x + j > img->width)
		continue ;
	  c = img->udata[(y + i) * img->sl_div + (x + j) * img->bpp_div] & 0xFF;
	  c -= img->udata[y * img->sl_div + x * img->bpp_div] & 0xFF;
	  c = c * c;
	  r += c;
	}
  }
  r = r / 10000;
  if (r > 255)
	r = 255;
  else if (r < 0)
	r = 0;
  return (r);
}
void	harris_kernel(t_env *e, t_img *img, int size)
{
  t_img	*tmp = ft_new_img(e->mlx, img->width, img->height);
  int x;
  int y;
  unsigned int c;
  char	**kernel;
  size = 3;
  ft_memcpy_uint(tmp->udata, img->udata, img->width * img->height);
  if (size <= 0)
	return ;
  x = -1;
  while (++x < img->width)
  {
	y = -1;
	while (++y < img->width)
	{
	  c = harris_kernel2(e, tmp, x, y, size);
	  c = (c << 16) | (c << 8) | (c);
	  img->udata[y * img->sl_div + x * img->bpp_div] = c;
	}
  }
  ft_destroy_img(e->mlx, tmp);
}

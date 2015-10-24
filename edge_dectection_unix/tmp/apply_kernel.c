
#include <libft.h>
#include "edge_detection.h"
#include <stdio.h>
#include <math.h>

void	apply_contrast_kernel(t_env *e, t_img *img, int intensity)
{
  t_img	*tmp = ft_new_img(e->mlx, img->width, img->height);
  int x;
  int y;
  int c;
  char	**kernel;

  ft_memcpy_uint(tmp->udata, img->udata, img->width * img->height);

  if (intensity <= 0)
	return ;
  kernel = e->contrast_kernel;
  y = -1;
  while (++y < img->height)
  {
	x = -1;
	while (++x < img->width)
	{
	  c = 0;
	  if (y > 0)
	  {
		if (x > 0)
		  c += (tmp->udata[(y - 1) * tmp->sl_div + (x - 1) * tmp->bpp_div] & 0xFF) * kernel[0][0] * intensity;
		c += (tmp->udata[(y - 1) * tmp->sl_div + (x) * tmp->bpp_div] & 0xFF) * kernel[0][1] * intensity;
		if (x < img->width)
		  c += (tmp->udata[(y - 1) * tmp->sl_div + (x + 1) * tmp->bpp_div] & 0xFF) * kernel[0][2] * intensity;
	  }
	  if (x > 0)
		c += (tmp->udata[(y) * tmp->sl_div + (x - 1) * tmp->bpp_div] & 0xFF) * kernel[1][0] * intensity;
	  c += (tmp->udata[(y) * tmp->sl_div + (x) * tmp->bpp_div] & 0xFF) * kernel[1][1] * intensity;
	  if (x < img->width)
		c += (tmp->udata[(y) * tmp->sl_div + (x + 1) * tmp->bpp_div] & 0xFF) * kernel[1][2] * intensity;

	  if (y + 1 < img->height)
	  {
		if (x > 0)
		  c += (tmp->udata[(y + 1) * tmp->sl_div + (x - 1) * tmp->bpp_div] & 0xFF) * kernel[2][0] * intensity;
		c += (tmp->udata[(y + 1) * tmp->sl_div + (x) * tmp->bpp_div] & 0xFF) * kernel[2][1] * intensity;
		if (x < img->width)
		  c += (tmp->udata[(y + 1) * tmp->sl_div + (x + 1) * tmp->bpp_div] & 0xFF) * kernel[2][2] * intensity;
	  }
		if (c > 0xFF)
			c = 0xFF;
	  c = (c << 16) | (c << 8) | (c);
	  img->udata[y * img->sl_div + x * img->bpp_div] = c;
	}
  }
  ft_destroy_img(e->mlx, tmp);
}


void	apply_sobel_kernel(t_env *e, t_img *img, int intensity)
{
  t_img	*tmp = ft_new_img(e->mlx, img->width, img->height);
  int x;
  int y;
  int c;
  char	**kernel;

  ft_memcpy_uint(tmp->udata, img->udata, img->width * img->height);

  if (intensity <= 0)
	return ;
  // first kernel
  kernel = e->sobel_kernel_w;
  y = -1;
  while (++y < img->height)
  {
	x = -1;
	while (++x < img->width)
	{
	  c = 0;
	  if (y > 0)
	  {
		if (x > 0)
		  c += (tmp->udata[(y - 1) * tmp->sl_div + (x - 1) * tmp->bpp_div] & 0xFF) * kernel[0][0] * intensity;
		c += (tmp->udata[(y - 1) * tmp->sl_div + (x) * tmp->bpp_div] & 0xFF) * kernel[0][1] * intensity;
		if (x < img->width)
		  c += (tmp->udata[(y - 1) * tmp->sl_div + (x + 1) * tmp->bpp_div] & 0xFF) * kernel[0][2] * intensity;
	  }
	  if (x > 0)
		c += (tmp->udata[(y) * tmp->sl_div + (x - 1) * tmp->bpp_div] & 0xFF) * kernel[1][0] * intensity;
	  c += (tmp->udata[(y) * tmp->sl_div + (x) * tmp->bpp_div] & 0xFF) * kernel[1][1] * intensity;
	  if (x < img->width)
		c += (tmp->udata[(y) * tmp->sl_div + (x + 1) * tmp->bpp_div] & 0xFF) * kernel[1][2] * intensity;

	  if (y + 1 < img->height)
	  {
		if (x > 0)
		  c += (tmp->udata[(y + 1) * tmp->sl_div + (x - 1) * tmp->bpp_div] & 0xFF) * kernel[2][0] * intensity;
		c += (tmp->udata[(y + 1) * tmp->sl_div + (x) * tmp->bpp_div] & 0xFF) * kernel[2][1] * intensity;
		if (x < img->width)
		  c += (tmp->udata[(y + 1) * tmp->sl_div + (x + 1) * tmp->bpp_div] & 0xFF) * kernel[2][2] * intensity;
	  }
		if (c > 0xFF)
			c = 0xFF;
	  c = (c << 16) | (c << 8) | (c);
	  img->udata[y * img->sl_div + x * img->bpp_div] = c;
	}
  }
  // second kernel
  kernel = e->sobel_kernel_h;
  y = -1;
  while (++y < img->height)
  {
	x = -1;
	while (++x < img->width)
	{
	  c = 0;
	  if (y > 0)
	  {
		if (x > 0)
		  c += (tmp->udata[(y - 1) * tmp->sl_div + (x - 1) * tmp->bpp_div] & 0xFF) * kernel[0][0] * intensity;
		c += (tmp->udata[(y - 1) * tmp->sl_div + (x) * tmp->bpp_div] & 0xFF) * kernel[0][1] * intensity;
		if (x < img->width)
		  c += (tmp->udata[(y - 1) * tmp->sl_div + (x + 1) * tmp->bpp_div] & 0xFF) * kernel[0][2] * intensity;
	  }
	  if (x > 0)
		c += (tmp->udata[(y) * tmp->sl_div + (x - 1) * tmp->bpp_div] & 0xFF) * kernel[1][0] * intensity;
	  c += (tmp->udata[(y) * tmp->sl_div + (x) * tmp->bpp_div] & 0xFF) * kernel[1][1] * intensity;
	  if (x < img->width)
		c += (tmp->udata[(y) * tmp->sl_div + (x + 1) * tmp->bpp_div] & 0xFF) * kernel[1][2] * intensity;

	  if (y + 1 < img->height)
	  {
		if (x > 0)
		  c += (tmp->udata[(y + 1) * tmp->sl_div + (x - 1) * tmp->bpp_div] & 0xFF) * kernel[2][0] * intensity;
		c += (tmp->udata[(y + 1) * tmp->sl_div + (x) * tmp->bpp_div] & 0xFF) * kernel[2][1] * intensity;
		if (x < img->width)
		  c += (tmp->udata[(y + 1) * tmp->sl_div + (x + 1) * tmp->bpp_div] & 0xFF) * kernel[2][2] * intensity;
	  }
	  c = (c * c)
		+ ((img->udata[y * img->sl_div + x * img->bpp_div] & 0xFF)
			* (img->udata[y * img->sl_div + x * img->bpp_div] & 0xFF));
	  c = sqrt(c);
		if (c > 0xFF)
			c = 0xFF;
	  c = (c << 16) | (c << 8) | (c);
	  img->udata[y * img->sl_div + x * img->bpp_div] = c;
	}
  }

  ft_destroy_img(e->mlx, tmp);
}

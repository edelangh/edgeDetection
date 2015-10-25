
#include "edge_detection.h"

//sigma 1-4
#define sigma 1
//thresh 1000
#define thresh 1000

static void  init_ix(double *ix, t_img* i)
{
  unsigned int x, y;
  double c;
  double **kernel;
  double intensity = 1;

  // init kernel
  kernel = malloc(sizeof(double*) * 3);
  kernel[0] = malloc(sizeof(double) * 3);
  kernel[1] = malloc(sizeof(double) * 3);
  kernel[2] = malloc(sizeof(double) * 3);

  kernel[0][0] = -1; kernel[0][1] = 0; kernel[0][2] = 1;
  kernel[1][0] = -1; kernel[1][1] = 0; kernel[1][2] = 1;
  kernel[2][0] = -1; kernel[2][1] = 0; kernel[2][2] = 1;

  y = -1;
  while (++y < i->height)
  {
	x = -1;
	while (++x < i->width)
	{
	  c = 0;
	  if (y > 0)
	  {
		if (x > 0)
		  c += ((i->udata[(y - 1) * i->sl_div + (x - 1) * i->bpp_div] & 0xFF)) * kernel[0][0] * intensity;
		c += ((i->udata[(y - 1) * i->sl_div + (x) * i->bpp_div] & 0xFF)) * kernel[0][1] * intensity;
		if (x < i->width)
		  c += ((i->udata[(y - 1) * i->sl_div + (x + 1) * i->bpp_div] & 0xFF)) * kernel[0][2] * intensity;
	  }
	  if (x > 0)
		c += ((i->udata[(y) * i->sl_div + (x - 1) * i->bpp_div] & 0xFF)) * kernel[1][0] * intensity;
	  c += ((i->udata[(y) * i->sl_div + (x) * i->bpp_div] & 0xFF)) * kernel[1][1] * intensity;
	  if (x < i->width)
		c += ((i->udata[(y) * i->sl_div + (x + 1) * i->bpp_div] & 0xFF)) * kernel[1][2] * intensity;

	  if (y + 1 < i->height)
	  {
		if (x > 0)
		  c += ((i->udata[(y + 1) * i->sl_div + (x - 1) * i->bpp_div] & 0xFF)) * kernel[2][0] * intensity;
		c += ((i->udata[(y + 1) * i->sl_div + (x) * i->bpp_div] & 0xFF)) * kernel[2][1] * intensity;
		if (x < i->width)
		  c += ((i->udata[(y + 1) * i->sl_div + (x + 1) * i->bpp_div] & 0xFF)) * kernel[2][2] * intensity;
	  }
	  ix[(y) * i->width + (x)] = c;
	}
  }
  free(kernel[0]);
  free(kernel[1]);
  free(kernel[2]);
  free(kernel);
}

static void  init_iy(double *iy, t_img* i)
{
  unsigned int x, y;
  double c;
  double **kernel;
  double intensity = 1;
  // init kernel
  kernel = malloc(sizeof(double*) * 3);
  kernel[0] = malloc(sizeof(double) * 3);
  kernel[1] = malloc(sizeof(double) * 3);
  kernel[2] = malloc(sizeof(double) * 3);

  kernel[0][0] = -1; kernel[0][1] = -1; kernel[0][2] = -1;
  kernel[1][0] = 0; kernel[1][1] = 0; kernel[1][2] = 0;
  kernel[2][0] = 1; kernel[2][1] = 1; kernel[2][2] = 1;

  y = -1;
  while (++y < i->height)
  {
	x = -1;
	while (++x < i->width)
	{
	  c = 0;
	  if (y > 0)
	  {
		if (x > 0)
		  c += (i->udata[(y - 1) * i->sl_div + (x - 1) * i->bpp_div] & 0xFF) * kernel[0][0] * intensity;
		c += (i->udata[(y - 1) * i->sl_div + (x) * i->bpp_div] & 0xFF) * kernel[0][1] * intensity;
		if (x < i->width)
		  c += (i->udata[(y - 1) * i->sl_div + (x + 1) * i->bpp_div] & 0xFF) * kernel[0][2] * intensity;
	  }
	  if (x > 0)
		c += (i->udata[(y) * i->sl_div + (x - 1) * i->bpp_div] & 0xFF) * kernel[1][0] * intensity;
	  c += (i->udata[(y) * i->sl_div + (x) * i->bpp_div] & 0xFF) * kernel[1][1] * intensity;
	  if (x < i->width)
		c += (i->udata[(y) * i->sl_div + (x + 1) * i->bpp_div] & 0xFF) * kernel[1][2] * intensity;

	  if (y + 1 < i->height)
	  {
		if (x > 0)
		  c += (i->udata[(y + 1) * i->sl_div + (x - 1) * i->bpp_div] & 0xFF) * kernel[2][0] * intensity;
		c += (i->udata[(y + 1) * i->sl_div + (x) * i->bpp_div] & 0xFF) * kernel[2][1] * intensity;
		if (x < i->width)
		  c += (i->udata[(y + 1) * i->sl_div + (x + 1) * i->bpp_div] & 0xFF) * kernel[2][2] * intensity;
	  }
	  iy[(y) * i->width + (x)] = c;
	}
  }
  free(kernel[0]);
  free(kernel[1]);
  free(kernel[2]);
  free(kernel);
}

void	init_ixy(double* ixy, double* ix, double* iy, unsigned int width, unsigned int height)
{
  unsigned int	x, y;

  y = 0;
  while (y < height)
  {
	x = 0;
	while (x < width)
	{
	  ixy[(y) * width + (x)]
		= ix[(y) * width + (x)]
		* iy[(y) * width + (x)];
	  ix[y * width + x] *= ix[y * width + x];
	  iy[y * width + x] *= iy[y * width + x];

	  ++x;
	}
	++y;
  }
}

void harris(t_img* img, double* ix, double* iy, double* ixy)
{
  unsigned int x, y;
  double max = 0;
  double t;

  y = 0;
  while (y < img->height)
  {
	x = 0;
	while (x < img->width)
	{
	  t = (((ix[(y) * img->width + (x)] * iy[(y) * img->width + (x)])
			- (ixy[(y) * img->width + (x)] * ixy[(y) * img->width + (x)]))
		  / (ix[(y) * img->width + (x)]
			+ iy[(y) * img->width + (x)]
			+ EPS
			)
		  );
	dprintf(1, "A: %f\n", ixy[(y) * img->width + (x)] * ixy[(y) * img->width + (x)]);
	  img->udata[(y) * img->sl_div + (x) * img->bpp_div] = t;
	  if (t > max)
		max = t;
	  ++x;
	}
	++y;	
  }
  dprintf(1, "Max:%f\n", max);
  max = 0xFF / max;
  y = 0;
  while (y < img->height)
  {
	x = 0;
	while (x < img->width)
	{
	  ++x;
	  img->udata[(y) * img->sl_div + (x) * img->bpp_div] *= max;
	  /*    if (img->udata[(y) * img->sl_div + (x) * img->bpp_div] < max - )
			img->udata[(y) * img->sl_div + (x) * img->bpp_div] = 0;
			else
			img->udata[(y) * img->sl_div + (x) * img->bpp_div] = 0xFFFFFF;
	   */
	}
	++y;
  }
}

void	harris_kernel(t_env *e, t_img *img, int size)
{
  //  t_img	*ix = ft_new_img(e->mlx, img->width, img->height);
  //  t_img	*iy = ft_new_img(e->mlx, img->width, img->height);
  //  t_img	*ixy = ft_new_img(e->mlx, img->width, img->height);
  double* ix;
  double* iy;
  double* ixy;

  ix = malloc(sizeof(double) * img->width * img->height);
  iy = malloc(sizeof(double) * img->width * img->height);
  ixy = malloc(sizeof(double) * img->width * img->height);

  init_ix(ix, img);
  init_iy(iy, img);

  init_ixy(ixy, ix, iy, img->width, img->height);

  //  cim = (Ix2.*Iy2 - Ixy.^2)./(Ix2 + Iy2 + eps);
  harris(img, ix, iy, ixy);

  free(ix);
  free(iy);
  free(ixy);
  // ft_destroy_img(e->mlx, ix);
  // ft_destroy_img(e->mlx, iy);
  // ft_destroy_img(e->mlx, ixy);
}

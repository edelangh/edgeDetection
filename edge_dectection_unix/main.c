
#include "edge_detection.h"
#include <math.h>
#include "mlx_key.h"

void		img2_ceuil(t_img2* dst, double ceuil)
{
  int	x, y;
  for (y = 0; y < dst->height; ++y)
  {
	for (x = 0; x < dst->width; ++x)
	{
	  if (dst->ddata[y * dst->width + x] > ceuil)
		dst->ddata[y * dst->width + x] = 0xFF;
	  else
		dst->ddata[y * dst->width + x] = 0;
	}
  }
}

void	harris2(t_img* tmp)
{
  t_kernel*	k;
  t_kernel*	sx;
  t_kernel*	sy;
  t_img2*	iy;
  t_img2*	ix;
  t_img2*	ixy;
  t_img2*	cim;

  k = load_kernel("kernel/gaussian_5x5");
  sx = load_kernel("kernel/sobelx_3x3");
  sy = load_kernel("kernel/sobely_3x3");
  ix = img2_create(tmp->width, tmp->height);
  iy = img2_create(tmp->width, tmp->height);
  ixy = img2_create(tmp->width, tmp->height);
  cim = img2_create(tmp->width, tmp->height);

  img2_copy_img(ix, tmp);
  img2_copy_img(iy, tmp);
  img2_rgb2gray(ix);
  img2_rgb2gray(iy);

  apply_kernel(ix, sx);
  apply_kernel(iy, sy);

  img2_mult_img2(ixy, ix, iy);
  apply_kernel(ixy, k);

  img2_mult_img2(ix, ix, ix);
  apply_kernel(ix, k);
  img2_mult_img2(iy, iy, iy);
  apply_kernel(iy, k);

  // (Ix2.*Iy2 - Ixy.^2)
  img2_mult_img2(cim, ix, iy);
  img2_mult_img2(ixy, ixy, ixy);
  img2_sub_img2(cim, cim, ixy);
  // (Ix2 + Iy2 + eps)
  img2_add_img2(ix, ix, iy);
  img2_add(ix, EPS);
  // cim = (Ix2.*Iy2 - Ixy.^2)./(Ix2 + Iy2 + eps); % Harris corner measure
  img2_div_img2(cim, cim, ix);

  img2_ceuil(cim, 3000);
  img2_gray2rgb(cim);
  img_copy_img2(tmp, cim);

  kernel_destroy(k);
  kernel_destroy(sx);
  kernel_destroy(sy);
  img2_destroy(ix);
  img2_destroy(iy);
  img2_destroy(ixy);
  img2_destroy(cim);
}

int	draw(t_env *e)
{
  ft_memcpy_uint(e->tmp->udata, e->img->udata, e->img->width * e->img->height);
  harris2(e->tmp);
  /*
	 if (e->contrast_rgb > 0)
	 contrast_rgb(e->tmp, e->contrast_rgb - 1);
	 if (e->luminance)
	 luminance(e->tmp);
	 if (e->average)
	 average(e->tmp);
	 if (e->contrast > 0)
	 contrast(e->tmp, e->contrast - 1);
	 lightness(e->tmp, e->lightness);
	 gaussian(e->tmp, e->gaussian);
	 if (e->contrast_intensity > 0)
	 apply_contrast_kernel(e, e->tmp, e->contrast_intensity);
	 if (e->sobel_intensity > 0)
	 apply_sobel_kernel(e, e->tmp, e->sobel_intensity);
	 if (e->harris_intensity > 0)
	 harris_kernel(e, e->tmp, e->harris_intensity);
   */
  mlx_put_image_to_window(e->mlx, e->win, e->img->img, 0, 0);
  mlx_put_image_to_window(e->mlx, e->win, e->tmp->img, WIN_WIDTH, 0);
  return (1);
}

int	key(int key, t_env *e)
{
  dprintf(1, "key: %d\n", key);
  if (key == KEY_ESCAPE)
	exit(dprintf(2, "exit\n"));
  else if (key == KEY_1)
	e->lightness = (e->lightness + 1) % 4;
  else if (key == KEY_2)
	e->gaussian = fmod((e->gaussian + 0.5), 5.5);
  else if (key == KEY_3)
	e->sobel_intensity = (e->sobel_intensity + 1) % 4;
  else if (key == KEY_4)
	e->luminance = !e->luminance;
  else if (key == KEY_5)
	e->average = !e->average;
  else if (key == KEY_6)
	e->contrast = (e->contrast == 0 ? 255 : e->contrast >> 1);
  else if (key == KEY_7)
	e->contrast_rgb = (e->contrast_rgb == 0 ? 255 : e->contrast_rgb >> 1);
  else if (key == KEY_8)
	e->contrast_intensity = (e->contrast_intensity + 1) % 4;
  else if (key == KEY_9)
	e->harris_intensity = !e->harris_intensity * 6;
  else if (key == KEY_0)
  {
	e->lightness = 0;
	e->gaussian = 0;
	e->sobel_intensity = 0;
	e->luminance = 0;
	e->average = 0;
	e->contrast = 0;
	e->contrast_rgb = 0;
	e->contrast_intensity = 0;
	e->harris_intensity = 0;
  }
  else if (key == 'e')
  {
	ft_export_xpm(e->tmp, "test.xpm");
	exit(1);
  }
  else if (key == 'h')
  {
	printf(""
		"1: lightness\n"
		"2: gaussian\n"
		"3: sobel_intensity\n"
		"4: luminance\n"
		"5: average\n"
		"6: contrast\n"
		"7: contrast_rgb\n"
		"8: contrast_intensity\n"
		"9: harris_intensity\n");
  }
  dprintf(1, "l:%d/3 g:%f/5 s:%d/3 l:%d a:%d c_gris:%d/255 c_rgb:%d/255 c:%d/3 h:%d\n"
	  , e->lightness, e->gaussian
	  , e->sobel_intensity, e->luminance
	  , e->average, e->contrast - 1
	  , e->contrast_rgb - 1, e->contrast_intensity
	  , e->harris_intensity);
  draw(e);
  return (1);
}

void	init(t_env *e, char **av)
{
  t_img	*tmp;
  int	size[4];
  int	pos[] = {0, 0, 0, 0};

  // init contrast_kernel
  e->contrast_kernel = malloc(sizeof(char*) * 3);
  e->contrast_kernel[0] = malloc(sizeof(char) * 3);
  e->contrast_kernel[1] = malloc(sizeof(char) * 3);
  e->contrast_kernel[2] = malloc(sizeof(char) * 3);

  e->contrast_kernel[0][0] = 0; e->contrast_kernel[0][1] = -1; e->contrast_kernel[0][2] = 0;
  e->contrast_kernel[1][0] = -1; e->contrast_kernel[1][1] = 5; e->contrast_kernel[1][2] = -1;
  e->contrast_kernel[2][0] = 0; e->contrast_kernel[2][1] = -1; e->contrast_kernel[2][2] = 0;

  // init sobel_kernel_w
  e->sobel_kernel_w = malloc(sizeof(char*) * 3);
  e->sobel_kernel_w[0] = malloc(sizeof(char) * 3);
  e->sobel_kernel_w[1] = malloc(sizeof(char) * 3);
  e->sobel_kernel_w[2] = malloc(sizeof(char) * 3);

  e->sobel_kernel_w[0][0] = 1; e->sobel_kernel_w[0][1] = 2; e->sobel_kernel_w[0][2] = 1;
  e->sobel_kernel_w[1][0] = 0; e->sobel_kernel_w[1][1] = 0; e->sobel_kernel_w[1][2] = 0;
  e->sobel_kernel_w[2][0] = -1; e->sobel_kernel_w[2][1] = -2; e->sobel_kernel_w[2][2] = -1;

  // init sobel_kernel_h
  e->sobel_kernel_h = malloc(sizeof(char*) * 3);
  e->sobel_kernel_h[0] = malloc(sizeof(char) * 3);
  e->sobel_kernel_h[1] = malloc(sizeof(char) * 3);
  e->sobel_kernel_h[2] = malloc(sizeof(char) * 3);

  e->sobel_kernel_h[0][0] = -1; e->sobel_kernel_h[0][1] = 0; e->sobel_kernel_h[0][2] = 1;
  e->sobel_kernel_h[1][0] = -2; e->sobel_kernel_h[1][1] = 0; e->sobel_kernel_h[1][2] = 2;
  e->sobel_kernel_h[2][0] = -1; e->sobel_kernel_h[2][1] = 0; e->sobel_kernel_h[2][2] = 1;

  // init img and tmp
  tmp = ft_load_img(e->mlx, av[1]);
  e->img = ft_new_img(e->mlx, WIN_WIDTH, WIN_HEIGHT);
  e->tmp = ft_new_img(e->mlx, WIN_WIDTH, WIN_HEIGHT);
  size[0] = tmp->width;
  size[1] = tmp->height;
  size[2] = WIN_WIDTH;
  size[3] = WIN_HEIGHT;
  ft_resize_img(e->img, tmp, pos, size);
}

int	main(int ac, char **av)
{
  t_env	e;

  ft_bzero(&e, sizeof(t_env));
  if (ac < 2)
	exit(dprintf(2, "Usage: %s <img>\n", av[0]));
  if ((e.mlx = mlx_init()))
  {
	if ((e.win = mlx_new_window(e.mlx, WIN_WIDTH * 2, WIN_HEIGHT, WIN_TITLE)))
	{
	  init(&e, av);
	  mlx_expose_hook(e.win, draw, &e);
	  mlx_key_hook(e.win, key, &e);
	  mlx_loop_hook(e.mlx, draw, &e);
	  mlx_loop(e.mlx);
	}
  }
  if (!e.mlx || !e.win)
	exit(dprintf(2, "Error on load mlx !\n"));
  return (0);
}

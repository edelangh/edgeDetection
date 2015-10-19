

#ifndef EDGE_DETECTION_H
# define EDGE_DETECTION_H

# include "libft.h"
# include "ft_mlx.h"
# include <string.h>
#include <stdio.h>

# define WIN_WIDTH 400
# define WIN_HEIGHT 400
# define WIN_TITLE "edge_detection"

typedef struct	s_env
{
	void	*mlx;
	void	*win;
	t_img	*img;
	t_img	*tmp;
	int		lightness;
	int		luminance;
	int		average;
	int		contrast;
	int		contrast_rgb;
	double	gaussian;
	char	**sobel_kernel_w;
	char	**sobel_kernel_h;
	char	**contrast_kernel;
	int		sobel_intensity;
	int		contrast_intensity;
	int		harris_intensity;
}		t_env;

void	lightness(t_img *i, int a);
void	gaussian(t_img *i, double a);
void	apply_sobel_kernel(t_env *e, t_img *img, int intensity);
void	apply_contrast_kernel(t_env *e, t_img *img, int intensity);
void	luminance(t_img	*i);
void	average(t_img	*i);
void	contrast(t_img *i, int contrast);
void	contrast_rgb(t_img *i, int contrast);

// Tools
void	ft_memcpy_uint(unsigned int* dest, unsigned int* src, unsigned int size);

// corner
void	harris_kernel(t_env *e, t_img *img, int size);
#endif

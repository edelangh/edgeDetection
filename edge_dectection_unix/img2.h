
#ifndef IMG2_H
#define IMG2_H

#include <ft_mlx.h>

typedef struct s_img2
{
	double*		ddata;
	int			width;
	int			height;
}				t_img2;

#define t_kernel t_img2

#define MAX_KERNEL_SIZE 42
// jai juste pas envie de me faire chier

t_kernel*	load_kernel(char *src);
void		kernel_destroy(t_kernel* k);
void		apply_kernel(t_img2 *i, t_kernel* k);

t_img2*		img2_create(int width, int height);
void		img2_destroy(t_img2* i);
void		img2_copy_img(t_img2* dst, t_img* src);
void		img_copy_img2(t_img* dst, t_img2* src);
void		img2_copy_img2(t_img2* dst, t_img2* src);
void		img2_rgb2gray(t_img2* i);
void		img2_gray2rgb(t_img2* i);

void		img2_mult_img2(t_img2* dst, t_img2* a, t_img2* b);
void		img2_div_img2(t_img2* dst, t_img2* a, t_img2* b);
void		img2_add_img2(t_img2* dst, t_img2* a, t_img2* b);
void		img2_sub_img2(t_img2* dst, t_img2* a, t_img2* b);

void		img2_add(t_img2* dst, double a);
#endif

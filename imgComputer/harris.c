#include "img2.h"

void	harris(t_img2* tmp, int ceuil)
{
	t_kernel*	k;
	t_kernel*	sx;
	t_kernel*	sy;
	t_img2*	iy;
	t_img2*	ix;
	t_img2*	ixy;
	t_img2*	cim;

	k = load_kernel("C:\\Users\\Eric\\Work\\edgeDetection\\Debug\\kernel/gaussian_5x5");
	sx = load_kernel("C:\\Users\\Eric\\Work\\edgeDetection\\Debug\\kernel/sobelx_3x3");
	sy = load_kernel("C:\\Users\\Eric\\Work\\edgeDetection\\Debug\\kernel/sobely_3x3");
	ix = img2_create(tmp->width, tmp->height);
	iy = img2_create(tmp->width, tmp->height);
	ixy = img2_create(tmp->width, tmp->height);
	cim = img2_create(tmp->width, tmp->height);

	img2_copy_img2(ix, tmp);
	img2_copy_img2(iy, tmp);
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

	img2_ceuil(cim, ceuil);
	img2_gray2rgb(cim);
	img2_copy_img2(tmp, cim);

	kernel_destroy(k);
	kernel_destroy(sx);
	kernel_destroy(sy);
	img2_destroy(ix);
	img2_destroy(iy);
	img2_destroy(ixy);
	img2_destroy(cim);
}

# include "edge_detection.h"
# include <math.h>

void boxBlur_4 (int *scl, int *tcl, int w, int h, double r);
void boxBlurH_4 (int *scl, int *tcl, int w, int h, double r);
void boxBlurT_4 (int *scl, int *tcl, int w, int h, double r);

int *boxesForGauss(double sigma, int n)  // standard deviation, number of boxes
{
	double wIdeal = sqrt((12 * sigma * sigma / n) + 1);  // Ideal averaging filter width 
	int wl = floor(wIdeal);
	int	i;

	if(wl % 2 == 0)
			wl--;
	int wu = wl + 2;
	double mIdeal = (12 * sigma * sigma - n * wl * wl - 4 * n * wl - 3 * n) / (-4 * wl - 4);
	int m = round(mIdeal);
	// var sigmaActual = Math.sqrt( (m*wl*wl + (n-m)*wu*wu - n)/12 );

	int *sizes = malloc(sizeof(int) * WIN_WIDTH * WIN_HEIGHT);
	for (i = 0; i < n; i++) 
			sizes[i] = (i < m ? wl : wu);
	return (sizes);
}

void gaussBlur_4 (int *scl, int *tcl, int w, int h, double r) {
	int *bxs = boxesForGauss(r, 3);

	boxBlur_4 (scl, tcl, w, h, (bxs[0]-1)/2);
	boxBlur_4 (tcl, scl, w, h, (bxs[1]-1)/2);
	boxBlur_4 (scl, tcl, w, h, (bxs[2]-1)/2);
}

void boxBlur_4 (int *scl, int *tcl, int w, int h, double r)
{
	int	i;

		for (i = 0; i < w * h; i++)
{
			tcl[i] = scl[i];
}
		boxBlurH_4(tcl, scl, w, h, r);
		boxBlurT_4(scl, tcl, w, h, r);
}

void boxBlurH_4 (int *scl, int *tcl, int w, int h, double r) {
		double iarr = 1 / (r+r+1);
		int	i;
		int	j;
		for(i = 0; i < h; i++)
{
				double ti = i*w, li = ti, ri = ti+r;
				double fv = scl[(int)ti], lv = scl[(int)(ti+w-1)], val = (r+1)*fv;
				for(j=0; j<r; j++)
					val += scl[(int)(ti+j)];
				for(j = 0 ; j <= r ; j++)
				{
					val += scl[(int)ri++] - fv;
					tcl[(int)ti++] = round(val*iarr);
				}
				for(j = r + 1; j < w - r; j++)
				{
					val += scl[(int)ri++] - scl[(int)li++];
					tcl[(int)ti++] = round(val*iarr);
				}
				for(j = w - r; j < w; j++)
				{
					val += lv - scl[(int)li++];
					tcl[(int)ti++] = round(val * iarr);
				}
		}
}
void boxBlurT_4 (int *scl, int *tcl, int w, int h, double r)
{
		double  iarr = 1 / (r+r+1);
		int	i;
		int	j;

		for(i=0; i<w; i++) {
				int ti = i, li = ti, ri = ti+r*w;
				int fv = scl[(int)ti], lv = scl[(int)(ti+w*(h-1))], val = (r+1)*fv;
				for(j=0; j<r; j++) val += scl[(int)(ti+j*w)];
				for(j=0  ; j<=r ; j++) { val += scl[(int)ri] - fv     ;  tcl[(int)ti] = round(val*iarr);  ri+=w; ti+=w; }
				for(j=r+1; j<h-r; j++) { val += scl[(int)ri] - scl[(int)li];  tcl[(int)ti] = round(val*iarr);  li+=w; ri+=w; ti+=w; }
				for(j=h-r; j<h  ; j++) { val += lv      - scl[(int)li];  tcl[(int)ti] = round(val*iarr);  li+=w; ti+=w; }
		}
}

void	gaussian(t_img *img, double a)
{
	int	*tmp[3];
	int	*cpy[3];
	int	x;
	int	y;

	tmp[0] = malloc(sizeof(int) * img->width * img->height);
	tmp[1] = malloc(sizeof(int) * img->width * img->height);
	tmp[2] = malloc(sizeof(int) * img->width * img->height);
	cpy[0] = malloc(sizeof(int) * img->width * img->height);
	cpy[1] = malloc(sizeof(int) * img->width * img->height);
	cpy[2] = malloc(sizeof(int) * img->width * img->height);
	y = -1;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
		{
			cpy[0][x + y * img->height] = img->udata[x * img->bpp_div + y * img->sl_div] >> 16 & 0xFF;
			cpy[1][x + y * img->height] = img->udata[x * img->bpp_div + y * img->sl_div] >> 8 & 0xFF;
			cpy[2][x + y * img->height] = img->udata[x * img->bpp_div + y * img->sl_div] & 0xFF;
		}
	}
	gaussBlur_4(cpy[0], tmp[0], img->width, img->height, a);
	gaussBlur_4(cpy[1], tmp[1], img->width, img->height, a);
	gaussBlur_4(cpy[2], tmp[2], img->width, img->height, a);
	y = -1;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
		{
			img->udata[x * img->bpp_div + y * img->sl_div] = tmp[2][x + y * img->height];
			img->udata[x * img->bpp_div + y * img->sl_div] |= tmp[1][x + y * img->height] << 8;
			img->udata[x * img->bpp_div + y * img->sl_div] |= tmp[0][x + y * img->height] << 16;
		}
	}
	free(tmp[0]);
	free(tmp[1]);
	free(tmp[2]);

}


#include "img2.h"
#include "img2_load.h"
#include <stdio.h>

t_img2*		img2_load_raw(const char* src, int width, int height, int bpp)
{
	t_img2*			i;
	FILE*			file;
	int				fd;
	unsigned char	c;
	unsigned int	sum;

	fopen_s(&file, src, "rb");
	if (!file)
		return (0);
	i = img2_create(width, height);
	for (int y = 0; y < height; ++y)
		for (int x = 0; x < width; ++x)
		{
			int b;
			sum = 0;
			for (b = 0; b < bpp / 8; ++b)
			{
				fread_s(&c, 1, 1, 1, file);
				sum += c;
			}
			sum /= b;
			i->ddata[x + y * width] = (double)sum;
		}
	fclose(file);
	return (i);
}
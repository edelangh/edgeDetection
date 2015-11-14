#include "harris.h"
#include <iostream>
#include "main_draw.h"

#include "img2_load.h"
#include <string>

#include <windows.h>

void main_draw(unsigned __int8 (*a)[WIN_HEIGHT][WIN_WIDTH][3], unsigned int height, unsigned int width)
{
	t_img2* tmp;
	// tmp = img2_create(width, height);

	tmp = img2_load_raw("C:\\Users\\Eric\\Work\\edgeDetection\\Debug\\catle_800_531.raw", 800, 531, 24);
	/*
	for (int y = 0; y < height; ++y)
		for (int x = 0; x < width; ++x)
	{
		double c = (((*a)[y][x][0] << 16) | ((*a)[y][x][1] << 8) | (*a)[y][x][2]);
		tmp->ddata[x + y * width] = c;
	}
	*/
	static int ceuil = 0;
	ceuil += 20;
	harris(tmp, ceuil);
	Sleep(20);
	
	for (unsigned int y = 0; y < height; ++y)
		for (unsigned int x = 0; x < width; ++x)
		{
			unsigned int c = (unsigned int)tmp->ddata[x + y * width];
			unsigned _int8 d;

			d = (c & (unsigned int)0xFF);
			(*a)[y][x][0] = d;
			(*a)[y][x][1] = d;
			(*a)[y][x][2] = d;
		}
	img2_destroy(tmp);
}
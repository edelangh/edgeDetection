#include "img2.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **tmp_strsplit(char *s, char c)
{
	char **res;
	int	i;
	
	i = -1;
	if (!s || !strlen(s))
		return (0);

	res = malloc((strlen(s) / 2 + 1) * sizeof(char*));
	s = _strdup(s);
	while (*s)
	{
		while (*s == c)
		{
			*s = '\0';
			++s;
		}
		res[++i] = s;
		while (*s && *s != c)
			++s;
	}
	res[++i] = 0;
	return (res);
}

t_kernel*	load_kernel(char *src)
{
	FILE*		file;
	char*		line;
	char**		tab;
	int			width;
	int			height;
	t_kernel*	k;
	int			i;

	fopen_s(&file, src, "r");

	if (!file)
	{
		printf("can't open file\n");
		return (0);
	}
	height = 0;
	width = 0;
	k = malloc(sizeof(t_kernel));
	k->ddata = malloc(sizeof(double) * MAX_KERNEL_SIZE);

	while (!feof(file)) {
		i = -1;
		char c;
		line = malloc(255);
		while (fread_s(&c, 1, sizeof(char), 1, file) && c != '\n')
			if (c != '\r')
				line[++i] = c;
		line[++i] = '\0';
		if (!strlen(line))
			break;
		tab = tmp_strsplit(line, ' ');
		i = -1;
		while (tab[++i])
		{
			k->ddata[height * width + i] = atof(tab[i]);
		}
		if (tab[0])
		{
			free(tab[0]);
			tab[0] = 0;
		}
		if (tab)
		{
		//	free(tab); // TODO
			tab = 0;
		}
		free(line);
		if (i)
			++height;
		if (!width)
			width = i;
	}
	k->width = width;
	k->height = height;
	fclose(file);
	return (k);
}

void	kernel_destroy(t_kernel* k)
{
	free(k->ddata);
	free(k);
}
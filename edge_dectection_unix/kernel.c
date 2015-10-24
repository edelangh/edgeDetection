
#include "img2.h"
#include <fcntl.h>
#include <libft.h>

t_kernel*	load_kernel(char *src)
{
	int			fd;
	char*		line;
	char**		tab;
	int			width;
	int			height;
	t_kernel*	k;
	int			i;

	fd = open(src, O_RDONLY);
	if (fd < 0)
		return (NULL);
	height = 0;
	width = 0;
	k->ddata = malloc(sizeof(double) * MAX_KERNEL_SIZE);
	while (get_next_line(fd, &line) > 0)
	{
		tab = ft_strsplit(line, ' ');
		i = -1;
		while (tab[++i])
		{
			k->ddata[height * width + i] = ft_atof(tab[i]);
			free(tab[i]);
		}
		free(tab);
		free(line);
		if (width)
			++height;
		else
			width = i;
	}
	k->width = width;
	k->height = height;
	close(fd);
}

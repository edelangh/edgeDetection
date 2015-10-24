
#include "libft.h"
#include "ft_mlx.h"
#include "ft_printf.h"
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>

typedef struct	s_color_code
{
	int			color;
	char		code[3];
}			 	t_color_code;

int		make_color_list(t_img *i, t_list **lst)
{
	int				x;
	int				y;
	char			*tab;
	int				color;
	int				nb;
	t_color_code	code;

	tab = ft_memalloc(0xFFFFFF + 1);
	ft_bzero(tab, sizeof(tab));
	ft_bzero(&code, sizeof(code));
	code.code[0] = 'a';
	nb = 0;
	x = -1;
	while (y = -1, ++x < i->width)
	{
		while (++y < i->height)
		{
			color = i->udata[y * i->sl_div + x * i->bpp_div];
			if (!tab[color])
			{
				++nb;
				code.color = color;
				ft_lstadd(lst, ft_lstnew(&code, sizeof(code)));
				if (++code.code[0] > 'z')
				{
					code.code[0] = 'a';
					if (!code.code[1])
						code.code[1] = 'a' - 1;
					++code.code[1];
				}
			}
			tab[color] = 1;
		}
	}
	return (nb);
}

void	put_color(t_list *lst, int fd)
{
	t_color_code	*c;
	int				len;

	len = ft_strlen(((t_color_code*)lst->content)->code);
	if (len == 1)
		while (lst)
		{
			c = lst->content;
			dprintf(fd, "\"%s c #%x\",\n", c->code, c->color);
			lst = lst->next;
		}
	else
		while (lst)
		{
			c = lst->content;
			if (!c->code[1])
			{
				c->code[1] = c->code[0];
				c->code[0] = ' ';
			}
			dprintf(fd, "\"%s c #%.6X\",\n", c->code, c->color);
			lst = lst->next;
		}
}

void	put_each_pixel(t_img *i, t_list *lst, int fd)
{
	int		x;
	int		y;
	t_list	*tmp;
	int		color;

	y = -1;
	while (x = -1, ++y < i->height)
	{
		ft_putchar_fd('"', fd);
		while (++x < i->width)
		{
			tmp = lst;
			color = i->udata[y * i->sl_div + x * i->bpp_div];
			while (tmp)
			{
				if (((t_color_code*)tmp->content)->color == color)
					break ;
				tmp = tmp->next;
			}
			ft_putstr_fd(((t_color_code*)tmp->content)->code, fd);
		}
		if (y + 1 < i->height)
			ft_putstr_fd("\",\n", fd);
		else
			ft_putstr_fd("\"\n};\n", fd);
	}
}

int		ft_export_xpm(t_img *i, char *name)
{
	int		fd;
	t_list	*color;
	int		nb;

	color = NULL;
	fd = open(name, O_RDWR | O_TRUNC | O_CREAT, 0622);
	nb = make_color_list(i, &color);
	dprintf(fd, "/* XPM */\nstatic char *%s[] = {\n", name);
	dprintf(fd, "\"%d %d %d %d \",\n", i->width, i->height, nb,
			((int)ft_strlen(((t_color_code*)color->content)->code)));
	put_color(color, fd);
	put_each_pixel(i, color, fd);
	close(fd);
	return (fd != -1);
}

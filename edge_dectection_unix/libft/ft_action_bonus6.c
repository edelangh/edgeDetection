/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action_bonus6.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/06 15:40:23 by vincent          #+#    #+#             */
/*   Updated: 2015/01/23 11:53:55 by vincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <locale.h>

char	*ft_makecolor(char **str)
{
	*str = ft_strdup(*str);
	*str = ft_strreplace(*str, "{red}", "\033[22;31m");
	*str = ft_strreplace(*str, "{green}", "\033[22;32m");
	*str = ft_strreplace(*str, "{blue}", "\033[22;34m");
	*str = ft_strreplace(*str, "{yellow}", "\033[01;33m");
	*str = ft_strreplace(*str, "{magenta}", "\033[22;35m");
	*str = ft_strreplace(*str, "{white}", "\033[01;37m");
	*str = ft_strreplace(*str, "{pink}", "\033[01;35m");
	*str = ft_strreplace(*str, "{cyan}", "\033[01;36m");
	*str = ft_strreplace(*str, "{gray}", "\033[01;37m");
	*str = ft_strreplace(*str, "{blink}", "\033[5m");
	*str = ft_strreplace(*str, "{eoc}", "\033[22;37m");
	return (*str);
}

char	*ft_tild(t_printf *info, int *lenght)
{
	int		len;
	char	*space;

	space = localeconv()->decimal_point;
	len = ft_strlen(info->value) - ft_len_untill(info->value, '.');
	if (info->tild && ft_strchr("fF", info->type) && info->type)
		while (len > 3)
		{
			if (len + ft_len_untill(info->value, '.') != ft_strlen(info->value))
				info->value = ft_strinsert(info->value,
					space, len + ft_len_untill(info->value, '.'));
			len -= 3;
			(*lenght) += 1;
		}
	len = ft_len_untill(info->value, '.');
	if (info->tild && ft_strchr("duifF", info->type) && info->type)
		while (len > 3)
		{
			info->value = ft_strinsert(info->value, space, len - 3);
			len -= 3;
			(*lenght) += 1;
		}
	if (info->intero && ++(*lenght))
		info->value = ft_strjoinnchar(info->value, -1, info->type);
	return (info->value);
}

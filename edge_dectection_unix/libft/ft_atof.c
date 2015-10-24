/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/07/15 17:47:29 by vincent          #+#    #+#             */
/*   Updated: 2015/10/24 17:48:13 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int			ft_pow(int a, int b)
{
	int	c;

	c = 1;
	while (b--)
	{
		c *= a;
	}
	return (c);
}

double		ft_atof(const char *str)
{
	double	result;
	int		i;

	result = (double)ft_atoi(str);
	i = ft_len_untill(str, '.');
	if (i)
	{
		if (result >= 0 && str[0] != '-')
		{
			result += ((double)ft_atoi(str + i + 1))
				/ (ft_pow(10, ft_strlen(str + i + 1)));
		}
		else
		{
			result -= ((double)ft_atoi(str + i + 1))
				/ (ft_pow(10, ft_strlen(str + i + 1)));
		}
	}
	return (result);
}

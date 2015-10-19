/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/17 11:46:53 by vincent          #+#    #+#             */
/*   Updated: 2014/11/25 14:48:43 by vincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lsort(char **tab, int len)
{
	int		k;
	int		flag;

	flag = 1;
	--len;
	while (flag)
	{
		k = 0;
		flag = 0;
		while (k < len)
		{
			if (ft_strcmp(tab[k], tab[k + 1]) > 0)
			{
				ft_swap((void**)&tab[k], (void**)&tab[k + 1]);
				flag = 1;
			}
			++k;
		}
		++k;
	}
}

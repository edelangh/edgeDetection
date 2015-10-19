/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 12:03:58 by vincent          #+#    #+#             */
/*   Updated: 2014/11/04 17:40:07 by vincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	int				a;
	unsigned char	*str;

	str = (unsigned char*)b;
	a = 0;
	while (len--)
		str[a++] = (unsigned char)c;
	return (b);
}

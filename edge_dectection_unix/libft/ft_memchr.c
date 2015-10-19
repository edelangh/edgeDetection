/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 17:10:42 by vincent          #+#    #+#             */
/*   Updated: 2014/11/04 11:56:18 by vincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	int				a;
	unsigned char	*b;

	a = 0;
	b = (unsigned char*)s;
	while (n--)
		if (b[a++] == (unsigned char)c)
			return ((void*)b + --a);
	return (NULL);
}

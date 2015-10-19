/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 18:04:47 by vincent          #+#    #+#             */
/*   Updated: 2014/11/12 12:02:28 by vincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	int	i;

	i = 0;
	if (!dst || !src)
		return (NULL);
	while (n > 0 && src[i])
	{
		--n;
		dst[i] = src[i];
		++i;
	}
	while (n > 0)
	{
		dst[i] = '\0';
		++i;
		--n;
	}
	return (dst);
}

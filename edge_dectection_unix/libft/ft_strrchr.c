/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 15:30:49 by vincent          #+#    #+#             */
/*   Updated: 2014/11/10 16:51:24 by vincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*s1;
	char	*o;

	if (!s)
		return (NULL);
	s1 = (char*)s;
	o = NULL;
	while (*s1)
	{
		if (*s1 == (char)c)
			o = s1;
		++s1;
	}
	if (*s1 == (char)c)
		o = s1;
	return (o);
}

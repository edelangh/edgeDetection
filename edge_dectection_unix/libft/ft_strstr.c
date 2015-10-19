/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 15:49:35 by vincent          #+#    #+#             */
/*   Updated: 2014/11/12 10:23:37 by vincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	char	*t1;
	char	*t2;
	char	*t3;

	t1 = (char*)s1;
	while (*t1)
	{
		t3 = t1;
		t2 = (char*)s2;
		while (*t2 && *t2 == *t3)
		{
			++t2;
			++t3;
		}
		++t1;
		if (*t2 == '\0')
			return (t1 - 1);
	}
	if (!*s1 && !*s2)
		return (t1);
	return (NULL);
}

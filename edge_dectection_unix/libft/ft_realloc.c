/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/27 11:29:17 by vincent          #+#    #+#             */
/*   Updated: 2014/12/02 20:15:15 by vincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

void	ft_realloc(void **ptr, size_t slen, size_t nlen)
{
	void	*new;

	if (!ptr)
		return ;
	new = ft_malloc(nlen);
	ft_memcpy(new, *ptr, slen);
	if (*ptr)
		free(*ptr);
	*ptr = new;
}

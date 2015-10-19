/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 10:40:11 by vincent          #+#    #+#             */
/*   Updated: 2014/11/12 11:32:37 by vincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	**lst;

	if (!alst || !del)
		return ;
	lst = alst;
	while (*lst)
	{
		alst = &((*lst)->next);
		ft_lstdelone(lst, del);
		lst = alst;
	}
}

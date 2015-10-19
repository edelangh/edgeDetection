/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/22 16:44:24 by vincent          #+#    #+#             */
/*   Updated: 2014/11/25 14:49:05 by vincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstcat(t_list *lst1, t_list *lst2)
{
	t_list	*lst3;

	lst3 = ft_lstend(lst1);
	if (lst3)
		lst3->next = lst2;
	return ((lst3 ? lst1 : lst2));
}

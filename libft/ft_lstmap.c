/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:50:44 by nmikuka           #+#    #+#             */
/*   Updated: 2025/03/09 22:56:46 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *),	void (*del)(void *))
{
	t_list	*res;
	t_list	*new_node;

	if (!lst || !f || !del)
		return (NULL);
	res = ft_lstnew((*f)(lst->content));
	new_node = res;
	lst = lst->next;
	while (lst)
	{
		new_node->next = ft_lstnew((*f)(lst->content));
		if (!new_node->next)
		{
			ft_lstclear(&res, (*del));
			return (NULL);
		}
		new_node = new_node->next;
		lst = lst->next;
	}
	return (res);
}

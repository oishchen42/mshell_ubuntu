/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmikuka <nmikuka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:40:45 by nmikuka           #+#    #+#             */
/*   Updated: 2025/03/09 23:05:12 by nmikuka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void	*))
{
	t_list	*tmp;
	t_list	*node_to_del;

	if (!lst || !del)
		return ;
	tmp = *lst;
	while (tmp)
	{
		node_to_del = tmp;
		tmp = tmp->next;
		ft_lstdelone(node_to_del, (*del));
	}
	*lst = NULL;
}

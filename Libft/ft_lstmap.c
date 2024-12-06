/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzarhoun <rzarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:31:59 by rzarhoun          #+#    #+#             */
/*   Updated: 2023/11/18 21:45:33 by rzarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*current;
	t_list	*lst_new;
	t_list	*new_node;

	current = lst;
	lst_new = NULL;
	while (current && f)
	{
		new_node = ft_lstnew(f(current->content));
		if (!new_node)
		{
			ft_lstclear(&lst_new, del);
			return (NULL);
		}
		ft_lstadd_back(&lst_new, new_node);
		current = current->next;
	}
	return (lst_new);
}

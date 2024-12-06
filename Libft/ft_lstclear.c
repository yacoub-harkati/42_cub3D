/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzarhoun <rzarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 09:45:11 by rzarhoun          #+#    #+#             */
/*   Updated: 2023/11/20 22:37:29 by rzarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*next;

	current = *lst;
	next = NULL;
	if (lst == NULL)
		return ;
	while (current)
	{
		if (del)
			del(current->content);
		next = current->next;
		free(current);
		current = next;
	}
	*lst = NULL;
}

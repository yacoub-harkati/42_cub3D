/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzarhoun <rzarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:45:51 by rzarhoun          #+#    #+#             */
/*   Updated: 2023/11/18 21:16:04 by rzarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	s;
	void	*p;

	if (!nmemb || !size)
	{
		nmemb = 1;
		size = 1;
	}
	if (SIZE_MAX / nmemb < size && nmemb != 0)
		return (NULL);
	s = nmemb * size;
	p = malloc(s);
	if (p == NULL)
		return (NULL);
	else
		ft_bzero(p, s);
	return (p);
}

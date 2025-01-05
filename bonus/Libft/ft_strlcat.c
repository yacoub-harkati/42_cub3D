/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzarhoun <rzarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 20:28:34 by rzarhoun          #+#    #+#             */
/*   Updated: 2023/11/18 22:31:06 by rzarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	d_len;
	size_t	s_len;

	i = 0;
	s_len = ft_strlen((char *)src);
	if (n == 0 && !dest)
		return (s_len + n);
	d_len = ft_strlen((char *)dest);
	j = d_len;
	if (n == 0 || n <= d_len)
		return (s_len + n);
	while (src[i] && i < n - d_len - 1)
	{
		dest[j] = src[i];
		j++;
		i++;
	}
	dest[j] = '\0';
	return (d_len + s_len);
}

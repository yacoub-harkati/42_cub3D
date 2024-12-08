/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 22:49:08 by root              #+#    #+#             */
/*   Updated: 2024/12/08 21:05:49 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**parse_map(char **file)
{
	int		i;
	int		len;
	char	**map;

	i = 0;
	len = 0;
	while (file[i])
	{
		if (is_map_line(file[i]))
			len++;
		i++;
	}
	map = malloc(sizeof(char *) * (len + 1));
	if (!map)
		return (err("Error\n"), NULL);
	get_map(file, map, (i - len));
	return (map);
}

char	**parse_file(char **av)
{
	int		count;
	char	**file;

	count = count_lines(av[1]);
	file = malloc(sizeof(char *) * (count + 1));
	if (!file)
		return (NULL);
	get_file(av[1], file);
	return (file);
}

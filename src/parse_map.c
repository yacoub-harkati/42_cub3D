/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 22:49:08 by root              #+#    #+#             */
/*   Updated: 2024/12/07 01:21:19 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_lines(char *av)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(av, O_RDONLY);
	if (fd < 0)
		return (err("Error\n"), -1);
	count = 0;
	while ((line = get_next_line(fd)))
	{
		count++;
		free(line);
	}
	close (fd);
	return (count);
}

void	get_map(char *file, char **map)
{
	int		i;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (err("Error\n"));
	i = 0;
	map[i] = get_next_line(fd);
	while (map[i])
	{
		i++;
		map[i] = get_next_line(fd);
	}
}

char	**parse_map(char **av)
{
	int		count;
	char	**map;

	count = count_lines(av[1]);
	map = malloc(sizeof(char *) * (count + 1));
	if (!map)
		return (NULL);
	get_map(av[1], map);
	return (map);
}

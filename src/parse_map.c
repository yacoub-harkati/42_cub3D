/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 22:49:08 by root              #+#    #+#             */
/*   Updated: 2024/12/07 00:51:59 by root             ###   ########.fr       */
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

char	**parse_map(char **av)
{
	int	count;

	count = count_lines(av[1]);
	printf("%d\n", count);
	return (NULL);
}

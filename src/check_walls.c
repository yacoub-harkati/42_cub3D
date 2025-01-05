/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzarhoun <rzarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:00:24 by rzarhoun          #+#    #+#             */
/*   Updated: 2025/01/05 21:52:27 by rzarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_walls1(t_map *map)
{
	int	i;

	i = 0;
	while (map->map[0][i])
	{
		while (map->map[0][i] == ' ' || map->map[0][i] == '\t')
			i++;
		if (map->map[0][i] != '1')
			return (err("Error\nMap should be surrounded by walls\n"), 1);
		i++;
	}
	i = 0;
	while (map->map[map->height - 1][i])
	{
		while (map->map[map->height - 1][i] == ' ' || map->map[map->height
			- 1][i] == '\t')
			i++;
		if (map->map[map->height - 1][i] != '1')
			return (err("Error\nMap should be surrounded by walls\n"), 1);
		i++;
	}
	return (0);
}

int	wall_check(t_map *map, int i, int j)
{
	if (i > 0 && map->map[i - 1][j] != '1' && map->map[i
		- 1][j] != ' ' && ft_isalnum(map->map[i - 1][j]))
		return (err("Error\nMap should be surrounded by walls\n"),
			1);
	if (i < map->height - 1 && map->map[i + 1][j] != '1'
		&& map->map[i + 1][j] != ' ' && ft_isalnum(map->map[i
			+ 1][j]))
		return (err("Error\nMap should be surrounded by walls\n"),
			1);
	if (j > 0 && map->map[i][j - 1] != '1' && map->map[i][j
		- 1] != ' ' && ft_isalnum(map->map[i][j - 1]))
		return (err("Error\nMap should be surrounded by walls\n"),
			1);
	if (map->map[i][j + 1] && map->map[i][j + 1] != '1'
		&& map->map[i][j + 1] != ' ' && ft_isalnum(map->map[i][j
			+ 1]))
		return (err("Error\nMap should be surrounded by walls\n"),
			1);
	return (0);
}

int	check_map_walls2(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == ' ')
			{
				if (wall_check(map, i, j))
					return (1);
			}
			if (map->map[i][j + 1] == '\0' &&
				((i > 0 && map->map[i - 1][j + 1] == '0') ||
				(i < map->height - 1 && map->map[i + 1][j + 1] == '0')))
				return (err("Error\nMap should be surrounded by walls\n"),
					1);
			j++;
		}
		i++;
	}
	return (0);
}

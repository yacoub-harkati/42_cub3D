/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzarhoun <rzarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:46:18 by rzarhoun          #+#    #+#             */
/*   Updated: 2025/01/04 22:01:01 by rzarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_borders(char **map)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = 0;
	while (map[i])
	{
		j = 0;
		len = ft_strlen(map[i]);
		while (map[i][len - 1] == ' ')
			len--;
		while (map[i][j] == ' ' || map[i][j] == '\t')
			j++;
		if (map[i][j] != '1' || map[i][len - 1] != '1')
			return (err("Error\nMap should be surrounded by walls\n"), 1);
		i++;
	}
	return (0);
}

int	check_map_elements(t_map *map)
{
	int	count;

	count = get_count(map);
	if (count < 0)
		return (err("Error\nMap contains invalid elements\n"), 1);
	else if (count == 0)
		return (err("Error\nMap doesnt contain a starting position\n"), 1);
	else if (count > 1)
		return (err("Error\nMap contains more than one starting position\n"),
			1);
	return (0);
}

int	check_map_path(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S'
				|| map->map[i][j] == 'W' || map->map[i][j] == 'E')
			{
				if (map->map[i][j + 1] == '1' && map->map[i][j - 1] == '1'
					&& map->map[i + 1][j] == '1' && map->map[i - 1][j] == '1')
					return (err("Error\nPlayer cannot move\n"), 1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_map(t_map *map)
{
	if (check_map_borders(map->map))
		return (1);
	if (check_map_walls1(map) || check_map_walls2(map))
		return (1);
	if (check_map_elements(map))
		return (1);
	if (check_map_path(map))
		return (1);
	return (0);
}

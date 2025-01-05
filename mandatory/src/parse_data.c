/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 22:49:08 by root              #+#    #+#             */
/*   Updated: 2025/01/05 22:30:49 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_count(t_map *map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] != '1' && map->map[i][j] != '0'
				&& map->map[i][j] != 'N' && map->map[i][j] != 'S'
				&& map->map[i][j] != 'W' && map->map[i][j] != 'E'
				&& map->map[i][j] != ' ' && map->map[i][j] != '\t')
				return (-1);
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S'
			|| map->map[i][j] == 'W' || map->map[i][j] == 'E')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

t_player	*get_player_info(char **map)
{
	int			i;
	int			j;
	char		*c;
	t_player	*player;

	i = 0;
	player = malloc(sizeof(t_player));
	if (!player)
		return (err("Error\n"), NULL);
	init_player(player);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			c = ft_strchr("NSWE", map[i][j]);
			if (c)
				return (get_position(player, c, i, j), player);
			j++;
		}
		i++;
	}
	return (player);
}

t_map	*parse_map(char **file)
{
	int		map_start;
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (err("Error\n"), NULL);
	map->height = 0;
	map->width = 0;
	map_start = get_map_start(file, map);
	map->map = malloc(sizeof(char *) * (map->height + 1));
	if (!map->map)
		return (err("Error\n"), NULL);
	get_map(file, map, map_start);
	map->width = get_width(map->map);
	return (map);
}

char	**parse_file(char **av)
{
	int		count;
	char	**file;

	count = count_lines(av[1]);
	file = malloc(sizeof(char *) * (count + 2));
	if (!file)
		return (NULL);
	get_file(av[1], file);
	return (file);
}

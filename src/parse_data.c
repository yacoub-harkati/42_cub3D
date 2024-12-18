/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzarhoun <rzarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 22:49:08 by root              #+#    #+#             */
/*   Updated: 2024/12/18 18:34:56 by rzarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((c = ft_strchr("NSWE", map[i][j])))
			{
				player->x = i;
				player->y = j;
				player->position = c[0];
				break ;
			}
			j++;
		}
		i++;
	}
	return (player);
}

t_map	*parse_map(char **file)
{
	int		i;
	int		map_start;
	t_map	*map;

	i = 0;
	map = malloc(sizeof(t_map));
	map->height = 0;
	map->width = 0;
	map_start = -1;
	if (!map)
		return (err("Error\n"), NULL);
	while (file[i])
	{
		if (is_map_line(file[i]))
		{
			if (map_start == -1)
				map_start = i;
			map->height++;
		}
		i++;
	}
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
	file = malloc(sizeof(char *) * (count + 1));
	if (!file)
		return (NULL);
	get_file(av[1], file);
	return (file);
}

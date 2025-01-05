/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzarhoun <rzarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:41:41 by rzarhoun          #+#    #+#             */
/*   Updated: 2025/01/05 20:51:15 by rzarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_player *player)
{
	player->x = 0;
	player->y = 0;
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
	player->position = '\0';
}

void	get_position(t_player *player, char *c, int i, int j)
{
	player->x = (double)j + 0.5;
	player->y = (double)i + 0.5;
	player->position = c[0];
}

int	get_map_start(char **file, t_map *map)
{
	int	i;
	int	map_start;

	i = 0;
	map_start = -1;
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
	return (map_start);
}

int	*convert_char_int(char **str)
{
	int	i;
	int	*res;

	i = 0;
	res = malloc(sizeof(int) * 4);
	while (i < 3)
	{
		res[i] = ft_atoi(str[i]);
		free(str[i]);
		i++;
	}
	free(str);
	return (res);
}

int	check_fc(t_mlx *mlx)
{
	char	**floor;
	char	**ceiling;
	char	*path;

	path = get_path(mlx->file, "F");
	floor = ft_split(path, ',');
	free(path);
	path = get_path(mlx->file, "C");
	ceiling = ft_split(path, ',');
	free(path);
	if (!floor)
		return (err("Error\nFloor color is missing\n"), 1);
	if (!ceiling)
		return (err("Error\nCeiling color is missing\n"), 1);
	mlx->floor = convert_char_int(floor);
	mlx->ceiling = convert_char_int(ceiling);
	if (check_rgb(mlx))
		return (1);
	return (0);
}

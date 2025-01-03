/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 22:45:13 by root              #+#    #+#             */
/*   Updated: 2024/12/29 23:29:02 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_mlx	*init_struct(int ac, char **av)
{
	t_mlx	*mlx;
	t_map	*map;

	(void)ac;
	mlx = malloc(sizeof(t_mlx));
	if (!mlx)
		return (err("Error\n"), NULL);
	mlx->file = parse_file(av);
	if (check_file(mlx))
		exit(1);
	mlx->map = parse_map(mlx->file);
	map = mlx->map;
	if (check_map(map))
		exit(1);
	mlx->player = get_player_info(mlx->map->map);
	if (!mlx->player)
		return (NULL);
	mlx->game = malloc(sizeof(t_game));
	if (!mlx->game)
		return (err("Error\n"), NULL);
	return (mlx);
}

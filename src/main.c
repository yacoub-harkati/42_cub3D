/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzarhoun <rzarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:39:14 by root              #+#    #+#             */
/*   Updated: 2025/01/05 21:04:59 by rzarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cleanup_mlx(t_mlx *mlx)
{
	if (!mlx)
		return ;
	if (mlx->game)
		close_window(mlx);
	if (mlx->game->ptr)
	{
		mlx_destroy_display(mlx->game->ptr);
		free(mlx->game->ptr);
		mlx->game->ptr = NULL;
	}
	free(mlx->game);
	mlx->game = NULL;
	if (mlx->file)
	{
		int i = 0;
		while (mlx->file[i])
			free(mlx->file[i++]);
		free(mlx->file);
	}
	if (mlx->map)
	{
		int i = 0;
		while (mlx->map->map[i])
			free(mlx->map->map[i++]);
		free(mlx->map->map);
		free(mlx->map);
	}
	if (mlx->player)
		free(mlx->player);
	if (mlx->path)
	{
		free(mlx->path->so);
		free(mlx->path->we);
		free(mlx->path->ea);
		free(mlx->path->no);
		free(mlx->path);
	}
	if (mlx->floor)
		free(mlx->floor);
	if (mlx->ceiling)
		free(mlx->ceiling);
	free(mlx);
}

int	main(int ac, char **av)
{
	t_mlx	*mlx;
	int		status;

	if (check_args(ac, av))
		return (1);
	mlx = init_struct(ac, av);
	if (!mlx)
		return (err("Error\n"), 1);
	status = init_game(mlx);
	cleanup_mlx(mlx);
	return (status);
}

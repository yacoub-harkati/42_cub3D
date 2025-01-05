/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:39:14 by root              #+#    #+#             */
/*   Updated: 2025/01/05 21:44:55 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_path(t_path *path)
{
	free(path->so);
	free(path->we);
	free(path->ea);
	free(path->no);
	free(path);
}

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
		free_matrix(mlx->file);
	if (mlx->map)
		(free_matrix(mlx->map->map), free(mlx->map));
	if (mlx->player)
		free(mlx->player);
	if (mlx->path)
		free_path(mlx->path);
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

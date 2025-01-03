/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:39:14 by root              #+#    #+#             */
/*   Updated: 2025/01/03 02:21:45 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cleanup_mlx(t_mlx *mlx)
{
	if (!mlx)
		return ;
	if (mlx->game)
		close_window(mlx);
	if (mlx->map)
		free(mlx->map);
	if (mlx->player)
		free(mlx->player);
	if (mlx->path)
		free(mlx->path);
	free(mlx);
}

int	main(int ac, char **av)
{
	t_mlx *mlx;
	int status;

	if (check_args(ac, av))
		return (1);
	mlx = init_struct(ac, av);
	if (!mlx)
		return (err("Error\n"), 1);
	status = init_game(mlx);
	cleanup_mlx(mlx);
	return (status);
}
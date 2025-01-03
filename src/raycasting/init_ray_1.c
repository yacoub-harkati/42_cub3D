/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 01:57:31 by yaharkat          #+#    #+#             */
/*   Updated: 2025/01/03 01:58:25 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_north_south(t_mlx *mlx)
{
	if (mlx->player->position == 'N')
	{
		mlx->player->dir_x = 0;
		mlx->player->dir_y = -1;
		mlx->player->plane_x = 0.66;
		mlx->player->plane_y = 0;
	}
	else if (mlx->player->position == 'S')
	{
		mlx->player->dir_x = 0;
		mlx->player->dir_y = 1;
		mlx->player->plane_x = -0.66;
		mlx->player->plane_y = 0;
	}
}

static void	init_east_west(t_mlx *mlx)
{
	if (mlx->player->position == 'E')
	{
		mlx->player->dir_x = 1;
		mlx->player->dir_y = 0;
		mlx->player->plane_x = 0;
		mlx->player->plane_y = 0.66;
	}
	else if (mlx->player->position == 'W')
	{
		mlx->player->dir_x = -1;
		mlx->player->dir_y = 0;
		mlx->player->plane_x = 0;
		mlx->player->plane_y = -0.66;
	}
}

void	init_raycast(t_mlx *mlx)
{
	init_north_south(mlx);
	init_east_west(mlx);
}
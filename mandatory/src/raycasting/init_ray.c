/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 01:57:31 by yaharkat          #+#    #+#             */
/*   Updated: 2025/01/04 02:24:03 by yaharkat         ###   ########.fr       */
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

void	init_ray(t_ray *ray, t_mlx *mlx, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->ray_dir_x = mlx->player->dir_x + mlx->player->plane_x * camera_x;
	ray->ray_dir_y = mlx->player->dir_y + mlx->player->plane_y * camera_x;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / ray->ray_dir_y);
	ray->hit = 0;
	ray->hit_type = '0';
}

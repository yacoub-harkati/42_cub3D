/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_dda.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 00:18:39 by yaharkat          #+#    #+#             */
/*   Updated: 2025/01/04 00:18:45 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_ray_position_walls(t_ray *ray, int *map_x, int *map_y)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		*map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		*map_y += ray->step_y;
		ray->side = 1;
	}
}

static void	handle_wall_hit(t_ray *ray, t_mlx *mlx, int *map_x, int *map_y)
{
	ray->hit = 1;
	ray->hit_type = '1';
	if (ray->side == 0)
		ray->perp_wall_dist = ((*map_x - mlx->player->x + (1 - ray->step_x) / 2)
				/ ray->ray_dir_x);
	else
		ray->perp_wall_dist = ((*map_y - mlx->player->y + (1 - ray->step_y) / 2)
				/ ray->ray_dir_y);
}

void	perform_dda_walls(t_ray *ray, t_mlx *mlx, int *map_x, int *map_y)
{
	while (ray->hit == 0)
	{
		update_ray_position_walls(ray, map_x, map_y);
		if (*map_x < 0 || *map_x >= mlx->map->width || *map_y < 0
			|| *map_y >= mlx->map->height)
		{
			ray->hit = 1;
			ray->side = 2;
			ray->hit_type = '0';
			break ;
		}
		if (mlx->map->map[*map_y][*map_x] == '1')
			handle_wall_hit(ray, mlx, map_x, map_y);
	}
}

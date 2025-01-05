/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 23:07:55 by yaharkat          #+#    #+#             */
/*   Updated: 2025/01/04 00:18:02 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_step_dist(t_ray *ray, t_mlx *mlx, int map_x, int map_y)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (mlx->player->x - map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (map_x + 1.0 - mlx->player->x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (mlx->player->y - map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (map_y + 1.0 - mlx->player->y) * ray->delta_dist_y;
	}
}

void	calc_wall_height(t_ray *ray, t_mlx *mlx, int map_x, int map_y)
{
	if (ray->side == 0 && ray->ray_dir_x != 0)
		ray->perp_wall_dist = (map_x - mlx->player->x + (1 - ray->step_x) / 2)
			/ ray->ray_dir_x;
	else if (ray->side == 1 && ray->ray_dir_y != 0)
		ray->perp_wall_dist = (map_y - mlx->player->y + (1 - ray->step_y) / 2)
			/ ray->ray_dir_y;
	else
		ray->perp_wall_dist = 1e30;
	ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	if (ray->line_height > WIN_HEIGHT * 10)
		ray->line_height = WIN_HEIGHT * 10;
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}

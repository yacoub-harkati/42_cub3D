/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 23:07:55 by yaharkat          #+#    #+#             */
/*   Updated: 2025/01/03 23:15:40 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	perform_dda_doors(t_ray *ray, t_mlx *mlx, int *map_x, int *map_y)
{
	ray->has_door = 0;
	while (ray->hit == 0)
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
		if (*map_x < 0 || *map_x >= mlx->map->width || *map_y < 0
			|| *map_y >= mlx->map->height)
		{
			ray->hit = 1;
			ray->side = 2;
			ray->hit_type = '0';
			break ;
		}
		if (mlx->map->map[*map_y][*map_x] == 'D')
		{
			ray->has_door = 1;
			ray->hit = 1;
			ray->hit_type = 'D';
			if (ray->side == 0)
				ray->perp_wall_dist = ((*map_x - mlx->player->x + (1
								- ray->step_x) / 2) / ray->ray_dir_x);
			else
				ray->perp_wall_dist = ((*map_y - mlx->player->y + (1
								- ray->step_y) / 2) / ray->ray_dir_y);
			break ;
		}
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 01:57:31 by yaharkat          #+#    #+#             */
/*   Updated: 2025/01/03 04:58:01 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray(t_ray *ray, t_mlx *mlx, int x)
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
}

static void	calc_step_dist(t_ray *ray, t_mlx *mlx, int map_x, int map_y)
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

static void	perform_dda(t_ray *ray, t_mlx *mlx, int *map_x, int *map_y)
{
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
			break ;
		}
		if (mlx->map->map[*map_y] && mlx->map->map[*map_y][*map_x] == '1')
			ray->hit = 1;
	}
}

static void	calc_wall_height(t_ray *ray, t_mlx *mlx, int map_x, int map_y)
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

void	cast_rays(t_mlx *mlx)
{
	t_ray	ray;
	int		x;
	int		map_x;
	int		map_y;

	if (!mlx || !mlx->player || !mlx->map || !mlx->game || !mlx->game->screen
		|| !mlx->game->screen->addr)
		return ;
	x = 0;
	while (x < WIN_WIDTH)
	{
		map_x = (int)floor(mlx->player->x);
		map_y = (int)floor(mlx->player->y);
		init_ray(&ray, mlx, x);
		calc_step_dist(&ray, mlx, map_x, map_y);
		perform_dda(&ray, mlx, &map_x, &map_y);
		calc_wall_height(&ray, mlx, map_x, map_y);
		if (ray.side != 2)
			draw_walls(mlx, &ray, x);
		x++;
	}
}

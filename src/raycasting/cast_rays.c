/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 00:15:02 by yaharkat          #+#    #+#             */
/*   Updated: 2025/01/04 00:21:07 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray_vars(t_ray *ray, t_mlx *mlx, int x, int *coords)
{
	coords[0] = (int)floor(mlx->player->x);
	coords[1] = (int)floor(mlx->player->y);
	init_ray(ray, mlx, x);
	calc_step_dist(ray, mlx, coords[0], coords[1]);
}

static void	render_walls(t_mlx *mlx)
{
	t_ray	ray;
	int		x;
	int		coords[2];

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray_vars(&ray, mlx, x, coords);
		perform_dda_walls(&ray, mlx, &coords[0], &coords[1]);
		calc_wall_height(&ray, mlx, coords[0], coords[1]);
		draw_walls(mlx, &ray, x);
		x++;
	}
}

static void	render_doors(t_mlx *mlx)
{
	t_ray	ray;
	int		x;
	int		coords[2];

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray_vars(&ray, mlx, x, coords);
		perform_dda_doors(&ray, mlx, &coords[0], &coords[1]);
		if (ray.hit && ray.hit_type == 'D')
		{
			calc_wall_height(&ray, mlx, coords[0], coords[1]);
			draw_doors(mlx, &ray, x);
		}
		x++;
	}
}

void	cast_rays(t_mlx *mlx)
{
	if (!mlx || !mlx->player || !mlx->map || !mlx->game || !mlx->game->screen
		|| !mlx->game->screen->addr)
		return ;
	render_walls(mlx);
	render_doors(mlx);
}

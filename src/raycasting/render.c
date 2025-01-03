/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 01:48:58 by yaharkat          #+#    #+#             */
/*   Updated: 2025/01/03 02:00:37 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_img	*select_texture(t_mlx *mlx, t_ray *ray)
{
	if (ray->side == 0)
		return ((ray->ray_dir_x > 0) ? mlx->game->textures->ea : mlx->game->textures->we);
	return ((ray->ray_dir_y > 0) ? mlx->game->textures->so : mlx->game->textures->no);
}

static void	calc_texture_coords(t_ray *ray, t_mlx *mlx, double *wall_x,
		int *tex_x)
{
	if (ray->side == 0)
		*wall_x = mlx->player->y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		*wall_x = mlx->player->x + ray->perp_wall_dist * ray->ray_dir_x;
	*wall_x -= floor(*wall_x);
	*tex_x = (int)(*wall_x * TEXTURE_SIZE);
	if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1
			&& ray->ray_dir_y < 0))
		*tex_x = TEXTURE_SIZE - *tex_x - 1;
}

static double	calc_shade(t_ray *ray)
{
	double	shade;

	shade = 1.0;
	if (ray->perp_wall_dist > 1.0)
		shade = 1.0 / (ray->perp_wall_dist * 0.95);
	if (shade > 1.0)
		shade = 1.0;
	if (ray->side == 0)
		shade *= 0.85;
	shade = 0.5 + (shade * 0.9);
	return (shade);
}

static void	draw_texture_line(t_mlx *mlx, t_ray *ray, t_draw_data *data)
{
	int	y;
	int	tex_y;
	int	color;

	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)data->tex_pos & (TEXTURE_SIZE - 1);
		data->tex_pos += data->step;
		color = data->texture->addr[TEXTURE_SIZE * tex_y + data->tex_x];
		data->r = ((color >> 16) & 0xFF) * data->shade;
		data->g = ((color >> 8) & 0xFF) * data->shade;
		data->b = (color & 0xFF) * data->shade;
		data->r = (data->r > 255) ? 255 : data->r;
		data->g = (data->g > 255) ? 255 : data->g;
		data->b = (data->b > 255) ? 255 : data->b;
		color = create_rgb(data->r, data->g, data->b);
		mlx->game->screen->addr[y * WIN_WIDTH - data->x + WIN_WIDTH] = color;
		y++;
	}
}

void	draw_walls(t_mlx *mlx, t_ray *ray, int x)
{
	t_draw_data	data;
	double		wall_x;

	data.texture = select_texture(mlx, ray);
	calc_texture_coords(ray, mlx, &wall_x, &data.tex_x);
	data.shade = calc_shade(ray);
	data.step = 1.0 * TEXTURE_SIZE / ray->line_height;
	data.tex_pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2)
		* data.step;
	data.x = x;
	draw_texture_line(mlx, ray, &data);
}

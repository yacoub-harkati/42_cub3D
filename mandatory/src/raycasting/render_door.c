/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 01:57:31 by yaharkat          #+#    #+#             */
/*   Updated: 2025/01/04 02:28:19 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_door_data(t_draw_data *data, t_mlx *mlx, t_ray *ray, int x)
{
	data->texture = select_texture(mlx, ray);
	calc_texture_coords(ray, mlx, &data->tex_x, ray->hit_type);
	data->shade = calc_shade(ray, ray->hit_type);
	data->step = 1.0 * TEXTURE_SIZE / ray->line_height;
	data->tex_pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2)
		* data->step;
	data->x = x;
}

static int	check_texture_bounds(int y, int tex_y, int tex_x)
{
	return (y < 0 || y >= WIN_HEIGHT || tex_y < 0 || tex_y >= TEXTURE_SIZE
		|| tex_x < 0 || tex_x >= TEXTURE_SIZE);
}

static void	draw_door_pixel(t_mlx *mlx, int buffer_index, int color)
{
	if (buffer_index >= 0 && buffer_index < (WIN_WIDTH * WIN_HEIGHT))
		mlx->game->screen->addr[buffer_index] = create_rgb(color, color, color);
}

static void	draw_door_line(t_mlx *mlx, t_ray *ray, t_draw_data *data)
{
	int	y;
	int	tex_y;
	int	color;
	int	buffer_index;

	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)data->tex_pos & (TEXTURE_SIZE - 1);
		data->tex_pos += data->step;
		if (check_texture_bounds(y, tex_y, data->tex_x))
		{
			y++;
			continue ;
		}
		color = data->texture->addr[TEXTURE_SIZE * tex_y + data->tex_x];
		if (color != TRANSPARENT_COLOR)
		{
			buffer_index = y * WIN_WIDTH - data->x;
			draw_door_pixel(mlx, buffer_index, color);
		}
		y++;
	}
}

void	draw_doors(t_mlx *mlx, t_ray *ray, int x)
{
	t_draw_data	data;

	if (x < 0 || x >= WIN_WIDTH)
		return ;
	if (mlx->game->textures->door->current_frame >= 0)
	{
		init_door_data(&data, mlx, ray, x);
		draw_door_line(mlx, ray, &data);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 01:48:58 by yaharkat          #+#    #+#             */
/*   Updated: 2025/01/03 22:31:51 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*select_texture(t_mlx *mlx, t_ray *ray)
{
	if (ray->hit_type == 'D')
		return (mlx->game->textures->door->frames[mlx->game->textures->door->current_frame]);
	if (ray->side == 0)
		return (ft_ternary(ray->ray_dir_x > 0, mlx->game->textures->ea,
				mlx->game->textures->we));
	return (ft_ternary(ray->ray_dir_y > 0, mlx->game->textures->so,
			mlx->game->textures->no));
}

void	calc_texture_coords(t_ray *ray, t_mlx *mlx, double *wall_x, int *tex_x,
		char wall_type)
{
	if (ray->side == 0)
		*wall_x = mlx->player->y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		*wall_x = mlx->player->x + ray->perp_wall_dist * ray->ray_dir_x;
	*wall_x -= floor(*wall_x);
	*tex_x = (int)(*wall_x * TEXTURE_SIZE);
	if (wall_type == 'D')
	{
		/* Make doors look consistent regardless of side hit */
		if ((ray->side == 0 && ray->ray_dir_x < 0) || (ray->side == 1
				&& ray->ray_dir_y < 0))
			*tex_x = TEXTURE_SIZE - *tex_x - 1;
	}
	else if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1
			&& ray->ray_dir_y < 0))
		*tex_x = TEXTURE_SIZE - *tex_x - 1;
}

double	calc_shade(t_ray *ray, char wall_type)
{
	double	shade;

	shade = 1.0;
	if (ray->perp_wall_dist > 1.0)
		shade = 1.0 / (ray->perp_wall_dist * 0.95);
	if (shade > 1.0)
		shade = 1.0;
	if (ray->side == 0)
		shade *= 0.85;
	if (wall_type == 'D')
		shade *= 1.2;
	shade = 0.5 + (shade * 0.9);
	return (shade);
}

static void	draw_texture_line(t_mlx *mlx, t_ray *ray, t_draw_data *data)
{
	int	y;
	int	tex_y;
	int	color;
	int	white;

	white = 255;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)data->tex_pos & (TEXTURE_SIZE - 1);
		data->tex_pos += data->step;
		color = data->texture->addr[TEXTURE_SIZE * tex_y + data->tex_x];
		if (color != TRANSPARENT_COLOR)
		{
			data->r = ((color >> 16) & 0xFF) * data->shade;
			data->g = ((color >> 8) & 0xFF) * data->shade;
			data->b = (color & 0xFF) * data->shade;
			data->r = *(int *)ft_ternary((data->r > 255), &white, &data->r);
			data->g = *(int *)ft_ternary((data->g > 255), &white, &data->g);
			data->b = *(int *)ft_ternary((data->b > 255), &white, &data->b);
			color = create_rgb(data->r, data->g, data->b);
			mlx->game->screen->addr[y * WIN_WIDTH - data->x
				+ WIN_WIDTH] = color;
		}
		y++;
	}
}

void	draw_walls(t_mlx *mlx, t_ray *ray, int x)
{
	t_draw_data	data;
	double		wall_x;

	// Only draw if we hit something
	if (ray->hit)
	{
		// For doors, only draw them if they're fully closed
		if (ray->hit_type == 'D'
			&& mlx->game->textures->door->current_frame > 0)
			return ;
		data.texture = select_texture(mlx, ray);
		calc_texture_coords(ray, mlx, &wall_x, &data.tex_x, ray->hit_type);
		data.shade = calc_shade(ray, ray->hit_type);
		data.step = 1.0 * TEXTURE_SIZE / ray->line_height;
		data.tex_pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2)
			* data.step;
		data.x = x;
		draw_texture_line(mlx, ray, &data);
	}
}

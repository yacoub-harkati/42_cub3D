/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 00:28:42 by yaharkat          #+#    #+#             */
/*   Updated: 2025/01/04 02:23:59 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_pixel(t_mlx *mlx, int x, int y, int color)
{
	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
		mlx->game->screen->addr[y * WIN_WIDTH + x] = color;
}

void	draw_map_border(t_mlx *mlx, t_minimap *mm)
{
	int	x;
	int	y;

	y = -mm->border;
	while (y < mm->map_height + mm->border)
	{
		x = -mm->border;
		while (x < mm->map_width + mm->border)
		{
			mm->pixel_x = mm->mini_x + x;
			mm->pixel_y = mm->mini_y + y;
			if (x < 0 || x >= mm->map_width || y < 0 || y >= mm->map_height)
				set_pixel(mlx, mm->pixel_x, mm->pixel_y, 0xFFFFFF);
			x++;
		}
		y++;
	}
}

int	get_tile_color(t_mlx *mlx, int x, int y)
{
	if (mlx->map->map[y][x] == '1')
		return (0x808080);
	if (mlx->map->map[y][x] == '0' || ft_strchr("NSWE", mlx->map->map[y][x]))
		return (0x202020);
	return (0x000000);
}

void	draw_map_tile(t_mlx *mlx, t_minimap *mm, int x, int y)
{
	int	i;
	int	j;
	int	color;

	color = get_tile_color(mlx, x, y);
	i = 1;
	while (i < mm->tile_size - 1)
	{
		j = 1;
		while (j < mm->tile_size - 1)
		{
			mm->pixel_x = mm->mini_x + (x * mm->tile_size) + i;
			mm->pixel_y = mm->mini_y + (y * mm->tile_size) + j;
			set_pixel(mlx, mm->pixel_x, mm->pixel_y, color);
			j++;
		}
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 00:26:56 by yaharkat          #+#    #+#             */
/*   Updated: 2025/01/04 02:23:54 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_map_tiles(t_mlx *mlx, t_minimap *mm)
{
	int	x;
	int	y;

	y = 0;
	while (y < mlx->map->height)
	{
		if (!mlx->map->map[y])
		{
			y++;
			continue ;
		}
		x = 0;
		while (x < mlx->map->width && x < (int)ft_strlen(mlx->map->map[y]))
		{
			draw_map_tile(mlx, mm, x, y);
			x++;
		}
		y++;
	}
}

static void	draw_player_dot(t_mlx *mlx, t_minimap *mm)
{
	int	i;
	int	j;

	i = -2;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			if (i * i + j * j <= 4)
				set_pixel(mlx, mm->player_x + i, mm->player_y + j, 0xFF0000);
			j++;
		}
		i++;
	}
}

static void	draw_direction_line(t_mlx *mlx, t_minimap *mm)
{
	int	i;
	int	line_x;
	int	line_y;

	i = 0;
	while (i < 8)
	{
		line_x = mm->player_x + (int)(mlx->player->dir_x * i);
		line_y = mm->player_y + (int)(mlx->player->dir_y * i);
		set_pixel(mlx, line_x, line_y, 0xFFFF00);
		i++;
	}
}

void	draw_minimap(t_mlx *mlx)
{
	t_minimap	mm;

	mm.tile_size = 8;
	mm.mini_x = 10;
	mm.mini_y = 10;
	mm.border = 2;
	mm.map_width = mlx->map->width * mm.tile_size;
	mm.map_height = mlx->map->height * mm.tile_size;
	mm.player_x = mm.mini_x + (int)(mlx->player->x * mm.tile_size);
	mm.player_y = mm.mini_y + (int)(mlx->player->y * mm.tile_size);
	draw_map_border(mlx, &mm);
	draw_map_tiles(mlx, &mm);
	draw_player_dot(mlx, &mm);
	draw_direction_line(mlx, &mm);
}

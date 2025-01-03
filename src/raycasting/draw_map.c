/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 02:00:23 by yaharkat          #+#    #+#             */
/*   Updated: 2025/01/03 02:00:45 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_map_border(t_mlx *mlx, t_minimap *mm)
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
			if (mm->pixel_x >= 0 && mm->pixel_x < WIN_WIDTH && mm->pixel_y >= 0
				&& mm->pixel_y < WIN_HEIGHT)
			{
				if (x < 0 || x >= mm->map_width || y < 0 || y >= mm->map_height)
					mlx->game->screen->addr[mm->pixel_y * WIN_WIDTH
						+ mm->pixel_x] = 0xFFFFFF;
			}
			x++;
		}
		y++;
	}
}

static void	draw_map_tile(t_mlx *mlx, t_minimap *mm, int x, int y)
{
	int	i;
	int	j;
	int	color;

	if (mlx->map->map[y][x] == '1')
		color = 0x808080;
	else if (mlx->map->map[y][x] == '0' || ft_strchr("NSWE",
			mlx->map->map[y][x]))
		color = 0x202020;
	else
		color = 0x000000;
	i = 1;
	while (i < mm->tile_size - 1)
	{
		j = 1;
		while (j < mm->tile_size - 1)
		{
			mm->pixel_x = mm->mini_x + (x * mm->tile_size) + i;
			mm->pixel_y = mm->mini_y + (y * mm->tile_size) + j;
			if (mm->pixel_x >= 0 && mm->pixel_x < WIN_WIDTH && mm->pixel_y >= 0
				&& mm->pixel_y < WIN_HEIGHT)
				mlx->game->screen->addr[mm->pixel_y * WIN_WIDTH
					+ mm->pixel_x] = color;
			j++;
		}
		i++;
	}
}

static void	draw_map_tiles(t_mlx *mlx, t_minimap *mm)
{
	int	x;
	int	y;

	y = 0;
	while (y < mlx->map->height)
	{
		if (!mlx->map->map[y])
			continue ;
		x = 0;
		while (x < mlx->map->width)
		{
			if (x >= (int)ft_strlen(mlx->map->map[y]))
				break ;
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
			{
				mm->pixel_x = mm->player_x + i;
				mm->pixel_y = mm->player_y + j;
				if (mm->pixel_x >= 0 && mm->pixel_x < WIN_WIDTH
					&& mm->pixel_y >= 0 && mm->pixel_y < WIN_HEIGHT)
					mlx->game->screen->addr[mm->pixel_y * WIN_WIDTH
						+ mm->pixel_x] = 0xFF0000;
			}
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
		if (line_x >= 0 && line_x < WIN_WIDTH && line_y >= 0
			&& line_y < WIN_HEIGHT)
			mlx->game->screen->addr[line_y * WIN_WIDTH + line_x] = 0xFFFF00;
		i++;
	}
}

void	draw_minimap(t_mlx *mlx)
{
	t_minimap mm;

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
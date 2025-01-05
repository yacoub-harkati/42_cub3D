/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 01:49:47 by yaharkat          #+#    #+#             */
/*   Updated: 2025/01/04 02:44:44 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_floor_ceiling(t_mlx *mlx)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (y < WIN_HEIGHT / 2)
				mlx->game->screen->addr[y * WIN_WIDTH
					+ x] = create_rgb(mlx->ceiling[0], mlx->ceiling[1],
						mlx->ceiling[2]);
			else
				mlx->game->screen->addr[y * WIN_WIDTH
					+ x] = create_rgb(mlx->floor[0], mlx->floor[1],
						mlx->floor[2]);
			x++;
		}
		y++;
	}
}

static int	validate_game_state(t_mlx *mlx)
{
	if (!mlx->game->running)
		return (1);
	if (!mlx || !mlx->game || !mlx->game->screen || !mlx->game->screen->addr)
		return (1);
	return (0);
}

int	game_loop(t_mlx *mlx)
{
	if (validate_game_state(mlx))
		return (1);
	if (mlx->game->screen->addr)
		ft_memset(mlx->game->screen->addr, 0, WIN_WIDTH * WIN_HEIGHT
			* sizeof(int));
	if (mlx->game->screen->addr)
		draw_floor_ceiling(mlx);
	if (mlx->map && mlx->player && mlx->game->running)
	{
		update_door_animation(mlx->game->textures->door);
		cast_rays(mlx);
		draw_minimap(mlx);
	}
	if (mlx->game->ptr && mlx->game->win && mlx->game->screen->img)
		mlx_put_image_to_window(mlx->game->ptr, mlx->game->win,
			mlx->game->screen->img, 0, 0);
	return (0);
}

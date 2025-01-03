/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 02:24:29 by yaharkat          #+#    #+#             */
/*   Updated: 2025/01/03 02:25:09 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_movement(t_mlx *mlx, double *new_x, double *new_y, int key)
{
	if (key == KEY_W)
	{
		*new_x += mlx->player->dir_x * MOVE_SPEED;
		*new_y += mlx->player->dir_y * MOVE_SPEED;
	}
	if (key == KEY_S)
	{
		*new_x -= mlx->player->dir_x * MOVE_SPEED;
		*new_y -= mlx->player->dir_y * MOVE_SPEED;
	}
	if (key == KEY_A)
	{
		*new_x -= mlx->player->dir_y * MOVE_SPEED;
		*new_y += mlx->player->dir_x * MOVE_SPEED;
	}
	if (key == KEY_D)
	{
		*new_x += mlx->player->dir_y * MOVE_SPEED;
		*new_y -= mlx->player->dir_x * MOVE_SPEED;
	}
}

void	move_player(t_mlx *mlx, int key)
{
	double	new_x;
	double	new_y;

	new_x = mlx->player->x;
	new_y = mlx->player->y;
	handle_movement(mlx, &new_x, &new_y, key);
	if (new_x >= 0 && new_x < mlx->map->width && new_y >= 0
		&& new_y < mlx->map->height
		&& mlx->map->map[(int)new_y][(int)new_x] != '1')
	{
		mlx->player->x = new_x;
		mlx->player->y = new_y;
	}
}

void	rotate_player(t_mlx *mlx, int direction)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rotation;

	old_dir_x = mlx->player->dir_x;
	old_plane_x = mlx->player->plane_x;
	rotation = ROT_SPEED * direction;
	mlx->player->dir_x = mlx->player->dir_x * cos(rotation) - mlx->player->dir_y
		* sin(rotation);
	mlx->player->dir_y = old_dir_x * sin(rotation) + mlx->player->dir_y
		* cos(rotation);
	mlx->player->plane_x = mlx->player->plane_x * cos(rotation)
		- mlx->player->plane_y * sin(rotation);
	mlx->player->plane_y = old_plane_x * sin(rotation) + mlx->player->plane_y
		* cos(rotation);
}

int	handle_keypress(int key, t_mlx *mlx)
{
	if (key == KEY_ESC)
		return (close_window(mlx));
	if (key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D)
		move_player(mlx, key);
	if (key == KEY_LEFT)
		rotate_player(mlx, 1);
	if (key == KEY_RIGHT)
		rotate_player(mlx, -1);
	return (0);
}
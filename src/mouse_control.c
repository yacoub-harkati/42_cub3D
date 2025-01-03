/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 02:49:46 by yaharkat          #+#    #+#             */
/*   Updated: 2025/01/03 03:27:21 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_mouse_move(int x, int y, t_mlx *mlx)
{
	static int	last_x = -1;
	double		rotation;
	int			dx;

	(void)y;
	if (!mlx->game->running)
		return (0);
	if (last_x == -1)
	{
		last_x = x;
		return (0);
	}
	dx = x - last_x;
	if (dx != 0)
	{
		rotation = -(double)dx * MOUSE_SENSITIVITY;
		rotate_camera(mlx, rotation);
	}
	last_x = x;
	if (x <= 1 || x >= WIN_WIDTH - 2)
	{
		mlx_mouse_move(mlx->game->ptr, mlx->game->win, WIN_WIDTH / 2, WIN_HEIGHT
			/ 2);
		last_x = WIN_WIDTH / 2;
	}
	return (0);
}

/* Update rotate_camera for smoother rotation */
void	rotate_camera(t_mlx *mlx, double rotation)
{
	double old_dir_x;
	double old_plane_x;
	double cos_rot;
	double sin_rot;

	cos_rot = cos(rotation);
	sin_rot = sin(rotation);
	old_dir_x = mlx->player->dir_x;
	old_plane_x = mlx->player->plane_x;
	mlx->player->dir_x = mlx->player->dir_x * cos_rot - mlx->player->dir_y
		* sin_rot;
	mlx->player->dir_y = old_dir_x * sin_rot + mlx->player->dir_y * cos_rot;
	mlx->player->plane_x = mlx->player->plane_x * cos_rot - mlx->player->plane_y
		* sin_rot;
	mlx->player->plane_y = old_plane_x * sin_rot + mlx->player->plane_y
		* cos_rot;
}
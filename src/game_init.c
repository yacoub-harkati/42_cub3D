/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 01:34:47 by yaharkat          #+#    #+#             */
/*   Updated: 2025/01/03 19:46:59 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*init_texture(void *mlx_ptr, char *path)
{
	t_img	*texture;
	int		width;
	int		height;

	texture = ft_calloc(1, sizeof(t_img));
	if (!texture)
		return (NULL);
	texture->img = mlx_xpm_file_to_image(mlx_ptr, path, &width, &height);
	if (!texture->img)
	{
		free(texture);
		return (NULL);
	}
	texture->addr = (int *)mlx_get_data_addr(texture->img,
			&texture->bits_per_pixel, &texture->line_length, &texture->endian);
	if (!texture->addr)
	{
		mlx_destroy_image(mlx_ptr, texture->img);
		free(texture);
		return (NULL);
	}
	return (texture);
}

static int	init_textures(t_mlx *mlx)
{
	mlx->game->textures = ft_calloc(1, sizeof(t_textures));
	if (!mlx->game->textures)
		return (0);
	mlx->game->textures->no = init_texture(mlx->game->ptr, mlx->path->NO);
	mlx->game->textures->so = init_texture(mlx->game->ptr, mlx->path->SO);
	mlx->game->textures->ea = init_texture(mlx->game->ptr, mlx->path->EA);
	mlx->game->textures->we = init_texture(mlx->game->ptr, mlx->path->WE);
	mlx->game->textures->door = init_door_animation(mlx->game->ptr);
	if (!mlx->game->textures->no || !mlx->game->textures->so
		|| !mlx->game->textures->ea || !mlx->game->textures->we
		|| !mlx->game->textures->door)
		return (0);
	return (1);
}

static int	init_screen(t_mlx *mlx)
{
	mlx->game->screen = ft_calloc(1, sizeof(t_img));
	if (!mlx->game->screen)
		return (0);
	mlx->game->screen->img = mlx_new_image(mlx->game->ptr, WIN_WIDTH,
			WIN_HEIGHT);
	if (!mlx->game->screen->img)
		return (0);
	mlx->game->screen->addr = (int *)mlx_get_data_addr(mlx->game->screen->img,
			&mlx->game->screen->bits_per_pixel, &mlx->game->screen->line_length,
			&mlx->game->screen->endian);
	if (!mlx->game->screen->addr)
		return (0);
	return (1);
}

int	init_game(t_mlx *mlx)
{
	if (!mlx || !mlx->map || !mlx->player)
		return (err("Invalid game state"), close_window(mlx), 1);
	mlx->game = ft_calloc(1, sizeof(t_game));
	if (!mlx->game)
		return (err("Game allocation failed"), close_window(mlx), 1);
	mlx->game->ptr = mlx_init();
	if (!mlx->game->ptr)
		return (err("MLX initialization failed"), close_window(mlx), 1);
	mlx->game->win = mlx_new_window(mlx->game->ptr, WIN_WIDTH, WIN_HEIGHT,
			"cub3D");
	if (!mlx->game->win)
		return (err("Window creation failed"), close_window(mlx), 1);
	if (!init_screen(mlx))
		return (err("Screen initialization failed"), close_window(mlx), 1);
	if (!init_textures(mlx))
		return (err("Texture initialization failed"), close_window(mlx), 1);
	mlx->game->running = 1;
	init_raycast(mlx);
	mlx_loop_hook(mlx->game->ptr, game_loop, mlx);
	mlx_hook(mlx->game->win, 2, 1L << 0, handle_keypress, mlx);
	mlx_hook(mlx->game->win, 17, 1L << 17, close_window, mlx);
	mlx_hook(mlx->game->win, 6, 1L << 6, handle_mouse_move, mlx);
	mlx_mouse_hide(mlx->game->ptr, mlx->game->win);
	mlx_mouse_move(mlx->game->ptr, mlx->game->win, WIN_WIDTH / 2, WIN_HEIGHT
		/ 2);
	mlx_loop(mlx->game->ptr);
	return (0);
}

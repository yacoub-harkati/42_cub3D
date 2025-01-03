/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 01:34:22 by yaharkat          #+#    #+#             */
/*   Updated: 2025/01/03 02:12:10 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cleanup_texture(void *mlx_ptr, t_img **texture)
{
	if (texture && *texture)
	{
		if ((*texture)->img)
			mlx_destroy_image(mlx_ptr, (*texture)->img);
		free(*texture);
		*texture = NULL;
	}
}

static void	cleanup_textures(t_game *game)
{
	if (!game || !game->textures)
		return ;
	if (game->ptr)
	{
		cleanup_texture(game->ptr, &game->textures->no);
		cleanup_texture(game->ptr, &game->textures->so);
		cleanup_texture(game->ptr, &game->textures->ea);
		cleanup_texture(game->ptr, &game->textures->we);
	}
	free(game->textures);
	game->textures = NULL;
}

static void	cleanup_screen(t_game *game)
{
	if (!game || !game->screen)
		return ;
	if (game->ptr && game->screen->img)
		mlx_destroy_image(game->ptr, game->screen->img);
	free(game->screen);
	game->screen = NULL;
}

int	close_window(t_mlx *mlx)
{
	if (!mlx || !mlx->game)
		return (0);
	mlx_loop_end(mlx->game->ptr);
	if (mlx->game->running)
	{
		mlx->game->running = 0;
		if (mlx->game->screen)
			cleanup_screen(mlx->game);
		if (mlx->game->textures)
			cleanup_textures(mlx->game);
		if (mlx->game->win)
		{
			mlx_destroy_window(mlx->game->ptr, mlx->game->win);
			mlx->game->win = NULL;
		}
		if (mlx->game->ptr)
		{
			mlx_destroy_display(mlx->game->ptr);
			free(mlx->game->ptr);
			mlx->game->ptr = NULL;
		}
		free(mlx->game);
		mlx->game = NULL;
	}
	return (0);
}

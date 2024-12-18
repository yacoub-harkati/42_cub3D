/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzarhoun <rzarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:36:49 by rzarhoun          #+#    #+#             */
/*   Updated: 2024/12/18 19:25:10 by rzarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_img(t_textures *textures)
{
	
}

void	init_game(t_mlx	*mlx)
{
	t_game	*game;

	game = mlx->game;
	game->ptr = mlx_init();
	if (!game->ptr)
		return ;
	game->win = mlx_new_window(game->ptr, (mlx->map->width * 64), mlx->map->height * 64, "cub3d");
	if (!game->win)
		return ;
	game->textures = malloc(sizeof(t_textures));
	if (!game)
		return ;
	get_img(game->textures);
	mlx_loop(game->ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzarhoun <rzarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:36:49 by rzarhoun          #+#    #+#             */
/*   Updated: 2024/12/18 21:13:01 by rzarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_img(t_game *game)
{
	int	x;
	t_textures	*textures;

	textures = game->textures;
	textures->floor = mlx_xpm_file_to_image(game->ptr, "assets/textures/floor.xpm", &x, &x);
	textures->ceiling = mlx_xpm_file_to_image(game->ptr, "assets/textures/ceiling.xpm", &x, &x);
	textures->no = mlx_xpm_file_to_image(game->ptr, "assets/textures/no.xpm", &x, &x);
	textures->so = mlx_xpm_file_to_image(game->ptr, "assets/textures/so.xpm", &x, &x);
	textures->we = mlx_xpm_file_to_image(game->ptr, "assets/textures/we.xpm", &x, &x);
	textures->ea = mlx_xpm_file_to_image(game->ptr, "assets/textures/ea.xpm", &x, &x);
}

void	init_game(t_mlx	*mlx)
{
	t_game	*game;
	t_textures	*textures;

	game = mlx->game;
	game->ptr = mlx_init();
	if (!game->ptr)
		return ;
	game->win = mlx_new_window(game->ptr, (mlx->map->width * 64), mlx->map->height * 64, "cub3d");
	if (!game->win)
		return ;
	game->textures = malloc(sizeof(t_textures));
	if (!game->textures)
		return ;
	textures = game->textures;
	get_img(game);
	if (!textures->floor || !textures->ceiling ||
		!textures->no || !textures->so ||
		!textures->we || !textures->ea)
		return ;
	mlx_loop(game->ptr);
}

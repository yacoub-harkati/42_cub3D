/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 02:48:53 by yaharkat          #+#    #+#             */
/*   Updated: 2025/01/04 02:52:50 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_door_distance(double px, double py, int dx, int dy)
{
	double	check_dist;

	check_dist = sqrt(pow(px - dx, 2) + pow(py - dy, 2));
	return (check_dist <= DOOR_RANGE);
}

static int	is_valid_map_position(t_mlx *mlx, int x, int y)
{
	if (y < 0 || y >= mlx->map->height || x < 0 || x >= mlx->map->width)
		return (0);
	return (1);
}

static int	check_door_at_position(t_mlx *mlx, double px, double py,
		int *door_coords)
{
	int	check_x;
	int	check_y;

	check_y = (int)(py - DOOR_RANGE);
	while (check_y <= (int)(py + DOOR_RANGE))
	{
		check_x = (int)(px - DOOR_RANGE);
		while (check_x <= (int)(px + DOOR_RANGE))
		{
			if (is_valid_map_position(mlx, check_x, check_y))
			{
				if (mlx->map->map[check_y][check_x] == 'D'
					&& check_door_distance(px, py, check_x, check_y))
				{
					door_coords[0] = check_x;
					door_coords[1] = check_y;
					return (1);
				}
			}
			check_x++;
		}
		check_y++;
	}
	return (0);
}

static int	is_near_door(t_mlx *mlx, int *door_x, int *door_y)
{
	double	player_x;
	double	player_y;
	int		door_coords[2];

	player_x = mlx->player->x;
	player_y = mlx->player->y;
	if (check_door_at_position(mlx, player_x, player_y, door_coords))
	{
		*door_x = door_coords[0];
		*door_y = door_coords[1];
		return (1);
	}
	return (0);
}

void	handle_door_interaction(t_mlx *mlx)
{
	int	door_x;
	int	door_y;

	if (!mlx->game->textures->door)
		return ;
	if (is_near_door(mlx, &door_x, &door_y))
	{
		if (!mlx->game->textures->door->is_animating)
		{
			if (mlx->game->textures->door->current_frame == 0)
			{
				mlx->game->textures->door->is_animating = 1;
				mlx->game->textures->door->animation_dir = 1;
			}
			else if (mlx->game->textures->door->current_frame == DOOR_FRAMES
				- 1)
			{
				mlx->game->textures->door->is_animating = 1;
				mlx->game->textures->door->animation_dir = -1;
			}
		}
	}
}

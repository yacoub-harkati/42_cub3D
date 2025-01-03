/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 19:42:54 by yaharkat          #+#    #+#             */
/*   Updated: 2025/01/03 20:19:02 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*get_frame_path(int frame_num)
{
	char	*base_path;
	char	*frame_str;
	char	*temp;
	char	*result;

	base_path = ft_strdup("assets/textures/door/door_");
	if (!base_path)
		return (NULL);
	frame_str = ft_itoa(frame_num);
	if (!frame_str)
	{
		free(base_path);
		return (NULL);
	}
	temp = ft_strdup(base_path);
	free(base_path);
	if (!temp)
	{
		free(frame_str);
		return (NULL);
	}
	result = ft_strjoin(temp, frame_str);
	free(temp);
	free(frame_str);
	if (!result)
		return (NULL);
	temp = ft_strjoin(result, ".xpm");
	free(result);
	return (temp);
}

t_door_anim	*init_door_animation(void *mlx_ptr)
{
	t_door_anim	*door;
	char		*frame_path;
	int			i;

	door = ft_calloc(1, sizeof(t_door_anim));
	if (!door)
		return (NULL);
	i = 0;
	while (i < DOOR_FRAMES)
	{
		frame_path = get_frame_path(i);
		if (!frame_path)
		{
			cleanup_door_frames(mlx_ptr, door);
			return (NULL);
		}
		door->frames[i] = init_texture(mlx_ptr, frame_path);
		free(frame_path);
		if (!door->frames[i])
		{
			cleanup_door_frames(mlx_ptr, door);
			return (NULL);
		}
		i++;
	}
	door->current_frame = 0;
	door->frame_counter = 0;
	door->is_animating = 0;
	door->animation_dir = 1;
	return (door);
}

void	cleanup_door_frames(void *mlx_ptr, t_door_anim *door)
{
	int	i;

	if (!door)
		return ;
	i = 0;
	while (i < DOOR_FRAMES)
	{
		if (door->frames[i])
		{
			if (door->frames[i]->img)
				mlx_destroy_image(mlx_ptr, door->frames[i]->img);
			free(door->frames[i]);
		}
		i++;
	}
	free(door);
}

void	update_door_animation(t_door_anim *door)
{
	if (!door || !door->is_animating)
		return ;
	door->frame_counter++;
	if (door->frame_counter >= FRAME_DELAY)
	{
		door->frame_counter = 0;
		door->current_frame += door->animation_dir;
		if (door->current_frame >= DOOR_FRAMES - 1)
		{
			door->current_frame = DOOR_FRAMES - 1;
			door->is_animating = 0;
		}
		else if (door->current_frame <= 0)
		{
			door->current_frame = 0;
			door->is_animating = 0;
		}
	}
}

static int	is_near_door(t_mlx *mlx, int *door_x, int *door_y)
{
	int		check_x;
	int		check_y;
	double	player_x;
	double	player_y;
	double	check_dist;

	player_x = mlx->player->x;
	player_y = mlx->player->y;
	// Check in a small radius around the player
	for (check_y = (int)(player_y - DOOR_RANGE); check_y <= (int)(player_y
			+ DOOR_RANGE); check_y++)
	{
		for (check_x = (int)(player_x - DOOR_RANGE); check_x <= (int)(player_x
				+ DOOR_RANGE); check_x++)
		{
			// Check map bounds
			if (check_y < 0 || check_y >= mlx->map->height || check_x < 0
				|| check_x >= mlx->map->width)
				continue ;
			// Check if there's a door
			if (mlx->map->map[check_y][check_x] == 'D')
			{
				// Calculate exact distance
				check_dist = sqrt(pow(player_x - check_x, 2) + pow(player_y
							- check_y, 2));
				if (check_dist <= DOOR_RANGE)
				{
					*door_x = check_x;
					*door_y = check_y;
					return (1);
				}
			}
		}
	}
	return (0);
}

void	handle_door_interaction(t_mlx *mlx)
{
	int door_x;
	int door_y;

	if (!mlx->game->textures->door)
		return ;

	if (is_near_door(mlx, &door_x, &door_y))
	{
		// If door is not already animating
		if (!mlx->game->textures->door->is_animating)
		{
			// If door is closed (frame 0), open it
			if (mlx->game->textures->door->current_frame == 0)
			{
				mlx->game->textures->door->is_animating = 1;
				mlx->game->textures->door->animation_dir = 1;
			}
			// If door is open (last frame), close it
			else if (mlx->game->textures->door->current_frame == DOOR_FRAMES
				- 1)
			{
				mlx->game->textures->door->is_animating = 1;
				mlx->game->textures->door->animation_dir = -1;
			}
		}
	}
}
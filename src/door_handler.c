/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 19:42:54 by yaharkat          #+#    #+#             */
/*   Updated: 2025/01/04 02:49:23 by yaharkat         ###   ########.fr       */
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
		make_color_transparent(door->frames[i]);
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

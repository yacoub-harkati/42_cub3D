/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 02:29:52 by yaharkat          #+#    #+#             */
/*   Updated: 2025/01/04 02:30:46 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	make_color_transparent(t_img *img)
{
	int	i;
	int	total_pixels;

	if (!img || !img->addr)
		return ;
	total_pixels = TEXTURE_SIZE * TEXTURE_SIZE;
	i = 0;
	while (i < total_pixels)
	{
		if (img->addr[i] == COLOR_TO_REPLACE)
			img->addr[i] = TRANSPARENT_COLOR;
		i++;
	}
}

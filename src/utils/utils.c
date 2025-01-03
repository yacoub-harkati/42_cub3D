/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 14:15:25 by root              #+#    #+#             */
/*   Updated: 2025/01/03 21:23:38 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	count_lines(char *av)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(av, O_RDONLY);
	if (fd < 0)
		return (err("Error\n"), -1);
	count = 0;
	while ((line = get_next_line(fd)))
	{
		count++;
		free(line);
	}
	close(fd);
	return (count);
}

void	get_map(char **file, t_map *map, int index)
{
	int	i;

	i = 0;
	while (i < map->height && file[index])
	{
		map->map[i] = ft_strdup(file[index]);
		i++;
		index++;
	}
	map->map[i] = NULL;
}

void	get_file(char *str, char **file)
{
	int	i;
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (err("Error\n"));
	i = 0;
	file[i] = ft_strtrim(get_next_line(fd), "\n");
	while (file[i])
	{
		i++;
		file[i] = ft_strtrim(get_next_line(fd), "\n");
	}
}

size_t	get_width(char **map)
{
	int		i;
	size_t	width;

	i = 0;
	width = ft_strlen(map[0]);
	while (map[i])
	{
		if (ft_strlen(map[i]) > width)
			width = ft_strlen(map[i]);
		i++;
	}
	return (width);
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	free_matrix(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	*ft_ternary(int condition, void *if_true, void *if_false)
{
	if (condition)
		return (if_true);
	return (if_false);
}

void	make_color_transparent(t_img *img)
{
	int i;
	int total_pixels;

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
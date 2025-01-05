/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzarhoun <rzarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:32:28 by rzarhoun          #+#    #+#             */
/*   Updated: 2025/01/04 21:52:11 by rzarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_path(char **file, char *str)
{
	int		i;
	char	*s;
	char	**split;

	i = 0;
	while (file[i])
	{
		s = ft_strnstr(file[i], str, ft_strlen(file[i]));
		if (s)
			break ;
		i++;
	}
	if (s)
		s = ft_strtrim(s, "\n");
	split = ft_split(s, ' ');
	if (!split)
		return (NULL);
	free(s);
	s = ft_strdup(split[1]);
	free_matrix(split);
	return (s);
}

int	is_xpm_png_file(char *file)
{
	int	len;

	len = ft_strlen(file);
	if ((file[len - 4] == '.' && file[len - 3] == 'x' && file[len - 2] == 'p'
			&& file[len - 1] == 'm') || (file[len - 4] == '.'
			&& file[len - 3] == 'p' && file[len - 2] == 'n'
			&& file[len - 1] == 'g'))
		return (1);
	return (0);
}

int	check_path_file(t_path *path)
{
	int	fd;

	fd = open(path->no, O_RDONLY);
	if (fd < 0)
		return (err("Error\nNO texture file doesnt exist\n"), 1);
	close(fd);
	fd = open(path->so, O_RDONLY);
	if (fd < 0)
		return (err("Error\nSO texture file doesnt exist\n"), 1);
	close(fd);
	fd = open(path->we, O_RDONLY);
	if (fd < 0)
		return (err("Error\nWE texture file doesnt exist\n"), 1);
	close(fd);
	fd = open(path->ea, O_RDONLY);
	if (fd < 0)
		return (err("Error\nEA texture file doesnt exist\n"), 1);
	close(fd);
	if (!is_xpm_png_file(path->no) || !is_xpm_png_file(path->so)
		|| !is_xpm_png_file(path->we) || !is_xpm_png_file(path->ea))
		return (err("Error\nNO texture file have to be a .xpm or .png file\n"),
			1);
	return (0);
}

int	check_rgb(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if ((mlx->floor[i] < 0 || mlx->floor[i] > 255) || (mlx->ceiling[i] < 0
				|| mlx->ceiling[i] > 255))
			return (err("Error\nInvalid rgb color\n"), 1);
		i++;
	}
	return (0);
}

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
		|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2)
		|| !ft_strncmp(line, "C", 1) || !ft_strncmp(line, "F", 1))
		return (0);
	while (line[i])
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == ' ' || line[i] == 'N'
			|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
			return (1);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:32:28 by root              #+#    #+#             */
/*   Updated: 2024/12/08 00:49:43 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_identifier(char **file, char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (file[i])
	{
		if (ft_strnstr(file[i], str, ft_strlen(file[i])))
			count++;
		i++;
	}
	if (count == 0)
		return (err("Error\n"), err(str), err(" identifier doesnt exist\n"), 0);
	else if (count > 1)
		return (err("Error\n"), err(str), err(" identifier is set more than one time\n"), 0);
	else
		return (1);
}

int	check_order(char **file)
{
	int	no;
	int	so;
	int	we;
	int	ea;
	int	f;
	int	c;
	int	i;

	no = 0;
	so = 0;
	we = 0;
	ea = 0;
	f = 0;
	c = 0;
	i = 0;
	while (file[i])
	{
		if (ft_strnstr(file[i], "NO", ft_strlen(file[i])))
			no = i;
		else if (ft_strnstr(file[i], "SO", ft_strlen(file[i])))
			so = i;
		else if (ft_strnstr(file[i], "WE", ft_strlen(file[i])))
			we = i;
		else if (ft_strnstr(file[i], "EA", ft_strlen(file[i])))
			ea = i;
		else if (ft_strnstr(file[i], "F", ft_strlen(file[i])))
			f = i;
		else if (ft_strnstr(file[i], "C", ft_strlen(file[i])))
			c = i;
		i++;
	}
	if (no > so || no > we || no > ea || no > f || no > c ||
		so > we || so > ea || so > f || so > c || we > ea ||
		we > f || we > c || ea > f || ea > c || f > c)
		return (err("Error\nIdentifiers arent in right order\n"), 1);
	return (0);
}

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
	return (split[1]);
}

int	is_xpm_png_file(char *file)
{
	int	len;

	len = ft_strlen(file);
	if ((file[len - 4] == '.' && file[len - 3] == 'x' &&
		file[len - 2] == 'p' && file[len - 1] == 'm') ||
		(file[len - 4] == '.' && file[len - 3] == 'p' &&
		file[len - 2] == 'n' && file[len - 1] == 'g'))
		return (1);
	return (0);
}

int	check_path_file(t_path *path)
{
	int		fd;

	fd = open(path->NO, O_RDONLY);
	if (fd < 0)
		return (err("Error\nNO texture file doesnt exist\n"), 1);
	close (fd);
	fd = open(path->SO, O_RDONLY);
	if (fd < 0)
		return (err("Error\nSO texture file doesnt exist\n"), 1);
	close (fd);
	fd = open(path->WE, O_RDONLY);
	if (fd < 0)
		return (err("Error\nWE texture file doesnt exist\n"), 1);
	close (fd);
	fd = open(path->EA, O_RDONLY);
	if (fd < 0)
		return (err("Error\nEA texture file doesnt exist\n"), 1);
	close (fd);
	if (!is_xpm_png_file(path->NO))
		return (err("Error\nNO texture file have to be a .xpm or .png file\n"), 1);
	if (!is_xpm_png_file(path->SO))
		return (err("Error\nSO texture file have to be a .xpm or .png file\n"), 1);
	if (!is_xpm_png_file(path->WE))
		return (err("Error\nWE texture file have to be a .xpm or .png file\n"), 1);
	if (!is_xpm_png_file(path->EA))
		return (err("Error\nEA texture file have to be a .xpm or .png file\n"), 1);
	return (0);
}

int	check_path(t_mlx *mlx, t_path **path)
{
	*path = malloc(sizeof(t_path));
	if (!*path)
		return (1);
	(*path)->NO = get_path(mlx->file, "NO");
	if (!(*path)->NO)
		return (err("Error\nNO path is missing\n"), 1);
	(*path)->SO = get_path(mlx->file, "SO");
	if (!(*path)->SO)
		return (err("Error\nSO path is missing\n"), 1);
	(*path)->WE = get_path(mlx->file, "WE");
	if (!(*path)->WE)
		return (err("Error\nWE path is missing\n"), 1);
	(*path)->EA = get_path(mlx->file, "EA");
	if (!(*path)->EA)
		return (err("Error\nEA path is missing\n"), 1);
	if (check_path_file(*path))
		return (1);
	return (0);
}

int	check_file(t_mlx *mlx)
{
	if (!check_identifier(mlx->file, "NO") || !check_identifier(mlx->file, "SO") ||
		!check_identifier(mlx->file, "WE") || !check_identifier(mlx->file, "EA") ||
		!check_identifier(mlx->file, "F") || !check_identifier(mlx->file, "C"))
		return (1);
	if (check_order(mlx->file))
		return (1);
	if (check_path(mlx, &mlx->path))
		return (1);
	return (0);
}

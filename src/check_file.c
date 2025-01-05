/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzarhoun <rzarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:48:16 by rzarhoun          #+#    #+#             */
/*   Updated: 2025/01/05 20:54:31 by rzarhoun         ###   ########.fr       */
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
		{
			if (ft_strncmp(file[i], str, ft_strlen(str)))
				(err("Error\nIdentifier and path order is invalid\n"), exit(1));
			count++;
		}
		i++;
	}
	if (count == 0)
		return (err("Error\n"), err(str), err(" identifier doesnt exist\n"), 0);
	else if (count > 1)
		return (err("Error\n"), err(str),
			err(" identifier is set more than one time\n"), 0);
	else
		return (1);
}

int	check_order(char **file)
{
	t_pos	*position;

	position = init_pos(file);
	if (!position)
		return (1);
	if (position->no > position->so || position->no > position->we
		|| position->no > position->ea || position->no > position->f
		|| position->no > position->c || position->so > position->we
		|| position->so > position->ea || position->so > position->f
		|| position->so > position->c || position->we > position->ea
		|| position->we > position->f || position->we > position->c
		|| position->ea > position->f || position->ea > position->c
		||position->f > position->c)
		return (err("Error\nIdentifiers arent in right order\n"), free(position), 1);
	return (free(position), 0);
}

int	check_path(t_mlx *mlx, t_path **path)
{
	*path = malloc(sizeof(t_path));
	if (!*path)
		return (1);
	(*path)->no = get_path(mlx->file, "NO");
	if (!(*path)->no)
		return (err("Error\nNO path is missing\n"), 1);
	(*path)->so = get_path(mlx->file, "SO");
	if (!(*path)->so)
		return (err("Error\nSO path is missing\n"), 1);
	(*path)->we = get_path(mlx->file, "WE");
	if (!(*path)->we)
		return (err("Error\nWE path is missing\n"), 1);
	(*path)->ea = get_path(mlx->file, "EA");
	if (!(*path)->ea)
		return (err("Error\nEA path is missing\n"), 1);
	if (check_path_file(*path))
		return (1);
	if (check_fc(mlx))
		return (1);
	return (0);
}

int	check_map_is_at_end(char **file)
{
	int	i;
	int	map_start;

	i = 0;
	map_start = -1;
	while (file[i])
	{
		if (is_map_line(file[i]))
		{
			map_start = i;
			break ;
		}
		i++;
	}
	if (map_start == -1)
		return (1);
	while (file[i])
	{
		if (!is_map_line(file[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_file(t_mlx *mlx)
{
	if (!check_identifier(mlx->file, "NO") || !check_identifier(mlx->file, "SO")
		|| !check_identifier(mlx->file, "WE") || !check_identifier(mlx->file,
			"EA") || !check_identifier(mlx->file, "F")
		|| !check_identifier(mlx->file, "C"))
		return (1);
	if (check_order(mlx->file))
		return (1);
	if (check_path(mlx, &mlx->path))
		return (1);
	if (check_map_is_at_end(mlx->file))
		return (err("Error\nMap is not at the end of file\n"), 1);
	return (0);
}

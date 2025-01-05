/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzarhoun <rzarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 22:45:13 by root              #+#    #+#             */
/*   Updated: 2025/01/05 23:10:10 by rzarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_mlx	*init_struct(int ac, char **av)
{
	t_mlx	*mlx;
	t_map	*map;

	(void)ac;
	mlx = malloc(sizeof(t_mlx));
	if (!mlx)
		return (err("Error\n"), NULL);
	mlx->file = parse_file(av);
	if (check_file(mlx))
		exit(1);
	mlx->map = parse_map(mlx->file);
	map = mlx->map;
	if (check_map(map))
		exit(1);
	mlx->player = get_player_info(mlx->map->map);
	if (!mlx->player)
		return (NULL);
	return (mlx);
}

t_pos	*init_pos(char **file)
{
	int		i;
	t_pos	*position;

	i = 0;
	position = malloc(sizeof(t_pos));
	if (!position)
		return (NULL);
	while (file[i])
	{
		if (ft_strnstr(file[i], "NO", ft_strlen(file[i])))
			position->no = i;
		else if (ft_strnstr(file[i], "SO", ft_strlen(file[i])))
			position->so = i;
		else if (ft_strnstr(file[i], "WE", ft_strlen(file[i])))
			position->we = i;
		else if (ft_strnstr(file[i], "EA", ft_strlen(file[i])))
			position->ea = i;
		else if (ft_strnstr(file[i], "F", ft_strlen(file[i])))
			position->f = i;
		else if (ft_strnstr(file[i], "C", ft_strlen(file[i])))
			position->c = i;
		i++;
	}
	return (position);
}

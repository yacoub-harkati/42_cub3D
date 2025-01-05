/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 14:06:23 by root              #+#    #+#             */
/*   Updated: 2024/12/08 01:48:40 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_args(int ac, char **av)
{
	int		fd;
	char	*file;

	if (ac != 2)
	{
		err("Error\nInvalid number of arguments\n");
		return (1);
	}
	file = ft_strchr(av[1], '.');
	if (!file || (file && ft_strcmp(file, ".cub")))
	{
		err("Error\nMap must be a .cub file\n");
		return (1);
	}
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		err("Error\nNo such file or directory\n");
		return (1);
	}
	close (fd);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 22:45:13 by root              #+#    #+#             */
/*   Updated: 2024/12/08 21:06:41 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_mlx	*init_struct(int ac, char **av)
{
	t_mlx	*mlx;

	(void)ac;
	mlx = malloc(sizeof(t_mlx));
	if (!mlx)
		return(err("Error\n"), NULL);
	mlx->file = parse_file(av);
	if (check_file(mlx))
		exit (1);
	mlx->map = parse_map(mlx->file);
	return (mlx);
}

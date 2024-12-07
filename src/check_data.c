/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:32:28 by root              #+#    #+#             */
/*   Updated: 2024/12/07 22:33:32 by root             ###   ########.fr       */
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

int	check_file(char **file)
{
	if (!check_identifier(file, "NO") || !check_identifier(file, "SO") ||
		!check_identifier(file, "WE") || !check_identifier(file, "EA") ||
		!check_identifier(file, "F") || !check_identifier(file, "C"))
		return (1);
	
	return (0);
}

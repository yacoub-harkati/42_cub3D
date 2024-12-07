/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:32:28 by root              #+#    #+#             */
/*   Updated: 2024/12/07 23:36:27 by root             ###   ########.fr       */
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

int	check_file(char **file)
{
	if (!check_identifier(file, "NO") || !check_identifier(file, "SO") ||
		!check_identifier(file, "WE") || !check_identifier(file, "EA") ||
		!check_identifier(file, "F") || !check_identifier(file, "C"))
		return (1);
	if (check_order(file))
		return (1);
	return (0);
}

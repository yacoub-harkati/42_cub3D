#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

# include "libft.h"

typedef struct s_path
{
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
}	t_path;

typedef struct s_map
{
	char	**map;
	int		height;
	int		width;
}	t_map;


typedef struct	s_mlx
{
	char	**file;
	t_map	*map;
	t_path	*path;
	int		*floor;
	int		*ceiling;
}	t_mlx;

void	err(char *str);
int		check_args(int ac, char **av);
int 	ft_strcmp(char *s1, char *s2);
t_mlx	*init_struct(int ac, char **av);
char	**parse_file(char **av);
int		count_lines(char *av);
void	get_file(char *file, char **map);
int		check_file(t_mlx *mlx);
int		is_map_line(char *line);
t_map	*parse_map(char **file);
void	get_map(char **file, t_map *map, int index);
int		check_map(t_map *map);
size_t	get_width(char **map);

#endif
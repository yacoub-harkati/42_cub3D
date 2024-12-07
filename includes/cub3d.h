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


typedef struct	s_mlx
{
	char	**map;
	t_path	*path;
}	t_mlx;

void	err(char *str);
int		check_args(int ac, char **av);
int 	ft_strcmp(char *s1, char *s2);
t_mlx	*init_struct(int ac, char **av);
char	**parse_map(char **av);

#endif
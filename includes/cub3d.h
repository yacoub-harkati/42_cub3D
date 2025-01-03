/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 23:48:16 by yaharkat          #+#    #+#             */
/*   Updated: 2025/01/03 02:30:09 by yaharkat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIN_WIDTH 1024
# define WIN_HEIGHT 768

# define TEXTURE_SIZE 64
# define PI 3.14159265359
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

typedef struct s_img
{
	void		*img;
	int			*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	char		position;
}				t_player;

typedef struct s_ray
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			tex_x;
	double		wall_x;
}				t_ray;

typedef struct s_draw_data
{
	t_img		*texture;
	double		step;
	double		tex_pos;
	double		shade;
	int			tex_x;
	int			x;
	int			r;
	int			g;
	int			b;
}				t_draw_data;

typedef struct s_minimap
{
	int			tile_size;
	int			mini_x;
	int			mini_y;
	int			border;
	int			map_width;
	int			map_height;
	int			player_x;
	int			player_y;
	int			pixel_x;
	int			pixel_y;
}				t_minimap;

typedef struct s_path
{
	char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;
}				t_path;

typedef struct s_map
{
	char		**map;
	int			height;
	int			width;
}				t_map;

typedef struct s_textures
{
	t_img		*no;
	t_img		*so;
	t_img		*we;
	t_img		*ea;
	int			*floor;
	int			*ceiling;
}				t_textures;

typedef struct s_game
{
	void		*ptr;
	void		*win;
	t_img		*screen;
	t_textures	*textures;
	int			running;
}				t_game;

typedef struct s_mlx
{
	char		**file;
	t_map		*map;
	t_path		*path;
	int			*floor;
	int			*ceiling;
	t_player	*player;
	t_game		*game;
	t_ray		*ray;
}				t_mlx;

t_mlx			*init_struct(int ac, char **av);
int				init_game(t_mlx *mlx);
void			init_raycast(t_mlx *mlx);

char			**parse_file(char **av);
t_map			*parse_map(char **file);
void			get_map(char **file, t_map *map, int index);
void			get_file(char *file, char **map);

int				check_args(int ac, char **av);
int				check_file(t_mlx *mlx);
int				check_map(t_map *map);
int				is_map_line(char *line);
int				count_lines(char *av);

t_player		*get_player_info(char **map);
void			move_player(t_mlx *mlx, int key);
void			rotate_player(t_mlx *mlx, int direction);

void			cast_rays(t_mlx *mlx);
void			draw_walls(t_mlx *mlx, t_ray *ray, int x);
void			draw_minimap(t_mlx *mlx);

int				handle_keypress(int key, t_mlx *mlx);
int				close_window(t_mlx *mlx);
int				game_loop(t_mlx *mlx);

int				create_rgb(int r, int g, int b);
void			err(char *str);
int				ft_strcmp(char *s1, char *s2);
size_t			get_width(char **map);

#endif
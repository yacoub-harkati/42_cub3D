/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 23:48:16 by yaharkat          #+#    #+#             */
/*   Updated: 2025/01/03 23:09:21 by yaharkat         ###   ########.fr       */
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

# define MOUSE_SENSITIVITY 0.0032

# define DOOR_FRAMES 24
# define FRAME_DELAY 2
# define KEY_E 101
# define DOOR_RANGE 2.0
# define COLOR_TO_REPLACE 16711890
# define TRANSPARENT_COLOR 16515796

typedef struct s_img
{
	void		*img;
	int			*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_door_anim
{
	t_img		*frames[DOOR_FRAMES];
	int			current_frame;
	int			frame_counter;
	int			is_animating;
	int			animation_dir;
}				t_door_anim;

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
	char		hit_type;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			tex_x;
	double		wall_x;
	int			has_door;
	double		wall_dist;
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
	t_door_anim	*door;
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

t_img			*init_texture(void *mlx_ptr, char *path);
void			cast_rays(t_mlx *mlx);
void			draw_walls(t_mlx *mlx, t_ray *ray, int x);
void			draw_minimap(t_mlx *mlx);

int				handle_keypress(int key, t_mlx *mlx);
int				close_window(t_mlx *mlx);
void			cleanup_door_frames(void *mlx_ptr, t_door_anim *door);
int				game_loop(t_mlx *mlx);

int				handle_mouse_move(int x, int y, t_mlx *mlx);
void			rotate_camera(t_mlx *mlx, double rotation);

t_door_anim		*init_door_animation(void *mlx_ptr);
void			cleanup_door_frames(void *mlx_ptr, t_door_anim *door);
void			update_door_animation(t_door_anim *door);
void			handle_door_interaction(t_mlx *mlx);
void			make_color_transparent(t_img *img);

int				create_rgb(int r, int g, int b);
void			err(char *str);
int				ft_strcmp(char *s1, char *s2);
size_t			get_width(char **map);
void			free_matrix(char **str);
void			*ft_ternary(int condition, void *if_true, void *if_false);

void			draw_doors(t_mlx *mlx, t_ray *ray, int x);
void			perform_dda_walls(t_ray *ray, t_mlx *mlx, int *map_x,
					int *map_y);
void			perform_dda_doors(t_ray *ray, t_mlx *mlx, int *map_x,
					int *map_y);
double			calc_shade(t_ray *ray, char wall_type);
t_img			*select_texture(t_mlx *mlx, t_ray *ray);
void			calc_texture_coords(t_ray *ray, t_mlx *mlx, double *wall_x,
					int *tex_x, char wall_type);
void			calc_step_dist(t_ray *ray, t_mlx *mlx, int map_x, int map_y);
void			init_ray(t_ray *ray, t_mlx *mlx, int x);
void			perform_dda_doors(t_ray *ray, t_mlx *mlx, int *map_x,
					int *map_y);
void			calc_wall_height(t_ray *ray, t_mlx *mlx, int map_x, int map_y);

#endif
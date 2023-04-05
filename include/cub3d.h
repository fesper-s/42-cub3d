/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fesper-s <fesper-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 08:13:26 by fesper-s          #+#    #+#             */
/*   Updated: 2023/04/05 10:26:50 by fesper-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifdef __linux__
#  include "../lib/mlx_linux/mlx.h"
# else
#  include "../lib/mlx/mlx.h"
# endif

# include "../lib/libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>

# ifdef __linux__

enum e_keycode
{
	W_KEY = 119,
	S_KEY = 115,
	A_KEY = 97,
	D_KEY = 100,
	LEFT_KEY = 65361,
	RIGHT_KEY = 65363,
	ESC = 65307
};
# else

enum e_keycode
{
	W_KEY = 13,
	S_KEY = 1,
	A_KEY = 0,
	D_KEY = 2,
	LEFT_KEY = 123,
	RIGHT_KEY = 124,
	ESC = 53
};
# endif

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;


typedef struct s_player
{
	double	pl_x;
	double	pl_y;
	double	pldir_x;
	double	pldir_y;
	double	old_pldir_x;
	int		ver_walk;
	int		hor_walk;
	int		turn_dir;
}	t_player;

typedef struct s_raycast
{
	double	plane_x;
	double	plane_y;
	double	old_plane_x;
	double	raydir_x;
	double	raydir_y;
	double	camera_x;
	double	delta_x;
	double	delta_y;
	double	side_x;
	double	side_y;
	double	step_x;
	double	step_y;
	int		map_x;
	int		map_y;
	double	camera_wall;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_id;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	double	wall_x;
}	t_raycast;

typedef struct s_map
{
	char	**map;
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	int		**n_texture;
	int		**s_texture;
	int		**e_texture;
	int		**w_texture;
	char	*floor;
	char	*ceiling;
	int		f_color;
	int		c_color;
}	t_map;

typedef struct s_game
{
	int					width;
	int					height;
	double				frame;
	double				old_frame;
	void				*mlx;
	void				*mlx_win;
	struct s_map		*map;
	struct s_player		*pl;
	struct s_raycast	*ray;
	struct s_keys		*keys;
}	t_game;

// map.c
int		read_map(char *path, t_map *map);
int		check_map(char *path, t_map *map);

//check.c
int		check_sprites(t_map *map);

//init.c

void	pl_pos(t_game *game, t_map *map);
void	init_var(t_game *game);

// textures.c
char	*check_line(char *line);
char	**get_hex_color(int fd);
char	*check_texture_line(char *line);
char	**get_texture_line(int fd);
int		**convert_texture(char **texture_line, char **hex_color, int i, int j);

// texture_direction.c
void	get_north_texture(t_map *map);
void	get_south_texture(t_map *map);
void	get_east_texture(t_map *map);
void	get_west_texture(t_map *map);
void	get_texture(t_map *map);

// texture_utils.c
int		rgb_to_hex(char *rgb);

//raycast.c
void	raycasting(t_game *game);

//movement.c
void	vertical_movement(t_game *game, double speed);
void	horizontal_movement(t_game *game, double speed);
void	camera_movement(t_game *game, double speed);

//create a event.c file and put these in
int		key_press(int key, t_game *game);
int		key_release(int key, t_game *game);

// utils.c
int		ft_strrncmp(char *s1, char *s2, int len);
void	replace_char(char *str, char old, char new);
int		char_in_str(char *str, char c);

// ft_atoi_base.c
int		ft_atoi_base(const char *str, int str_base);

// error.c
int		print_error(char *msg);
void	exit_error(char *msg);

// memory.c
void	free_charpp(char **ptr);
void	free_intpp(int **ptr);
void	free_map(t_map *map);

// free_game.c
void	free_game(t_game *game);

#endif

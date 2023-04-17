/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fesper-s <fesper-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 08:13:26 by fesper-s          #+#    #+#             */
/*   Updated: 2023/04/17 11:41:44 by fesper-s         ###   ########.fr       */
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
	ESC_KEY = 65307
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
	ESC_KEY = 53
};
# endif

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_image;

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
	void				*mlx;
	void				*mlx_win;
	struct s_map		*map;
	struct s_player		*pl;
	struct s_raycast	*ray;
	struct s_image		*img;
}	t_game;

//main.c
int		close_game(t_game *game);
int		game_loop(t_game *game);
int		cub3d(char *path, t_map *map, t_game *game);

//map.c
void	get_map_info(int fd, t_map *map, int *j, int *found_map);
int		assign_map(t_map *map, char *path, int map_len);
int		read_map(char *path, t_map *map);
int		check_map(char *path, t_map *map);
void	insert_fill_line(t_map *map, char ***b_map);

//map_validation.c
void	count_players(t_map *map);
void	map_validation(t_map *map);
void	check_map_elements(t_map *map);
void	check_breach(char **b_map);

//check.c
void	check_sprites(t_map *map);

//init.c
void	init_var(t_game *game, t_map *map);
void	pl_pos(t_game *game, t_map *map);
void	set_player_pov(t_game *game, int i, int j);
void	init_raycast(t_game *game, int x);
void	init_map(t_map *map);

//raycast.c
void	raycasting(t_game *game);
void	step_and_side_calc(t_game *game);
void	camera_wall_calc(t_game *game);
void	dda(t_game *game);
void	get_line_position(t_game *game);

//draw.c
void	img_pixel_put(t_game *game, int x, int y, int color);
void	img_paste_pixel(t_game *game, int x, int y, int pixel);
void	ver_line(int x, t_game *game, int **tex);
void	get_texture_id(t_game *game);
void	get_texture_pos(t_game *game, int x);

//textures.c
char	*check_line(char *line);
char	**get_hex_color(int fd);
char	*check_texture_line(char *line);
void	joining_lines(char **line, char **buffer, int fd);
char	**get_texture_line(int fd);

//texture_direction.c
void	get_north_texture(t_map *map);
void	get_south_texture(t_map *map);
void	get_east_texture(t_map *map);
void	get_west_texture(t_map *map);
void	get_texture(t_map *map);

//texture_utils.c
int		**convert_texture(char **texture_line, char **hex_color, int i, int j);
int		rgb_to_hex(char *rgb);
void	getting_hex_colors(char **line, char **hex_line, int fd);
void	check_floor_and_ceiling(char *floor, char *ceiling);

//movement.c
void	vertical_movement(t_game *game, double speed);
void	horizontal_movement(t_game *game, double speed);
void	camera_movement(t_game *game, double speed);
int		key_press(int key, t_game *game);
int		key_release(int key, t_game *game);

//utils.c
int		ft_strrncmp(char *s1, char *s2, int len);
void	replace_char(char *str, char old, char new);
int		char_in_str(char *str, char c);
int		maplen(char *path);
int		grand_line(char **str);

//ft_atoi_base.c
int		ft_atoi_base(const char *str, int str_base);

//error.c
int		print_error(char *msg);
void	exit_error(char *msg);

//memory.c
void	free_charpp(char **ptr);
void	free_intpp(int **ptr);
void	free_map(t_map *map);
void	free_two(char *p1, char *p2);

// free_game.c
void	free_game(t_game *game);

#endif

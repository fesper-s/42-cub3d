/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fesper-s <fesper-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 08:13:26 by fesper-s          #+#    #+#             */
/*   Updated: 2023/03/28 08:26:57 by fesper-s         ###   ########.fr       */
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

typedef struct s_player
{
	double	pl_x;
	double	pl_y;
	double	pldir_x;
	double	pldir_y;
} t_player;

typedef struct s_raycast
{
	double	plane_x;
	double	plane_y;
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
	int 	hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;


} t_raycast;

typedef struct s_map
{
	char	**map;
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	char	*floor;
	char	*ceiling;
} t_map;

typedef struct s_game
{
	int		width;
	int		height;
	double	frame;
	double	old_frame;

	void	*mlx;
	void	*mlx_win;
	
	struct	s_map		*map;
	struct	s_player	*pl;
	struct	s_raycast	*ray;
} t_game;

// map.c
int		read_map(char *path, t_map *map);
int		check_map(char *path, t_map *map);

//check.c
int		check_sprites(t_map *map);

//init.c

void	pl_pos(t_game *game, t_map *map);
void	init_var(t_map *map, t_game *game);

// textures.c
int		**get_texture(void);

//raycast.c
void	raycasting(t_game *game);

// utils.c
int		ft_strrncmp(char *s1, char *s2, int len);
void	replace_char(char *str, char old, char new);
void	free_map(t_map *map);
int		char_in_str(char *str, char c);

//
int		ft_atoi_base(const char *str, int str_base);

// error.c
int		print_error(char *msg);

// memory.c
void	free_charpp(char **ptr);

#endif

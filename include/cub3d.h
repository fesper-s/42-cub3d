/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gussoare <gussoare@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 08:13:26 by fesper-s          #+#    #+#             */
/*   Updated: 2023/03/21 13:28:05 by gussoare         ###   ########.fr       */
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

//raycast.c
void	raycasting(t_game *game);

// error.c
int		print_error(char *msg);

// utils.c
int		ft_strrncmp(char *s1, char *s2, int len);
void 	replace_char(char *str, char old, char new);
void	free_map(t_map *map);
int		char_in_str(char *str, char c);

#endif

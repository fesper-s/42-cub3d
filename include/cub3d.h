/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gussoare <gussoare@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 08:13:26 by fesper-s          #+#    #+#             */
/*   Updated: 2023/03/13 14:33:09 by gussoare         ###   ########.fr       */
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

typedef struct s_map
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	char	*floor;
	char	*ceiling;
} t_map;

// map.c
int		read_map(char *path, t_map *map);
int		check_map(char *path, t_map *map);

//check.c
int		check_sprites(t_map *map);

// error.c
int		print_error(char *msg);

// utils.c
int		ft_strrncmp(char *s1, char *s2, int len);

#endif

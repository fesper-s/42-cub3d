/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fesper-s <fesper-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 08:13:26 by fesper-s          #+#    #+#             */
/*   Updated: 2023/03/13 13:37:53 by fesper-s         ###   ########.fr       */
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
	int		*floor;
	int		*ceiling;
} t_map;

// map.c
int		read_map(char *path, t_map *map);
int		check_map(char *path, t_map *map);

// error.c
int		print_error(char *msg);

// utils.c
int		ft_strrncmp(char *s1, char *s2, int len);

#endif

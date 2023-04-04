/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fesper-s <fesper-s@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 08:24:22 by fesper-s          #+#    #+#             */
/*   Updated: 2023/04/04 09:50:55 by fesper-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_charpp(char **ptr)
{
	int	i;

	i = -1;
	while (ptr[++i])
		free(ptr[i]);
	free(ptr);
}

void	free_intpp(int **ptr)
{
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(ptr);
}

void	free_map(t_map *map)
{
	free_charpp(map->map);
	free(map->north);
	free(map->south);
	free(map->east);
	free(map->west);
	free_intpp(map->n_texture);
	free_intpp(map->s_texture);
	free_intpp(map->e_texture);
	free_intpp(map->w_texture);
	free(map->floor);
	free(map->ceiling);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gussoare <gussoare@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:32:20 by gussoare          #+#    #+#             */
/*   Updated: 2023/03/28 14:22:10 by gussoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pl_pos(t_game *game, t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (map->map[++i])
	{
		j = -1;
		while (map->map[i][++j])
		{
			if (char_in_str("NSEW", map->map[i][j]))
			{
				game->pl->pl_x = i;
				game->pl->pl_y = j;
				if (map->map[i][j] == 'N')
					game->pl->pldir_x = 1;
				else if (map->map[i][j] == 'S')
					game->pl->pldir_x = -1;
				else if (map->map[i][j] == 'E')
					game->pl->pldir_y = 1;
				else if (map->map[i][j] == 'W')
					game->pl->pldir_y = -1;
				map->map[i][j] = '0';
			}
			
		}
	}
}

void	init_var(t_game *game)
{
	game->ray->raydir_x = 0;
	game->ray->raydir_y = 0;
	game->ray->camera_x = 0;
	game->ray->map_x = (int)game->pl->pl_x;
	game->ray->map_y = (int)game->pl->pl_y;
	game->ray->hit = 0;
	game->ray->side = 0;
	game->ray->camera_wall = 0;
}

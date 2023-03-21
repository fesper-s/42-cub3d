/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gussoare <gussoare@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:32:20 by gussoare          #+#    #+#             */
/*   Updated: 2023/03/21 09:10:48 by gussoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void pl_pos(t_game *game, t_map *map)
{
    int i;
    int j;

    i = -1;
    while (map->map[++i])
    {
        j = -1;
        while(map->map[i][++j])
        {
            if (char_in_str("NSEW", map->map[i][j]))
            {
                game->pl->pl_x = j;
                game->pl->pl_y = i;
            }
            if (map->map[i][j] == 'N')
                game->pl->pldir_y = 1;
            else if (map->map[i][j] == 'S')
                game->pl->pldir_y = -1;
            else if (map->map[i][j] == 'E')
                game->pl->pldir_x = 1;
            else if (map->map[i][j] == 'W')
                game->pl->pldir_x = -1; 
        }
    }
}

void init_var(t_map *map, t_game *game)
{
    game->pl->pl_x = 0;
    game->pl->pl_y = 0;
    game->pl->pldir_x = 0;
    game->pl->pldir_y = 0;
	game->ray->plane_x = 0;
	game->ray->plane_y = 0.66;
    game->ray->raydir_x = 0;
	game->ray->raydir_y = 0;
	game->ray->camera_x = 0;
	game->frame = 0;
	game->old_frame = 0;
    game->map = map;
    pl_pos(game, map);
}
